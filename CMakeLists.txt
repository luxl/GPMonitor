cmake_minimum_required(VERSION 3.6)
project(GPMonitor)

#Qt
set(QT_HOME "/home/allen/Programs/Qt5.6.1/5.6/gcc_64")
set(CMAKE_PREFIX_PATH ${QT_HOME})
SET(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_AUTORCC on)

#Qwt
set(QWT_ROOT "/usr/local/qwt-6.1.3")
set(QWT_INCLUDE_DIR ${QWT_ROOT}/include)
set(QWT_LIB ${QWT_ROOT}/lib)
include_directories(${QWT_INCLUDE_DIR})
link_directories(${QWT_LIB})
FILE(GLOB_RECURSE SERIAL ${PROJECT_ROOT}/serialport/linux/*.c* ${PROJECT_ROOT}/serialport/linux/*.h*) # serial port
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 REQUIRED Gui Core Widgets UiTools Xml Network)

set(SOURCE_FILES
    calibratedialog.cpp
    calibratedialog.h
    colorchart.cpp
    colorchart.h
    comdefs.h
    IRCommand.h
    main.cpp
    mainform.cpp
    mainform.h
    monitorform.cpp
    monitorform.h
    passworddialog.cpp
    passworddialog.h
#    promptform.cpp
#    promptform.h
    qdevicechangeevent.cpp
    qdevicechangeevent.h
    qdevicewatcher.cpp
    qdevicewatcher.h
    qdevicewatcher_global.h
    qdevicewatcher_linux.cpp
    qdevicewatcher_p.h
    resetdialog.cpp
    resetdialog.h
    settings.cpp
    settings.h
    visualchart.cpp
    visualchart.h
    waveform.cpp
    waveform.h
    ${SERIAL})

add_executable(GPMonitor ${SOURCE_FILES} Rsc.qrc)
target_link_libraries(GPMonitor Qt5::Core Qt5::Widgets Qt5::Gui Qt5::UiTools Qt5::Xml Qt5::Network qwt)