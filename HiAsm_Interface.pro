TARGET = CodeGen
TEMPLATE = lib
QT += core
CONFIG += c++14

#ru Путь до пакетов HiAsm
HIASM_PACKAGES = "D:/MyProgs/HiAsm_AltBuild/Elements"

#ru Копируем кодогенератор в интересующий пакет
contains(DEFINES, CNET){
    DESTDIR += $$HIASM_PACKAGES/"CNET"
} else {
    DESTDIR += $$HIASM_PACKAGES/"delphi"
}

#ru Где сохраняется собранный кодогенератор
message(Build path: $$DESTDIR)

HEADERS += \
    CGTShare.h \
    global.h \
    element.h \
    maincontainer.h \
    point.h \
    property.h \
    proxycgt.h \
    cgt.h

SOURCES += \
    main.cpp \
    element.cpp \
    maincontainer.cpp \
    point.cpp \
    property.cpp \
    proxycgt.cpp \
    cgt.cpp

