#include "thread.h"
#include "mainwindow.h"
#include<qdebug.h>

static  int URGDataTemp[280];

Thread::Thread(QObject *parent)
    :QThread(parent)
{
    qDebug()<<"begin";
     myCom= new QSerialPort();
     stopped = 1;
}
Thread::~Thread()
{
   stopThread();
   delete myCom;
    //执行delete时会调用析构函数
}
void Thread::run()
{
    QByteArray tempStr;
    char *ch;//不要定义成ch[n];
    int bytenum = 0;
   qDebug()<<"run";
    while(stopped)
    {
//        msleep(50);    //delay 5ms
        comThreadState=1;
        qDebug()<<"running";
        if(myCom->isOpen())
        {
//            myTime				= new QTimer();//
//            connect(myTime, SIGNAL(timeout()), this, SLOT(read_Data()));//也进行定时读取数据
//            connect(myCom, SIGNAL(readyRead()), this, SLOT(read_Data())); //也可以按信号来接收

            bytenum = myCom->bytesAvailable();
            if(bytenum>=20)  //限制频繁进行数据读取
            {
                 qDebug()<<"receiving";
                 tempStr= myCom->read(bytenum);
               if(!tempStr.isNull()){
                   Q_EMIT transReceiveData(tempStr);//可十六进制显示接收的内容
               }
               ch = tempStr.data();
               for(int i=0;i<bytenum;i++)
               {
                   //数据间的相互转化的网址：http://blog.csdn.net/ymc0329/article/details/7284514
                   HAOYI_DT_Data_Receive_Prepare(*(ch+i));
               }
            }

        }

    }
}
void Thread::read_Data()
{
    QByteArray tempStr;
    char *ch;//不要定义成ch[n];
    int bytenum = 0;
    bytenum = myCom->bytesAvailable();
    if(bytenum>=30)  //限制频繁进行数据读取
    {
         qDebug()<<"receiving";
         tempStr= myCom->read(bytenum);
       if(!tempStr.isNull()){
           Q_EMIT transReceiveData(tempStr);//可十六进制显示接收的内容
       }
       ch = tempStr.data();
       for(int i=0;i<bytenum;i++)
       {
           //数据间的相互转化的网址：http://blog.csdn.net/ymc0329/article/details/7284514
           HAOYI_DT_Data_Receive_Prepare(*(ch+i));
       }
    }
}
void Thread::stopThread()
{
    stopped = 0;
    QByteArray temp =myCom->readAll();//清除缓冲区数据
    if(myCom->isOpen()) {
               myCom->close();
           }
}

/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Prepare函数是协议预解析，根据协议的格式，将收到的数据进行一次格式性解析，格式正确的话再进行数据解析
//移植时，此函数应由用户根据自身使用的通信方式自行调用，比如串口每收到一字节数据，则调用此函数一次
//此函数解析出符合格式的数据帧后，会自行调用数据解析函数
void Thread::HAOYI_DT_Data_Receive_Prepare(quint8 data)
{
    //一次最大接收数据120个
    static quint8 RxBuffer[120];
    static quint8 _data_len = 0,_data_cnt = 0;
    static quint8 state = 0;
    if(state==0&&data==0xAA)
    {
        state=1;
        RxBuffer[0]=data;
//        qDebug()<<  "0";
    }
    else if((state==1)&&(data==0xAA))
    {
        state=2;
        RxBuffer[1]=data;
//        qDebug()<<  "1";
    }
    else if(state==2&&(data==0XC0||data==0X05))
    {
        state=3;
        RxBuffer[2]=data;
//        qDebug()<<  "2";
    }
    else if(state==3&&data<60)
    {
        state = 4;
        RxBuffer[3]=data;    //数据长度
        _data_len = data;
        _data_cnt = 0;
//         qDebug()<<  "3";
    }
    else if(state==4&&_data_len>0)
    {
        _data_len--;
        RxBuffer[4+_data_cnt++]=data;  //存储数据
        if(_data_len==0){state = 5;}
    }
    else if(state==5)
    {
//         qDebug()<<  "n";
        state = 0;
        RxBuffer[4+_data_cnt]=data; //应该是最后一个数据
        HAOYI_DT_Data_Receive_Anl(RxBuffer,_data_cnt+5);
    }
    else
        state = 0;
}



