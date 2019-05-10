/********************************************************************************
** Form generated from reading UI file 'radiatrueshow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RADIATRUESHOW_H
#define UI_RADIATRUESHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_radiaTrueShow
{
public:
    QWidget *widget;
    QPushButton *pushButton;

    void setupUi(QDialog *radiaTrueShow)
    {
        if (radiaTrueShow->objectName().isEmpty())
            radiaTrueShow->setObjectName(QStringLiteral("radiaTrueShow"));
        radiaTrueShow->resize(853, 593);
        widget = new QWidget(radiaTrueShow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(140, 20, 541, 521));
        pushButton = new QPushButton(radiaTrueShow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(34, 20, 81, 23));

        retranslateUi(radiaTrueShow);

        QMetaObject::connectSlotsByName(radiaTrueShow);
    } // setupUi

    void retranslateUi(QDialog *radiaTrueShow)
    {
        radiaTrueShow->setWindowTitle(QApplication::translate("radiaTrueShow", "Dialog", 0));
        pushButton->setText(QApplication::translate("radiaTrueShow", "\351\233\267\350\276\276\346\225\260\346\215\256\345\233\236\346\224\276", 0));
    } // retranslateUi

};

namespace Ui {
    class radiaTrueShow: public Ui_radiaTrueShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RADIATRUESHOW_H
