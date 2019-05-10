#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include <QT>
#include <QTextCodec>
#include <QTextCursor>
#include <QTextBlock>
#include <QByteArray>
#include "qglobal.h"
#include <QBitmap>
#include <qmath.h>
#include <QMessageBox>
#include <QTableWidget>
#include <QTextCodec>

#define test_here 0
float nowRoll,nowPitch,nowYaw,targetYaw;
ExcelEngine excel; //创建excel对象
static int urgCountNum;
static int attiNowCountNum;
static int attiCommCountNum;
static int attiAirComCountNum;
static int urgSaveNum;
 int  comThreadState;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showDial();//显示相关表
    ui->widget_2->installEventFilter(this);
    showQwtPlot();//显示相关曲线
    ui->webView->setUrl(QUrl("file:///E:/gaodemap/gaode.html"));
    ui->webView->show();
    t=0;
    isStartLog=0;
    isSaveData=0;
    isDataShowBack=0;
    urgCountNum=2;
    urgRowcount=2;
    attiAirComCountNum=2;
    attiAirComRowCount=2;
    attiCommCountNum=2;
    attiCommRowCount=2;
    attiNowCountNum=2;
    attiNowRowCount=2;
    checkNew();
    checkPoition=1;
    nowRoll=0;
    nowPitch=0;
    nowYaw=0;
    receiveYaw=0;
    receivePitch=0;
    receiveRoll=0;
    targetYaw=0;
    ui->rolllcdNumber->setStyleSheet("QLCDNumber{color: yellow}");
    ui->yawlcdNumber->setStyleSheet("QLCDNumber{color: white}");
    ui->pitchlcdNumber->setStyleSheet("QLCDNumber{color: red}");
    ui->heightlcdNumber->setStyleSheet("QLCDNumber{color: green}");
    ui->rolllcdNumber->display(nowRoll);
    ui->pitchlcdNumber->display(nowPitch);
    ui->yawlcdNumber->display(nowYaw);
//    ui->targetyawlcdNumber->display(targetYaw);
    ui->yaw2lcdNumber->display(receiveYaw);
    ui->pitch2lcdNumber->display(receivePitch);
    ui->roll2lcdNumber->display(receiveRoll);

    tableFlyPoint();
//    excel.Open(QObject::tr("f:\\Test.xls"),1,false); //打开指定的xls文件的指定sheet，且指定是否可见

