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

TEMPLATE = vclib
TARGET = omni-ui
INCLUDEPATH += ../interface "D:\Projects\thirdparty\boost_1_55_0"
LIBPATH += "D:\Projects\thirdparty\boost_1_55_0\stage\lib"
LIBS += bin/omni-core.lib

QT += core gui widgets

INCLUDEDIR = "../interface/omni/ui"
SOURCEDIR = "../source/omni/ui"
QMAKE_CXXFLAGS += /wd4251
DEFINES += omniui_BUILD_LIB

# Input
HEADERS += $$INCLUDEDIR/flowlayout.hpp $$INCLUDEDIR/syntax_input.hpp $$INCLUDEDIR/suggestion_list_model.hpp $$INCLUDEDIR/suggestion_text_edit.hpp $$INCLUDEDIR/blueprint.hpp $$INCLUDEDIR/ui.hpp $$INCLUDEDIR/entity_base_widget.hpp $$INCLUDEDIR/generic_entity_editor.hpp
SOURCES += $$SOURCEDIR/flowlayout.cpp $$SOURCEDIR/syntax_input.cpp $$SOURCEDIR/suggestion_list_model.cpp $$SOURCEDIR/suggestion_text_edit.cpp $$SOURCEDIR/blueprint.cpp $$SOURCEDIR/ui.cpp $$SOURCEDIR/entity_base_widget.cpp $$SOURCEDIR/generic_entity_editor.cpp

