#-------------------------------------------------
#
# Project created by QtCreator 2014-08-29T22:26:41
#
#-------------------------------------------------

QT       += core gui
QT +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GPMonitor
TEMPLATE = app


SOURCES += main.cpp \
    visualchart.cpp \
    monitorform.cpp \
    mainform.cpp \
    waveform.cpp \
    colorchart.cpp \
    settings.cpp \
    qdevicewatcher_linux.cpp \
    qdevicewatcher.cpp \
    qdevicechangeevent.cpp \
    passworddialog.cpp \
    resetdialog.cpp \
    calibratedialog.cpp

HEADERS  += \
    visualchart.h \
    monitorform.h \
    mainform.h \
    waveform.h \
    comdefs.h \
    colorchart.h \
    settings.h \
    IRCommand.h \
    qdevicewatcher_p.h \
    qdevicewatcher_global.h \
    qdevicewatcher.h \
    qdevicechangeevent.h \
    passworddialog.h \
    resetdialog.h \
    calibratedialog.h

win32 {
    SOURCES +=  serialport/win32/win_qextserialport.cpp \
        serialport/win32/qextserialbase.cpp

    HEADERS +=  serialport/win32/win_qextserialport.h \
        serialport/win32/qextserialbase.h

    CONFIG(debug, debug|release){
        LIBS += -lqwtd5
    }

    CONFIG(release, debug|release){
        LIBS += -lqwt5
    }

    INCLUDEPATH += "C:/QT/4.8.5/include/qwt"
}

unix {
    SOURCES += serialport/linux/qextserialport.cpp \
        serialport/linux/qextserialbase.cpp \
        serialport/linux/posix_qextserialport.cpp \
        serialport/linux/ManageSerialPort.cpp

    HEADERS += serialport/linux/qextserialport.h \
        serialport/linux/qextserialbase.h \
        serialport/linux/posix_qextserialport.h \
        serialport/linux/ManageSerialPort.h

    LIBS += -lqwt
    LIBS += -lQtXml
#    LIBS += -lQDeviceWatcher
    INCLUDEPATH += "/opt/qt-4.8.4-x11/include/qwt"
    INCLUDEPATH += "/opt/qt-4.8.4-x11/include/QtXml"
#    INCLUDEPATH +="/usr/lib"
#    INCLUDEPATH +="/sys/"
#    INCLUDEPATH +="/usr/include/linux"
#    INCLUDEPATH +="/usr/include/arm-linux-gnueabi/sys/"
}


FORMS    += \
    visualchart.ui \
    monitorform.ui \
    waveform.ui \
    colorchart.ui \
    settings.ui \
    mainform.ui \
    passworddialog.ui \
    resetdialog.ui \
    calibratedialog.ui

OTHER_FILES +=\

RESOURCES += \
    Rsc.qrc