//    excelInit();
    th = NULL;
    th = new Thread(this);//开启线程
    dialog=new radiaTrueShow;
    dialog->setAttribute(Qt::WA_QuitOnClose,false);//主界面关闭时，从界面跟着一起关闭
    testTimer = new QTimer(this);
    testTimerShowBack=new QTimer(this);
    testTimerCommAirAtti=new QTimer(this);
    testTimerCommAtti=new QTimer(this);
    testTimerUrg=new QTimer(this);
    testTimerNowAtti=new QTimer(this);
    testTimer->start(200);
    connect(testTimer,SIGNAL(timeout()),this,SLOT(timerEvent()));
    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(slotPopulateJavaScriptWindowObject()));
    QObject::connect(ui->searchComPushButton,&QPushButton::clicked,this,&MainWindow::showAvailableComNumberSlot);
    QObject::connect(ui->dataConnectPushButton,&QPushButton::clicked,this,&MainWindow::dateConnectSlot);
    QObject::connect(ui->openRadiaPushButton,SIGNAL(clicked()),this,SLOT(openRadiaPushButtonSlot()));
    QObject::connect(ui->pushButton_3_setfly,SIGNAL(clicked()),this,SLOT(setTargetPosition()));
    QObject::connect(ui->pushButton_startLog,SIGNAL(clicked()),this,SLOT(startLogSlot()));
    QObject::connect(ui->pushButton_saveData,SIGNAL(clicked()),this,SLOT(saveDataSlot()));
    QObject::connect(ui->spinBoxShowBack,SIGNAL(valueChanged(int)),this,SLOT(dataShowBackSlot(int)));
    QObject::connect(ui->pushButton_dataBackShow,SIGNAL(clicked()),this,SLOT(dataShowBackSlot()));
    QObject::connect(ui->comboBox_mapItem,SIGNAL(currentIndexChanged(int)),this,SLOT(MapItemShow(int)));
    QObject::connect(ui->pushButton_addFlyPoint,SIGNAL(clicked()),this,SLOT(setFlyPointSlot()));
    QObject::connect(ui->pushButton_home,SIGNAL(clicked()),this,SLOT(setHomePointSlot()));
    QObject::connect(ui->pushButton_stopAddFlyPoint,SIGNAL(clicked()),this,SLOT(stopAddFlyPointSlot()));
    QObject::connect(ui->pushButton_importPathway,SIGNAL(clicked()),this,SLOT(drawFlyPathSlot()));
    QObject::connect(ui->pushButton_savePathway,SIGNAL(clicked()),this,SLOT(saveFlyPathSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete testTimer;
    delete testTimerShowBack;
    delete testTimerCommAirAtti;
    delete testTimerCommAtti;
    delete testTimerUrg;
    delete testTimerNowAtti;
    delete th;
    delete dialog;//为什么

//    excel.Close();
}

void MainWindow::getCoordinate(QString lon,QString lat)
{
    QString tempLon=lon;
    QString tempLat=lat;
    ui->lineEdit_mouseLon->setText(tempLon);
    ui->lineEdit_mouseLat->setText(tempLat);
}

void MainWindow::saveFlyPathSlot()
{
    QDateTime datetime;
     QString timestr=datetime.currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")+".haoyi007";
     QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),timestr,
           tr("Files (*.haoyi007)"));

             if (!fileName.isEmpty()) {
                 QFile file(fileName);
                 if (!file.open(QIODevice::WriteOnly)) {
                    // error message
                 } else {
                    QDataStream stream( &file );           //保存二进制文件
                    stream << (quint32)0xBFE3CAAD;
                    file.close();
                 }
             }
}

void MainWindow::aboutSoftwareSlot()
{
    about *dialog=new about;
    dialog->show();
}

void MainWindow::drawFlyPathSlot()
{
    QWebFrame *webFrame = ui->webView->page()->mainFrame();
    QString cmd = QString("drawFlyPath()");
    webFrame->evaluateJavaScript(cmd);
}

void MainWindow::stopAddFlyPointSlot()
{
    QWebFrame *webFrame = ui->webView->page()->mainFrame();
    QString cmd = QString("stopAddFlyPoint()");
    webFrame->evaluateJavaScript(cmd);
}

void MainWindow::setHomePointSlot()
{
    QWebFrame *webFrame = ui->webView->page()->mainFrame();
    QString cmd = QString("setHomePoint()");
    webFrame->evaluateJavaScript(cmd);
}

void MainWindow::setFlyPointSlot()
{
    QWebFrame *webFrame = ui->webView->page()->mainFrame();
    QString cmd = QString("setFlyPoint()");
    webFrame->evaluateJavaScript(cmd);
}


void MainWindow::MapItemShow(int index)
{
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd;
    //index首个为0
    if(index==1){
            cmd = QString("showSatelliteMap()");
    }
    else{
        cmd = QString("showStreetMap()");
    }
    frame->evaluateJavaScript(cmd);
}

void MainWindow::slotPopulateJavaScriptWindowObject()             //这里JS可以通过MainWindow对象来访问其公共槽函数
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("MainWindow", this);
}

