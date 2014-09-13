CONFIG(debug, debug|release){
    DESTDIR = ./bin
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui
}

CONFIG(release, debug|release){
    DESTDIR = ./release
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui
}

TEMPLATE = vcapp
TARGET = omni-forge
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