//该协议解析对应于购买的那个CAN转串口的那个模块
void Thread::HAOYI_DT_Data_Receive_Prepare2(quint8 data)
{
    //一次最大接收数据120个
    static quint8 RxBuffer[120];
    static quint8 _data_len = 0,_data_cnt = 0;
    static quint8 state = 0;

    if(state==0&&data==0xD1)
    {
        state=1;
        RxBuffer[0]=data;
    }
    else if(state==0&&data==0xD2)
    {
        state=11;
        RxBuffer[0]=data;
    }
    else if((state==1)&&(data==0x0F))
    {
        state=21;
        RxBuffer[1]=data;
    }
    else if((state==11)&&(data==0xD2))
    {
        state=12;
        RxBuffer[1]=data;
    }
    else if((state==12)&&(data==0xD2))
    {
        state=13;
        RxBuffer[2]=data;
        _data_len = 5;
        _data_cnt = 0;
    }
    else if(state==13)
    {
        _data_len--;
        RxBuffer[3+_data_cnt++]=data;
        if(_data_len==1){state = 14;}
    }
    else if(state==14)
    {
        state = 0;
        RxBuffer[4+_data_cnt]=data; //应该是最后一个数据
        HAOYI_DT_Data_Receive_Anl2(RxBuffer);
    }
    else if((state==1)&&(data==0x0A||data==0x00))
    {
        state=22;
        RxBuffer[1]=data;
    }
    else if((state==1)&&(data==0xAA))
    {
        state=22;
        RxBuffer[1]=data;
    }
    else if(state==21&&(data==0XC0))
    {
        state=31;
        RxBuffer[2]=data;
        _data_len = 8;
        _data_cnt = 0;
    }
    else if(state==22&&(data==0X00))
    {
        state=32;
        RxBuffer[2]=data;
        _data_len = 8;
        _data_cnt = 0;
    }
    else if(state==22&&(data==0X0A))
    {
        state=32;
        RxBuffer[2]=data;
        _data_len = 8;
        _data_cnt = 0;
    }
    else if(state==31)
    {
        _data_len--;
        RxBuffer[3+_data_cnt++]=data;
        if(_data_len==1){state = 41;}
    }
    else if(state==32)
    {

        _data_len--;
        RxBuffer[3+_data_cnt++]=data;
        if(_data_len==1){state = 42;}
    }
    else if(state==41)
    {
        state = 0;
        RxBuffer[4+_data_cnt]=data; //应该是最后一个数据
        HAOYI_DT_Data_Receive_Anl2(RxBuffer);
    }
    else if(state==42)
    {
        state = 0;
        RxBuffer[4+_data_cnt]=data; //应该是最后一个数据
        HAOYI_DT_Data_Receive_Anl2(RxBuffer);
    }
    else
        state = 0;
}


void Thread::HAOYI_DT_Data_Receive_Anl2(quint8 *data_buf)
{

    float commRoll,commPitch,commYaw,current_Yaw;
    float now_roll,now_pitch,now_yaw,target_yaw;
    float air_rec_roll,air_rec_pitch,air_rec_yaw;
    if(!((*(data_buf)==0xD1||*(data_buf)==0xD2) && (*(data_buf+1)==0x0F||*(data_buf+1)==0x0A||*(data_buf+1)==0xAA||*(data_buf+1)==0x00||*(data_buf+1)==0xD2)))		return;		//判断帧头

    if(*(data_buf+2)==0X00&&*(data_buf+1)==0X0A)   //接收姿态命令信息
    {
        quint8 sum = 0;
        for(qint8 i=3;i<9;i++)
        {
            sum += *(data_buf+i);
        }
        if(!(sum==*(data_buf+9)))		return;		//判断sum
        //这里存在一个量纲的变化
        commRoll=0.01*((qint16)(*(data_buf+3)<< 8 | *(data_buf+4)));
        commPitch=0.01*((qint16)(*(data_buf+5)<< 8 | *(data_buf+6)));
        commYaw=0.01*((qint16)(*(data_buf+7)<< 8 | *(data_buf+8)));
        current_Yaw=10;
        Q_EMIT sendATIOk(commRoll,commPitch,commYaw,current_Yaw);
    }
   else if(*(data_buf+2)==0X00&&*(data_buf+1)==0X00)   //接收当前姿态信息
    {
        quint8 sum = 0;
        for(qint8 i=3;i<9;i++)
        {
            sum += *(data_buf+i);
        }
        if(!(sum==*(data_buf+9)))		return;		//判断sum
        now_roll=(qint16)(*(data_buf+3));
        now_pitch=(qint16)(*(data_buf+4));
        now_yaw=((qint16)(*(data_buf+5)<< 8 | *(data_buf+6)));
        target_yaw=((qint16)(*(data_buf+7)<< 8 | *(data_buf+8)));
        Q_EMIT send_Now_Atti(now_roll,now_pitch,now_yaw,target_yaw);
    }
    else if(*(data_buf+2)==0XC0)//接收激光雷达数据，这里不是
    {
            quint8 sum = 0;
            for(qint8 t=3;t<8;t++)
            {
                sum += *(data_buf+t);
            }
            if(!(sum==*(data_buf+8)))		return;		//判断sum
            URGDataTemp[*(data_buf+7)]=(int)((*(data_buf+3)<< 24) |(*(data_buf+4)<< 16) | (*(data_buf+5) << 8) |*(data_buf+6));
            Q_EMIT sendURGData(URGDataTemp[*(data_buf+7)],(int)*(data_buf+7));
    }
    else if(*(data_buf+2)==0X0A)//接收查询回复的目标position
    {
            rec_lat=(float)((int)((*(data_buf+3)<< 24) |(*(data_buf+4)<< 16) | (*(data_buf+5) << 8) |*(data_buf+6))*0.0000001f);
            rec_lon=(float)((int)((*(data_buf+7)<< 24) |(*(data_buf+8)<< 16) | (*(data_buf+9) << 8) |*(data_buf+10))*0.0000001f);
            Q_EMIT transTargetPosition(rec_lat,rec_lon);
    }
    else if(*(data_buf+2)==0XD2)//接收飞机穿过来的飞机接收到的姿态命令
    {
            quint8 sum = 0;
            for(qint8 t=3;t<7;t++)
            {
                sum += *(data_buf+t);
            }
            if(!(sum==*(data_buf+7)))		return;		//判断sum
            air_rec_roll=(float)(*(data_buf+3));
            air_rec_pitch=(float)(*(data_buf+4));
            air_rec_yaw=(float)(*(data_buf+5)<<8|*(data_buf+6));
            qDebug()<<  "air_rec_roll is"<<  air_rec_roll<< "air_rec_pitch is"<<  air_rec_pitch<<"air_rec_yaw is"<<  air_rec_yaw;
            Q_EMIT send_Air_Rec_Commatti(air_rec_roll,air_rec_pitch,air_rec_yaw);
    }
}