void MainWindow::tableFlyPoint()
{
        ui->tableWidget->setRowCount(4);          //设置行数为3
        ui->tableWidget->setColumnCount(7);   //设置列数为7
        ui->tableWidget->setGeometry(QRect(10,455,740,95));//设置tableWidget的大小
        //geometry : QRect，This property holds the geometry of the widget relative to its parent and excluding the window frame.
        ui->tableWidget->setItem(0,0,new QTableWidgetItem("0"));//第一行第一列的内容设置为0
        ui->tableWidget->setItem(1,0,new QTableWidgetItem("1"));//第一行第一列的内容设置为1
        ui->tableWidget->setItem(2,0,new QTableWidgetItem("2"));//第一行第一列的内容设置为2
        ui->tableWidget->setItem(3,0,new QTableWidgetItem("3"));//第一行第一列的内容设置为3
        ui->tableWidget->setRowHeight(0,18);      //设置第一行的行高
        ui->tableWidget->setRowHeight(1,18);      //设置第二行的行高
        ui->tableWidget->setRowHeight(2,18);      //设置第三行的行高
        ui->tableWidget->setRowHeight(3,18);      //设置第三行的行高
        ui->tableWidget->setColumnWidth(0,45);//设置第一列的列宽
        ui->tableWidget->setColumnWidth(1,55);//设置第二列的列宽
        ui->tableWidget->setColumnWidth(2,160);//设置第三列的列宽
        ui->tableWidget->setColumnWidth(3,160);//设置第四列的列宽
        ui->tableWidget->setColumnWidth(4,100);//设置第五列的列宽
        ui->tableWidget->setColumnWidth(5,100);//设置第六列的列宽
        ui->tableWidget->setColumnWidth(6,100);//设置第七列的列宽
        //QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));//编码设置为GB18030
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<tr("编号")<<tr("动作")<<tr("经度")<<tr("纬度")<<tr("高度")<<tr("速度")<<tr("时间"));
        ui->tableWidget->setFont(QFont("wenquanyi",12,3));//设置字体
        QHeaderView* headerView = ui->tableWidget->verticalHeader();
        headerView->setHidden(true);                              //行名隐藏
}

unsigned char send_temp_here[11];
void MainWindow::setTargetPosition()
{
    QString lat,lon;
//    lat = ui->lineEdit_5_target_lat->text();
//    lon = ui->lineEdit_4_target_lon->text();
    target_lat = lat.toFloat();
    target_lon = lon.toFloat();

    send_temp_here[0] = 0xD1;
    send_temp_here[1] = 0x0A;
    send_temp_here[2] = 0x01;
    send_temp_here[3] = (uchar)(((int32_t)(target_lat*10000000))>> 24);
    send_temp_here[4] = (uchar)(((int32_t)(target_lat*10000000))>> 16);
    send_temp_here[5] = (uchar)(((int32_t)(target_lat*10000000))>> 8);
    send_temp_here[6] = (uchar)((int32_t)(target_lat*10000000));
    send_temp_here[7] = (uchar)(((int32_t)(target_lon*10000000))>> 24);
    send_temp_here[8] = (uchar)(((int32_t)(target_lon*10000000))>> 16);
    send_temp_here[9] = (uchar)(((int32_t)(target_lon*10000000))>> 8);
    send_temp_here[10] = (uchar)((int32_t)(target_lon*10000000));
    uchar sum_att = 0;
    for (int h = 3; h<9; h++)
    {
        sum_att += send_temp_here[h];
    }
    send_temp_here[11] = sum_att;

     Q_EMIT senddata((char*)send_temp_here, 12);
}

void MainWindow::askFlyState()
{
    send_temp_here[0] = 0xD1;
    send_temp_here[1] = 0x0A;
    send_temp_here[2] = 0xAA;
    send_temp_here[3] = 0x01;
    send_temp_here[4] = 0x00;
    send_temp_here[5] = 0x00;
    send_temp_here[6] = 0x00;
    send_temp_here[7] = 0x00;
    send_temp_here[8] = 0x00;
    send_temp_here[9] = 0x00;

    uchar sum_att = 0;
    for (int h = 3; h<10; h++)
    {
        sum_att += send_temp_here[h];
    }
    send_temp_here[10] = sum_att;

     Q_EMIT senddata((char*)send_temp_here, 11);
     checkPoition = 1;
}

void MainWindow::checkNew()
{
    if( checkPoition = 0){
        QString lat_here,lon_here;
//         ui->lineEdit_5_target_lat->setText(lat_here.setNum(target_lat));
//         ui->lineEdit_4_target_lon->setText(lon_here.setNum(target_lon));
    }

}

void MainWindow::saveDataSlot()
{
    isSaveData=1;
    excel.Save();//保存
}

