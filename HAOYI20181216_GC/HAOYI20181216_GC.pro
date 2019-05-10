#-------------------------------------------------
#
# Project created by QtCreator 2017-08-09T20:48:55
#
#-------------------------------------------------
QT       += core gui webkitwidgets webkit
QT       += serialport
QT += printsupport
QT += multimedia

CONFIG  += qaxcontainer
CONFIG+=thread

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HAOYI20170809_GC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        thread.cpp \
    radiatrueshow.cpp\
    qcustomplot.cpp \
    execelengin1.cpp \
    myspeed.cpp\
    about.cpp
HEADERS  += mainwindow.h\
        thread.h \
    execelengine1.h \
    radiatrueshow.h\
    qcustomplot.h \
    myspeed.h\
    about.h

FORMS    += mainwindow.ui \
    radiatrueshow.ui \
    about.ui
RC_FILE = myapp.rc  //图标添加网址：http://blog.sina.com.cn/s/blog_71fa0df501011xrk.html

RESOURCES += \
    pic.qrc
