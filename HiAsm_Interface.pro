TARGET = CodeGen
TEMPLATE = lib
QT += core
CONFIG += c++14 dll console

#ru Путь до пакетов HiAsm
HIASM_PACKAGES = "C:/Users/Admin/AppData/Roaming/HiAsm_AltBuild/Elements"

DEFINES += #CNET
#ru Копируем кодогенератор в интересующий пакет
contains(DEFINES, CNET){
    PACKAGE += $$HIASM_PACKAGES/CNET
} else {
    PACKAGE += $$HIASM_PACKAGES/delphi
}
DESTDIR += $$PACKAGE
DEFINES += HIASM_PACKAGE=\"\\\"$$PACKAGE\\\"\"

#ru Подключаем SceneModel
#DEFINES += SCENEMODEL

#ru Подключаем ProxyCgt
DEFINES += PROXYCGT

#ru Где сохраняется собранный кодогенератор
message(Build path: $$DESTDIR)

SOURCES += $$files("*.cpp", true)
HEADERS += $$files("*.h", true)

#Параметры логгера
DEFINES += ELPP_QT_LOGGING \
           ELPP_STL_LOGGING \
           ELPP_STRICT_SIZE_CHECK \
           ELPP_THREAD_SAFE \
           ELPP_MULTI_LOGGER_SUPPORT \
           ELPP_NO_DEFAULT_LOG_FILE