void MainWindow::startLogSlot()
{
    if(isStartLog==0){
        QMessageBox msgBox1;
        msgBox1.setText("Log!");
        msgBox1.setInformativeText("是否确定开始进行数据记录?");
        msgBox1.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
        msgBox1.setDefaultButton(QMessageBox::Apply);
        int ret = msgBox1.exec();
        switch (ret) {
          case QMessageBox::Apply:
            isStartLog=1;
            ui->pushButton_startLog->setText("停止记录");
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
              break;
          default:
              // should never be reached
              break;
        }
    }
    else if(isStartLog==1){
        QMessageBox msgBox;
        msgBox.setText("I got data!");
        msgBox.setInformativeText("是否确定保存数据记录?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Save:
              // Save was clicked
            isStartLog=0;
            isSaveData=1;
            excel.Save();//保存
            ui->pushButton_startLog->setText("开始记录");
              break;
          case QMessageBox::Discard:
             isStartLog=0;
             ui->pushButton_startLog->setText("开始记录");
              // Don't Save was clicked
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
              break;
          default:
              // should never be reached
              break;
        }

    }
}

void MainWindow::dataShowBackSlot(int i)
{

     isDataShowBack=1;
     testTimerShowBack->start(200-i);
     connect(testTimerShowBack,SIGNAL(timeout()),this,SLOT(timerEventShowBack()));
}

void MainWindow::timerEventShowBack()
{
    if(attiCommRowCount<=attiCommCountNum){
         QVariant  receiveRoll2 = excel.GetCellData(attiCommRowCount,1); //访问指定单元格数据
         receiveRoll=receiveRoll2.toFloat();
         QVariant  receivePitch2 =excel.GetCellData(attiCommRowCount,2);
         receivePitch=receivePitch2.toFloat();
         QVariant  receiveYaw2 =excel.GetCellData(attiCommRowCount,3);
         receiveYaw=receiveYaw2.toFloat();
         Q_EMIT sendATIOkMain(receiveRoll,receivePitch,receiveYaw,receiveYaw);
         attiCommRowCount++;
    }
    if(attiAirComRowCount<=attiAirComCountNum){
         QVariant  receiveAirRoll2 =excel.GetCellData(attiAirComRowCount,4);
         receiveAirRoll=receiveAirRoll2.toFloat();
         QVariant  receiveAirPitch2 =excel.GetCellData(attiAirComRowCount,5);
         receiveAirPitch=receiveAirPitch2.toFloat();
         QVariant  receiveAirYaw2 =excel.GetCellData(attiAirComRowCount,6);
         receiveAirYaw=receiveAirYaw2.toFloat();
         attiAirComRowCount++;
    }
    if(attiNowRowCount<=attiNowCountNum){
         QVariant  nowRoll2 =excel.GetCellData(attiNowRowCount,7);
         nowRoll=nowRoll2.toFloat();
         QVariant  nowPitch2 =excel.GetCellData(attiNowRowCount,8);
         nowPitch=nowPitch2.toFloat();
         QVariant  nowYaw2 =excel.GetCellData(attiNowRowCount,9);
         nowYaw=nowYaw2.toFloat();
         QVariant  targetYaw2 =excel.GetCellData(attiNowRowCount,10);
         targetYaw=targetYaw2.toFloat();
         attiNowRowCount++;
    }
    if(urgRowcount<=urgCountNum){
         for(int i=0;i<216;i++){
                  URGDataMain2[i]=excel.GetCellData(urgRowcount,11+i);
                  URGDataMain[i]=URGDataMain2[i].toInt();
                  Q_EMIT sendURG(URGDataMain[i],i);
         }
         urgRowcount++;
    }
         timerEvent();//进行曲线的绘制
}

void MainWindow::getPosition(float lat, float lon)
{
    target_lat = lat;
    target_lon = lon;
    checkPoition = 0;
}

void MainWindow::excelInit()
{
     excel.SetCellData(1,1,"receiveCommRoll");
     excel.SetCellData(1,2,"receiveCommPitch");
     excel.SetCellData(1,3,"receiveCommYaw");
     excel.SetCellData(1,4,"receiveAirCommRoll");
     excel.SetCellData(1,5,"receiveAirCommPitch");
     excel.SetCellData(1,6,"receiveAirCommYaw");
     excel.SetCellData(1,7,"nowRoll");
     excel.SetCellData(1,8,"nowPitch");
     excel.SetCellData(1,9,"nowYaw");
     excel.SetCellData(1,10,"targetYaw");
     for(int i=11;i<227;i++){
              excel.SetCellData(1,i,"雷达数据");
     }
}

