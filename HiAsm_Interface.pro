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

#ru Подключаем SceneModel
DEFINES += SCENEMODEL

#ru Подключаем ProxyCgt
DEFINES += PROXYCGT

#ru Где сохраняется собранный кодогенератор
message(Build path: $$DESTDIR)

SOURCES += $$files("*.cpp", true)
HEADERS += $$files("*.h", true)

