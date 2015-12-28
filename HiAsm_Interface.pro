TARGET = CodeGen
TEMPLATE = lib
QT += core
CONFIG += c++14 dll

#ru Путь до пакетов HiAsm
HIASM_PACKAGES = "C:/Users/Admin/AppData/Roaming/HiAsm_AltBuild/Elements"

#DESTDIR += $$HIASM_PACKAGES/CNET
DESTDIR += $$HIASM_PACKAGES/delphi

#ru Подключаем SceneModel
#DEFINES += SCENEMODEL

#ru Подключаем ProxyCgt
#DEFINES += PROXYCGT

SOURCES += $$files("cgt/*.cpp", true)
HEADERS += $$files("cgt/*.h", true)
SOURCES += $$files("scenemodel/*.cpp", true)
HEADERS += $$files("scenemodel/*.h", true)
SOURCES += $$files("entry/*.cpp", true)
HEADERS += $$files("entry/*.h", true)
SOURCES += $$files("package/*.cpp", true)
HEADERS += $$files("package/*.h", true)

#Подключаем логгер
include(logger/logger.pri)
