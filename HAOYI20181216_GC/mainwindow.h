#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "thread.h"
#include <QTextCodec>
#include <QTextCursor>
#include <QTextBlock>
#include <qlayout.h>
#include <QVariant>
#include <QPixmap>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QtCore/qmath.h>
#include <QPoint>
#include <QPainter>
#include <QTimer>
#include<QPainterPath>
#include "radiatrueshow.h"
#include<QToolButton>
#include "execelengine1.h"
#include <QWebView>
#include <QtWebKit>
#include <QWebFrame>
#include "about.h"

#  ifndef foreach
#    define foreach Q_FOREACH
#  endif

extern int  comThreadState;//从线程是否处于激活状态

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   QTimer *testTimer;
   QTimer *testTimerShowBack;
   QTimer *testTimerUrg;
   QTimer *testTimerNowAtti;
   QTimer *testTimerCommAtti;
   QTimer *testTimerCommAirAtti;
   float receiveRoll,receivePitch,receiveYaw,receiveCurrentYaw;
   float receiveAirRoll,receiveAirPitch,receiveAirYaw;
   float nowPreRoll,nowPrePitch,nowPreYaw,targetPreYaw;
   float target_lon,target_lat;
   QVariant URGDataMain2[220];//类成员不可以在定义时初始化
   int URGDataMain[220];
   float t;//波形图坐标间隔
   int urgRowcount,attiNowRowCount,attiCommRowCount,attiAirComRowCount;
   int checkPoition;
   int isStartLog,isSaveData,isDataShowBack;
   QVector<double>x;
   QVector<double>y[10];
   double range_y;         //画图时定位波形图的最大上限
   void showDial();//显示表、指南针等相关操作
   void showQwtPlot();//显示qwtplot曲线等相关信息
   void showQwtPlotCheck();
   void excelInit();
   void aboutExcel();
   void paintEvent(QPaintEvent *event);
   void checkNew();
   void tableFlyPoint();

public Q_SLOTS:
    void sendDateSlot();
    void receiveDateSlot(QByteArray requestData);
    void showAvailableComNumberSlot();
    void dateConnectSlot();
    void getCursesShowSlot();
    void receiveURGDataSlot(int,int);
    void receiveATISlot(float roll,float pitch,float yaw,float current_Yaw);
    void receiveNowAttiSlot(float roll,float pitch,float yaw,float target_Yaw);
   void receiveAirCommAttiSlot(float roll,float pitch,float yaw);
    void timerEvent();
    void timerEventShowBack();
    void openRadiaPushButtonSlot();
    bool eventFilter(QObject *obj, QEvent *event);
    void setTargetPosition();
    void askFlyState();
    void getPosition(float lat,float lon);
    void startLogSlot();
    void saveDataSlot();
    void dataShowBackSlot(int i);
    void saveNowAttiSlot();
    void saveUrgSlot();
    void saveCommAttiSlot();
    void saveCommAirAttiSlot();
    void slotPopulateJavaScriptWindowObject();
    void MapItemShow(int index);
    void getCoordinate(QString lon,QString lat);
    void setFlyPointSlot();
    void setHomePointSlot();
    void stopAddFlyPointSlot();
    void drawFlyPathSlot();
    void saveFlyPathSlot();
    void aboutSoftwareSlot();
Q_SIGNALS:
    void senddata(char *TxData,int num);
    void sendURG(int data,int whitch);
   void sendATIOkMain(float roll,float pitch,float yaw,float current_Yaw);
private:
    Ui::MainWindow *ui;
    Thread *th;
    radiaTrueShow *dialog;

};




#endif // MAINWINDOW_H
