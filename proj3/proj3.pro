#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T15:24:03
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = skyscrapers
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        skyscrapers.cpp \
    backtrack.cpp \
    skyscraperconfig.cpp \
    triad.cpp \
    wheelconfig.cpp \
    borderlayout.cpp \
    gridbutton.cpp

HEADERS  += skyscrapers.h \
    backtrack.h \
    skyscraperconfig.h \
    triad.h \
    wheelconfig.h \
    borderlayout.h \
    gridbutton.h

FORMS    +=

OTHER_FILES += \
    proj3.pro.user \
    input.1 \
    input.2 \
    input.3
