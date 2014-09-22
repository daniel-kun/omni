TEMPLATE = vcapp
TARGET = omni-forge

CONFIG(debug, debug|release){
    DESTDIR = ./bin
    OBJECTS_DIR = debug/$$TARGET/.obj
    MOC_DIR = debug/$$TARGET/.moc
    RCC_DIR = debug/$$TARGET/.rcc
    UI_DIR = debug/$$TARGET/.ui
}

CONFIG(release, debug|release){
    DESTDIR = ./release
    OBJECTS_DIR = release/$$TARGET/.obj
    MOC_DIR = release/$$TARGET/.moc
    RCC_DIR = release/$$TARGET/.rcc
    UI_DIR = release/$$TARGET/.ui
}

INCLUDEPATH += ../interface
INCLUDEPATH += D:/Projects/thirdparty/boost_1_55_0
LIBPATH += D:/Projects/thirdparty/boost_1_55_0/stage/lib
LIBS += bin/omni-core.lib bin/omni-ui.lib

QT += core gui widgets

INCLUDEDIR = "../interface/omni/forge"
SOURCEDIR = "../source/omni/forge"
QMAKE_CXXFLAGS += /wd4251

# Input
HEADERS += $$INCLUDEDIR/mainwindow.hpp $$SOURCEDIR/sandbox.hpp
SOURCES += $$SOURCEDIR/mainwindow.cpp $$SOURCEDIR/main.cpp $$SOURCEDIR/sandbox.cpp

