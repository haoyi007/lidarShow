#ifndef RADIATRUESHOW_H
#define RADIATRUESHOW_H

#include <QDialog>
#include <QPointF>
namespace Ui {
class radiaTrueShow;
}

class radiaTrueShow : public QDialog
{
    Q_OBJECT

public:
    explicit radiaTrueShow(QWidget *parent = 0);
    ~radiaTrueShow();
    QTimer *radiaTimer;
    QPixmap *newPix ;
    int URGData[280];//类成员不可以在定义时初始化
    int receiveNum[100];
    void doRadar();
    void paintEvent(QPaintEvent *event);
    char data_to_send[50];	//发送数据缓存
    float draw_roll,draw_pitch,draw_yaw,draw_current_Yaw;
    float now_yaw_here,now_roll_here,now_pitch_here,now_taretyaw_here;

public Q_SLOTS:
        void receiveURGDataSlot2(int data,int whitch);
        void receiveATISlot2(float roll,float pitch,float yaw,float current_Yaw);
        void receiveNowAttiSlot2(float roll,float pitch,float yaw,float target_Yaw);
        void connectURGData();
Q_SIGNALS:
        void senddata(char *TxData,int num);

private:
    Ui::radiaTrueShow *ui;
    QPointF *pointf[280];    // 画多个点
    QPixmap *pix;
};

#endif // RADIATRUESHOW_H
