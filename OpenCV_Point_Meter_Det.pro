QT += core
QT += gui
QT += serialport
QT += texttospeech
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console

#openmp
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
LIBS += -lgomp -lpthread

TARGET = OpenCV_Point_Meter_Det
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    imagprocess.cpp \
    mtexttovoice.cpp

INCLUDEPATH += D:\opencv-build-zty411\install\include

LIBS += D:\opencv-build-zty411\install\x86\mingw\bin\libopencv_*.dll


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

FORMS +=

HEADERS += \
    imagprocess.h \
    circlefinder.h \
    onmouse.h \
    mtexttovoice.h
