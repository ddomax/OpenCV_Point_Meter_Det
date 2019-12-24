QT += core
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = OpenCV_Point_Meter_Det
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    imagprocess.cpp
INCLUDEPATH += C:\opencv\build\include
#INCLUDEPATH += C:\opencv-build-static\install\include

#LIBS += C:\opencv-build\bin\libopencv_core411.dll
#LIBS += C:\opencv-build\bin\libopencv_highgui411.dll
#LIBS += C:\opencv-build\bin\libopencv_imgcodecs411.dll
#LIBS += C:\opencv-build\bin\libopencv_imgproc411.dll
#LIBS += C:\opencv-build\bin\libopencv_features2d411.dll
#LIBS += C:\opencv-build\bin\libopencv_calib3d411.dll

LIBS += C:\opencv-build-static\bin\opencv_videoio_ffmpeg411.dll

#LIBS += C:\opencv-build\bin\libade.dll
LIBS += C:\opencv-build\bin\libopencv_calib3d411.dll
LIBS += C:\opencv-build\bin\libopencv_core411.dll
LIBS += C:\opencv-build\bin\libopencv_dnn411.dll
LIBS += C:\opencv-build\bin\libopencv_features2d411.dll
LIBS += C:\opencv-build\bin\libopencv_flann411.dll
LIBS += C:\opencv-build\bin\libopencv_gapi411.dll
LIBS += C:\opencv-build\bin\libopencv_highgui411.dll
LIBS += C:\opencv-build\bin\libopencv_imgcodecs411.dll
LIBS += C:\opencv-build\bin\libopencv_imgproc411.dll
LIBS += C:\opencv-build\bin\libopencv_ml411.dll
LIBS += C:\opencv-build\bin\libopencv_objdetect411.dll
LIBS += C:\opencv-build\bin\libopencv_photo411.dll
LIBS += C:\opencv-build\bin\libopencv_stitching411.dll
#LIBS += C:\opencv-build\bin\libopencv_ts411.dll
LIBS += C:\opencv-build\bin\libopencv_video411.dll
LIBS += C:\opencv-build\bin\libopencv_videoio411.dll

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
    imagprocess.h