void MainWindow::aboutExcel()
{
    int num = 0;
    for (int i=1; i<=10; i++)//10行
    {
        for (int j=1; j<=10; j++)//10列
        {
           excel.SetCellData(i,j,++num); //修改指定单元数据
        }
    }
    QVariant data1 = excel.GetCellData(1,1); //访问指定单元格数据
    QVariant data2 =excel.GetCellData(2,2);
    QVariant data3 =excel.GetCellData(3,3);
    qDebug()<<"数据1:%d"<<data1<<"数据2:%d"<<data2<<"数据3:%d"<<data3; //（%d表示整数）
    excel.Save();//保存
    excel.Close();

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

     if(obj == ui->widget_2)
     {
         if(event->type() == QEvent::Paint)
         {
            showQwtPlotCheck();

         }
     }

 return QWidget::eventFilter(obj, event);
}
void MainWindow::showQwtPlot()
{
    for(int i=0;i<9;i++){
        ui->widget_2->addGraph();
        ui->widget_2->graph(i)->setVisible(false);
    }
    ui->widget_2->graph(0)->setPen(QPen(QColor("red")));
    ui->widget_2->graph(1)->setPen(QPen(QColor("black")));
    ui->widget_2->graph(2)->setPen(QPen(QColor("orange")));
    ui->widget_2->graph(3)->setPen(QPen(QColor("green")));
    ui->widget_2->graph(4)->setPen(QPen(QColor("yellow")));
    ui->widget_2->graph(5)->setPen(QPen(QColor("blue")));
    ui->widget_2->graph(6)->setPen(QPen(QColor("gray")));
    ui->widget_2->graph(7)->setPen(QPen(QColor("dark gray")));
    ui->widget_2->graph(8)->setPen(QPen(QColor("cyan")));
}

void MainWindow::showQwtPlotCheck()
{
    if(ui->checkBox_commroll->isChecked()) {
        ui->widget_2->graph(0)->setVisible(true);
    }
    else{
        ui->widget_2->graph(0)->setVisible(false);

    }
    if(ui->checkBox_2_commpitch->isChecked()) {
        ui->widget_2->graph(1)->setVisible(true);
    }
    else{
        ui->widget_2->graph(1)->setVisible(false);

    }
    if(ui->checkBox_3_commyaw->isChecked()) {
        ui->widget_2->graph(2)->setVisible(true);
    }
    else{
        ui->widget_2->graph(2)->setVisible(false);
    }
    if(ui->checkBox_4curent_roll->isChecked()) {
        ui->widget_2->graph(3)->setVisible(true);
    }
    else{
        ui->widget_2->graph(3)->setVisible(false);
    }
    if(ui->checkBox_5curent_pitch->isChecked()) {
        ui->widget_2->graph(4)->setVisible(true);
    }
    else{
        ui->widget_2->graph(4)->setVisible(false);
    }
    if(ui->checkBox_6curent_yaw->isChecked()) {
        ui->widget_2->graph(5)->setVisible(true);
    }
    else{
        ui->widget_2->graph(5)->setVisible(false);
    }
    if(ui->checkBox_airrec_roll->isChecked()) {
        ui->widget_2->graph(6)->setVisible(true);
    }
    else{
        ui->widget_2->graph(6)->setVisible(false);
    }
    if(ui->checkBox_airrec_pitch->isChecked()) {
        ui->widget_2->graph(7)->setVisible(true);
    }
    else{
        ui->widget_2->graph(7)->setVisible(false);
    }
    if(ui->checkBox_airrec_yaw->isChecked()) {
        ui->widget_2->graph(8)->setVisible(true);
    }
    else{
        ui->widget_2->graph(8)->setVisible(false);
    }
}

void MainWindow::showDial()
{

}


