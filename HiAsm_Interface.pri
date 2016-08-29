CONFIG += c++14
QT += core

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += $$files($$PWD/"entry/*.cpp", true)
HEADERS += $$files($$PWD/"entry/*.h", true)

SOURCES += $$files($$PWD/"cgt/*.cpp", true)
HEADERS += $$files($$PWD/"cgt/*.h", true)
SOURCES += $$files($$PWD/"scenemodel/*.cpp", true)
HEADERS += $$files($$PWD/"scenemodel/*.h", true)
SOURCES += $$files($$PWD/"package/*.cpp", true)
HEADERS += $$files($$PWD/"package/*.h", true)

#Подключаем логгер
include($$PWD/logger/logger.pri)
