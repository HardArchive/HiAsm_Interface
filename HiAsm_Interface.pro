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

SOURCES += $$files("*.cpp", true)
HEADERS += $$files("*.h", true)

#Параметры логгера
DEFINES += ELPP_QT_LOGGING \
           ELPP_STL_LOGGING \
           ELPP_STRICT_SIZE_CHECK \
           ELPP_THREAD_SAFE \
           ELPP_MULTI_LOGGER_SUPPORT \
           ELPP_NO_DEFAULT_LOG_FILE