void MainWindow::timerEvent()//定时器事件，应该是200ms执行一次
{
//    qDebug()<<"thread running is"<<currentThreadId();//返回标识当前正在执行的线程,返回线程的ID
//    qDebug()<<th->stopped;
//    if(th->myCom->isOpen())//牵一发而动全身
//    {
//        if(th->isFinished()||comThreadState==0)
//        {
////            th->stopThread();
//            th->quit();
////            th->wait();//如果线程退出，则wait会返回
//            if(th->isFinished()){
//                qDebug()<<"th thread stopped";//对于意外从线程关闭，需要对其进行重新启动
//                QString portName=ui->comNumberComboBox->currentText();
//                int baudRate=ui->boundaryComboBox->currentText().toInt();
//                th->setObjectName("th thread");//设置线程名字
//                th->comThreadInit(portName,baudRate);
//                th->start();
//               connect(th, SIGNAL(sendATIOk(float,float,float,float)), this, SLOT(receiveATISlot(float,float,float,float)));
//               connect(th, SIGNAL(send_Now_Atti(float,float,float,float)), this, SLOT(receiveNowAttiSlot(float,float,float,float)));
//               connect(th,SIGNAL(send_Air_Rec_Commatti(float,float,float)),this,SLOT(receiveAirCommAttiSlot(float,float,float)));
//               connect(this,SIGNAL(senddata(char*,int)),th,SLOT(sendDateSlot(char*,int)));
//               connect(th,SIGNAL(transReceiveData(QByteArray)),this,SLOT(receiveDateSlot(QByteArray)));
//               connect(th,SIGNAL(transTargetPosition(float,float)),this,SLOT(getPosition(float,float)));
//            //将线程内发出的信号，与主线程中的槽进行连接，从而可以在主线程中对数据进行处理
//               connect(this,SIGNAL(sendURG(int,int)),dialog,SLOT(receiveURGDataSlot2(int,int)));
//               connect(th,SIGNAL(sendURGData(int,int)),dialog,SLOT(receiveURGDataSlot2(int,int)));
//               connect(this,SIGNAL(sendATIOkMain(float,float,float,float)),dialog,SLOT(receiveATISlot2(float,float,float,float)));
//               connect(th, SIGNAL(sendATIOk(float,float,float,float)), dialog, SLOT(receiveATISlot2(float,float,float,float)));
//               connect(th, SIGNAL(send_Now_Atti(float,float,float,float)), dialog, SLOT(receiveNowAttiSlot2(float,float,float,float)));
//               ui->dataConnectPushButton->setText("断开");
//            }
//         }
//         if(th->isRunning())qDebug()<<"Com opened!";//判断从线程是否在一直执行,
//         th->stopped=1;//防止串口自动关闭
//         comThreadState=0;
//    }
    t +=0.2;//更新波形数据(应该可以记录很长一段时间)，波形显示到多少，应该就是执行了多少秒

//    for(int i=0;i<7;i++){
//        if(receiveRoll>range_y)range_y=receiveRoll;
//    }
    range_y=14;
    if(t>50)ui->widget_2->xAxis->setRange(t-50,t);//相当于显示250个数据
    else ui->widget_2->xAxis->setRange(0,50);

    x.append(t);
    y[0].append(receiveRoll);
    ui->widget_2->graph(0)->setData(x,y[0]);

    y[1].append(receivePitch);
    ui->widget_2->graph(1)->setData(x,y[1]);

    y[2].append(receiveYaw);
    ui->widget_2->graph(2)->setData(x,y[2]);

    y[3].append(nowRoll);
    ui->widget_2->graph(3)->setData(x,y[3]);

    y[4].append(nowPitch);
    ui->widget_2->graph(4)->setData(x,y[4]);

    y[5].append(nowYaw);
    ui->widget_2->graph(5)->setData(x,y[5]);

    y[6].append(receiveAirRoll);
    ui->widget_2->graph(6)->setData(x,y[6]);

    y[7].append(receiveAirPitch);
    ui->widget_2->graph(7)->setData(x,y[7]);

    y[8].append(receiveAirYaw);
    ui->widget_2->graph(8)->setData(x,y[8]);

   if(ui->checkBox_3_commyaw->isChecked()||ui->checkBox_6curent_yaw->isChecked()||ui->checkBox_airrec_yaw->isChecked()) {
        ui->widget_2->yAxis->setRange(-180,180);
   }
   else{
       ui->widget_2->yAxis->setRange(-15,range_y+1);
   }
    ui->widget_2->replot();
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   painter.drawPixmap(0,0,width(),height(),QPixmap("background.bmp"));
}

