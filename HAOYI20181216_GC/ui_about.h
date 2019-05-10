/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_about
{
public:
    QLabel *label;
    QLabel *movieLabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *stopButton;
    QPushButton *contrinueButton;

    void setupUi(QDialog *about)
    {
        if (about->objectName().isEmpty())
            about->setObjectName(QStringLiteral("about"));
        about->resize(400, 300);
        label = new QLabel(about);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 20, 272, 38));
        movieLabel = new QLabel(about);
        movieLabel->setObjectName(QStringLiteral("movieLabel"));
        movieLabel->setGeometry(QRect(50, 70, 291, 151));
        widget = new QWidget(about);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(100, 240, 158, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stopButton = new QPushButton(widget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        horizontalLayout->addWidget(stopButton);

        contrinueButton = new QPushButton(widget);
        contrinueButton->setObjectName(QStringLiteral("contrinueButton"));

        horizontalLayout->addWidget(contrinueButton);

        label->raise();
        movieLabel->raise();
        contrinueButton->raise();
        stopButton->raise();
        contrinueButton->raise();
        stopButton->raise();

        retranslateUi(about);

        QMetaObject::connectSlotsByName(about);
    } // setupUi

    void retranslateUi(QDialog *about)
    {
        about->setWindowTitle(QApplication::translate("about", "Dialog", 0));
        label->setText(QApplication::translate("about", "<html><head/><body><p><span style=\" font-size:24pt; color:#ff0000;\">Made by haoyi007!</span></p></body></html>", 0));
        movieLabel->setText(QString());
        stopButton->setText(QApplication::translate("about", "\345\201\234\346\255\242\346\222\255\346\224\276", 0));
        contrinueButton->setText(QApplication::translate("about", "\347\273\247\347\273\255\346\222\255\346\224\276", 0));
    } // retranslateUi

};

namespace Ui {
    class about: public Ui_about {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
