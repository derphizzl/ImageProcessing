#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T21:33:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessing_UI
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mainworker.cpp \
    Filter.cpp \
    Gradient.cpp \
    HarrisCorners.cpp \
    Helper.cpp \
    HoughLines.cpp \
    Corners.cpp

HEADERS  += widget.h \
    mainworker.h \
    Filter.hpp \
    Gradient.hpp \
    HarrisCorners.hpp \
    Helper.hpp \
    HoughLines.hpp \
    CannyEdge.hpp \
    Corners.hpp

FORMS    += widget.ui

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

CONFIG( release, debug|release ) {
    LIBS += -L$$PWD/../../../../usr/local/lib/               \
        -lopencv_core310d                                    \
        -lopencv_imgproc310d                                 \
        -lopencv_features2d310d                              \
        -lopencv_calib3d310d                                 \
        -lopencv_flann310d                                   \
        -lopencv_highgui310d                                 \
        -lopencv_imgcodecs310d                               \
        -lopencv_imgproc310d                                 \
        -lopencv_ml310d                                      \
        -lopencv_objdetect310d                               \
        -lopencv_photo310d                                   \
        -lopencv_shape310d                                   \
        -lopencv_stitching310d                               \
        -lopencv_superres310d                                \
        -lopencv_ts310d                                      \
        -lopencv_video310d                                   \
        -lopencv_videoio310d                                 \
        -lopencv_videostab310d

    }
    else {
    LIBS += -L$$PWD/../../../../usr/local/lib/           \
        -lopencv_core                                    \
        -lopencv_imgproc                                 \
        -lopencv_features2d                              \
        -lopencv_calib3d                                 \
        -lopencv_flann                                   \
        -lopencv_highgui                                 \
        -lopencv_imgcodecs                               \
        -lopencv_imgproc                                 \
        -lopencv_ml                                      \
        -lopencv_objdetect                               \
        -lopencv_photo                                   \
        -lopencv_shape                                   \
        -lopencv_stitching                               \
        -lopencv_superres                                \
#        -lopencv_ts                                      \
        -lopencv_video                                   \
        -lopencv_videoio                                 \
        -lopencv_videostab
}






