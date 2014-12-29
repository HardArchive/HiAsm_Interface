TARGET = CodeGen
TEMPLATE = lib

QT += core

CONFIG += c++14

DEFINES += BUILDING_DLL

#DESTDIR += D:/MyProgs/HiAsm_AltBuild/Elements/CNET
DESTDIR += D:/MyProgs/HiAsm_AltBuild/Elements/delphi

HEADERS += \
    CGTShare.h \
    global.h \
    element.h \
    cgtsharewrapper.h \
    maincontainer.h \
    point.h \
    property.h

SOURCES += \
    main.cpp \
    element.cpp \
    cgtsharewrapper.cpp \
    maincontainer.cpp \
    point.cpp \
    property.cpp

DISTFILES +=