/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Anl函数是协议数据解析函数，函数参数是符合协议格式的一个数据帧，该函数会首先对协议数据进行校验
//校验通过后对数据进行解析，实现相应功能
//此函数可以不用用户自行调用，由函数Data_Receive_Prepare自动调用

void Thread::HAOYI_DT_Data_Receive_Anl(quint8 *data_buf,quint8 num)
{
    quint8 sum = 0;
    float commRoll,commPitch,commYaw,current_Yaw;
    for(qint8 i=0;i<(num-1);i++)
        sum += *(data_buf+i);
    if(!(sum==*(data_buf+num-1)))		return;		//判断sum
    if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAA))		return;		//判断帧头

    if(*(data_buf+2)==0X05)   //接收姿态命令信息
    {
        //这里存在一个量纲的变化
        commRoll=0.01*((qint16)(*(data_buf+4)<< 8 | *(data_buf+5)));//将其缩放回原来的倍数
        commPitch=0.01*((qint16)(*(data_buf+6)<< 8 | *(data_buf+7)));
        commYaw=0.01*((qint16)(*(data_buf+8)<< 8 | *(data_buf+9)));
        current_Yaw=0.01*((qint16)(*(data_buf+10)<< 8 | *(data_buf+11)));
        qDebug()<<"have data";
        Q_EMIT sendATIOk(commRoll,commPitch,commYaw,current_Yaw);//在主界面和激光雷达画布上接收该信号
    }
    else if(*(data_buf+2)==0XC0)//接收激光雷达数据，yes
    {
//            qDebug()<<  "got URG!";
            if(*(data_buf+4)<0) *(data_buf+4)=0;
            if(*(data_buf+4)>31) *(data_buf+4)=31;
            for(qint8 i=0;i<8;i++)
            {
                URGDataTemp[*(data_buf+4)*8+i]=(quint16)( (*(data_buf+5+2*i) << 8) |*(data_buf+6+2*i));
                Q_EMIT sendURGData(URGDataTemp[*(data_buf+4)*8+i],(*(data_buf+4)*8+i));
            }
    }

}

void Thread::comThreadInit(QString portName,int baudRate)
{
    qDebug()<<"connected";
 //    myCom= new QSerialPort();
      if(myCom->isOpen())
       {
            myCom->close();
        }
      stopped = 1;
      myCom->setPortName(portName);
      myCom->open(QIODevice::ReadWrite);
      myCom->setBaudRate(baudRate);
      myCom->setDataBits(QSerialPort::Data8);//数据位8位
      myCom->setParity(QSerialPort::NoParity) ;//无奇偶校验
      myCom->setStopBits(QSerialPort::OneStop);//停止位1位
      myCom->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    qDebug()<<  baudRate<<  portName;
}


void Thread::sendDateSlot(char *TxData,int num)
{
    myCom->write(TxData,num);
    qDebug()<<"send aaaa";
}