void MainWindow::sendDateSlot()
{
    qDebug()<<"senddata";
    char dat[5] = {55,1,5,0};
    char *TxData=dat;
    Q_EMIT senddata(TxData,5);
}

void MainWindow::receiveDateSlot(QByteArray requestData)
{
//    QString strDis=requestData.toHex().data();//以十六进制显示
    if(requestData!= NULL)//填充显示是乱码
    {
        ui->dateTextEdit->document()->setMaximumBlockCount(100);//设置最多显示100行，多余的自动删除
//        ui->dateTextEdit->append(strDis);
        ui->dateTextEdit->append(requestData);
        ui->dateTextEdit->setTextInteractionFlags(Qt::TextEditorInteraction);//设置文本框为可编辑状态
    }
    requestData.clear();
}

void MainWindow::showAvailableComNumberSlot()
{
    ui->comNumberComboBox->clear();//每次点击搜索时，都将之前搜索到的全部清除，然后重新加载，防止串口号重复。
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();

        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->comNumberComboBox->addItem(info.portName());
            serial.close();
        }
    }
    if(ui->comNumberComboBox->count()==0)QMessageBox::warning(this,"warning","没有可用的读写串口！");
}


void MainWindow::dateConnectSlot()
{
    if(ui->dataConnectPushButton->text() == QString("连接"))
    {
         QString portName=ui->comNumberComboBox->currentText();
         int baudRate=ui->boundaryComboBox->currentText().toInt();
         th->setObjectName("th thread");//设置线程名字
         th->comThreadInit(portName,baudRate);
         th->start();
        connect(th, SIGNAL(sendATIOk(float,float,float,float)), this, SLOT(receiveATISlot(float,float,float,float)));//主界面LCD显示
        connect(th, SIGNAL(send_Now_Atti(float,float,float,float)), this, SLOT(receiveNowAttiSlot(float,float,float,float)));
        connect(th,SIGNAL(send_Air_Rec_Commatti(float,float,float)),this,SLOT(receiveAirCommAttiSlot(float,float,float)));
        connect(this,SIGNAL(senddata(char*,int)),th,SLOT(sendDateSlot(char*,int)));
        connect(th,SIGNAL(transReceiveData(QByteArray)),this,SLOT(receiveDateSlot(QByteArray)));
        connect(th,SIGNAL(transTargetPosition(float,float)),this,SLOT(getPosition(float,float)));
     //将线程内发出的信号，与主线程中的槽进行连接，从而可以在主线程中对数据进行处理
        connect(this,SIGNAL(sendURG(int,int)),dialog,SLOT(receiveURGDataSlot2(int,int)));
        connect(th,SIGNAL(sendURGData(int,int)),dialog,SLOT(receiveURGDataSlot2(int,int)));
        connect(this,SIGNAL(sendATIOkMain(float,float,float,float)),dialog,SLOT(receiveATISlot2(float,float,float,float)));//在激光雷达画布上使用
        connect(th, SIGNAL(sendATIOk(float,float,float,float)), dialog, SLOT(receiveATISlot2(float,float,float,float)));//在激光雷达画布上使用
        connect(th, SIGNAL(send_Now_Atti(float,float,float,float)), dialog, SLOT(receiveNowAttiSlot2(float,float,float,float)));
        ui->dataConnectPushButton->setText("断开");
        if(th->isRunning())qDebug()<<"th thread is running!";//判断从线程是否在一直执行,这里不管用
    }
     else
    {
          ui->dataConnectPushButton->setText("连接");
          th->stopThread();
          if(th->isFinished())qDebug()<<"th thread is finished!";
     }

}
void  MainWindow::getCursesShowSlot()
{
    qDebug()<<"show";
    //有待完善
}

