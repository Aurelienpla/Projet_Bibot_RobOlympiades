TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS += -L/usr/local/lib

LIBS += -lopencv_core -lopencv_highgui -lopencv_imgcodecs  -lopencv_imgproc  -lopencv_videoio
