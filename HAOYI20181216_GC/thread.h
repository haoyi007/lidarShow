#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <qfiledialog>
#include <QSettings>
#include <qdebug.h>
#include <QTextCodec>
#include "ui_mainwindow.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread( QObject *parent);
    ~Thread();
    void run();
    void stopThread();
    void comThreadInit(QString portName,int baudRate);
    void HAOYI_DT_Data_Receive_Prepare(quint8 data);
    void HAOYI_DT_Data_Receive_Prepare2(quint8 data);//对应购买的can口的通信协议
    void HAOYI_DT_Data_Receive_Anl(quint8 *data_buf,quint8 num);
    void HAOYI_DT_Data_Receive_Anl2(quint8 *data_buf);//对应购买的can口的通信协议
    float rec_lat,rec_lon;
    volatile bool stopped;
    QSerialPort *myCom;//串口变量
    QTimer *myTime;

public Q_SLOTS:
    void sendDateSlot(char  *TxData,int  num);
    void read_Data();   //读取数据

Q_SIGNALS:
    void sendATIOk(float roll,float pitch,float yaw,float current_Yaw);
    void send_Now_Atti(float roll,float pitch,float yaw,float target_Yaw);
    void send_Air_Rec_Commatti(float roll,float pitch,float yaw);
    void sendURGData(int data,int whitchnum);
    void transReceiveData(QByteArray requestData);
    void transTargetPosition(float lat,float lon);
private:

    QByteArray requestData;

};

#endif // THREAD_H