void MainWindow::saveUrgSlot()
{
    excel.SetCellData(urgCountNum,urgSaveNum+11,URGDataMain[urgSaveNum]); //修改指定单元数据
    if(urgSaveNum=215)urgCountNum++;
}

void MainWindow::receiveURGDataSlot(int data,int num)
{
           urgSaveNum=num;
           URGDataMain[num]=data;
           if(isStartLog==1){
               testTimerUrg->start(100);
               connect(testTimerUrg,SIGNAL(timeout()),this,SLOT(saveUrgSlot()));
           }

}

void MainWindow::saveCommAirAttiSlot()
{
    excel.SetCellData(attiAirComCountNum,4,receiveAirRoll);
    excel.SetCellData(attiAirComCountNum,5,receiveAirPitch);
    excel.SetCellData(attiAirComCountNum,6,receiveAirYaw);//修改指定单元数据
    attiAirComCountNum++;
}

void MainWindow::receiveAirCommAttiSlot(float roll, float pitch, float yaw)
{
    receiveAirRoll=roll;
    receiveAirPitch=pitch;
    receiveAirYaw=yaw;
    if(isStartLog==1){
        testTimerCommAirAtti->start(100);
        connect(testTimerCommAirAtti,SIGNAL(timeout()),this,SLOT(saveCommAirAttiSlot()));
    }
}

void MainWindow::saveCommAttiSlot()
{
    excel.SetCellData(attiCommCountNum,1,receiveRoll);
    excel.SetCellData(attiCommCountNum,2,receivePitch);
    excel.SetCellData(attiCommCountNum,3,receiveYaw);//修改指定单元数据
    attiCommCountNum++;
}

void MainWindow::receiveATISlot(float roll, float pitch, float yaw,float current_Yaw)
{
    receiveRoll=roll;
    receivePitch=pitch;
    receiveYaw=yaw;
    if(isStartLog==1){
        testTimerCommAtti->start(100);
        connect(testTimerCommAtti,SIGNAL(timeout()),this,SLOT(saveCommAttiSlot()));
    }
    qDebug()<<"got data";
    receiveCurrentYaw=current_Yaw;
    ui->yaw2lcdNumber->display(receiveYaw);
    ui->pitch2lcdNumber->display(receivePitch);
    ui->roll2lcdNumber->display(receiveRoll);

}

void MainWindow::saveNowAttiSlot()
{
    excel.SetCellData(attiNowCountNum,7,nowRoll);
    excel.SetCellData(attiNowCountNum,8,nowPitch);
    excel.SetCellData(attiNowCountNum,9,nowYaw);//修改指定单元数据
    excel.SetCellData(attiNowCountNum,10,targetYaw);
    attiNowCountNum++;
}

void MainWindow::receiveNowAttiSlot(float roll, float pitch, float yaw, float target_Yaw)
{
    if(roll>-30&&roll<30)nowPreRoll = roll;
    if(pitch>-30&&pitch<30)nowPrePitch = pitch;
    if(yaw>-180&&yaw<180)nowPreYaw = yaw;
    if(target_Yaw>-180&&target_Yaw<180)targetPreYaw = target_Yaw;
    nowRoll = nowPreRoll;
    nowPitch = nowPrePitch;
    nowYaw = nowPreYaw;
    targetYaw = targetPreYaw;
    if(isStartLog==1){
        testTimerNowAtti->start(100);
        connect(testTimerNowAtti,SIGNAL(timeout()),this,SLOT(saveNowAttiSlot()));
    }
    ui->rolllcdNumber->display(nowRoll);
    ui->pitchlcdNumber->display(nowPitch);
    ui->yawlcdNumber->display(nowYaw);
//    ui->targetyawlcdNumber->display(targetYaw);
}


void MainWindow::openRadiaPushButtonSlot()
{   
//    if(ui->openRadiaPushButton->text() == QString("打开雷达显示"))
//    {
        dialog->show();
        dialog->setFixedSize(550,600);
//        connect(th,SIGNAL(sendURGData(int,int)),dialog,SLOT(receiveURGDataSlot2(int,int)));
//        ui->openRadiaPushButton->setText("关闭雷达显示");
//    }
// else
//    {
//          ui->openRadiaPushButton->setText("打开雷达显示");
//    }
}
