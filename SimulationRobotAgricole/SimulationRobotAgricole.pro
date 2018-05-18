TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

QT += core gui

mac:LIBS += -framework GLUT
else:unix|win32:LIBS += -lglut -lGL -lGLU

SOURCES += main.cpp \
    drawing.cpp \
    ccorn.cpp \
    ccornfield.cpp \
    crobot.cpp \
    clidar.cpp \
    utils.cpp

HEADERS += \
    drawing.h \
    ccorn.h \
    ccornfield.h \
    crobot.h \
    clidar.h \
    utils.h
