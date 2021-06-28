QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    farm_login.cpp \
    mainwindow.cpp \
    regisist.cpp

HEADERS += \
    ../sum/recorder-main/main.h \
    farm_login.h \
    mainwindow.h \
    regisist.h

FORMS += \
    farm_login.ui \
    mainwindow.ui \
    regisist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imag.qrc

DISTFILES += \
    ../build-farm_login-Desktop_Qt_5_12_11_MSVC2015_64bit-Debug/user.txt
