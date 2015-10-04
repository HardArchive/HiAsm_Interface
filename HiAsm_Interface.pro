TARGET = CodeGen
TEMPLATE = lib
QT += core
CONFIG += c++14

#ru Путь до пакетов HiAsm
HIASM_PACKAGES = "C:/Users/Admin/AppData/Roaming/HiAsm_AltBuild/Elements"

#ru Копируем кодогенератор в интересующий пакет
contains(DEFINES, CNET){
    PACKAGE += $$HIASM_PACKAGES/CNET
} else {
    PACKAGE += $$HIASM_PACKAGES/delphi
}
DESTDIR += $$PACKAGE
DEFINES += HIASM_PACKAGE=\"\\\"$$PACKAGE\\\"\"

#ru Подключаем DataCollector
DEFINES += DATACOLLECTOR

#ru Подключаем ProxyCgt
DEFINES += PROXYCGT

#ru Где сохраняется собранный кодогенератор
message(Build path: $$DESTDIR)

HEADERS += \
    CGTShare.h \
    global.h \
    element.h \
    point.h \
    property.h \
    proxycgt.h \
    cgt.h \
    container.h \
    datacollector.h

SOURCES += \
    main.cpp \
    element.cpp \
    point.cpp \
    property.cpp \
    proxycgt.cpp \
    cgt.cpp \
    container.cpp \
    datacollector.cpp

