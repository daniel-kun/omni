TEMPLATE = vclib
TARGET = omni-ui

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

INCLUDEPATH += ../interface "D:\Projects\thirdparty\boost_1_55_0"
LIBPATH += "D:\Projects\thirdparty\boost_1_55_0\stage\lib"
LIBS += bin/omni-core.lib

QT += core gui widgets

INCLUDEDIR = "../interface/omni/ui"
SOURCEDIR = "../source/omni/ui"
QMAKE_CXXFLAGS += /wd4251
DEFINES += omniui_BUILD_LIB

# Input
HEADERS += \
    $$INCLUDEDIR/blueprint.hpp \
    $$INCLUDEDIR/entity_base_widget.hpp \
    $$INCLUDEDIR/entity_placeholder_widget.hpp \
    $$INCLUDEDIR/entity_toggle_widget.hpp \
    $$INCLUDEDIR/entity_widget_provider.hpp \
    $$INCLUDEDIR/entity_widget_provider_base.hpp \
    $$INCLUDEDIR/flowlayout.hpp \
    $$INCLUDEDIR/generic_entity_editor.hpp \
    $$INCLUDEDIR/literal_expression_view.hpp \
    $$INCLUDEDIR/suggestion_list_model.hpp \
    $$INCLUDEDIR/suggestion_text_edit.hpp \
    $$INCLUDEDIR/syntax_input.hpp \
    $$INCLUDEDIR/tree_sort_filter_proxy_model.hpp \
    $$INCLUDEDIR/ui.hpp \
    $$INCLUDEDIR/variable_declaration_expression_view.hpp

SOURCES += \
    $$SOURCEDIR/blueprint.cpp \
    $$SOURCEDIR/entity_base_widget.cpp \
    $$SOURCEDIR/entity_placeholder_widget.cpp \
    $$SOURCEDIR/entity_toggle_widget.cpp \
    $$SOURCEDIR/entity_widget_provider.cpp \
    $$SOURCEDIR/flowlayout.cpp \
    $$SOURCEDIR/generic_entity_editor.cpp \
    $$SOURCEDIR/literal_expression_view.cpp \
    $$SOURCEDIR/suggestion_list_model.cpp \
    $$SOURCEDIR/suggestion_text_edit.cpp \
    $$SOURCEDIR/syntax_input.cpp \
    $$SOURCEDIR/tree_sort_filter_proxy_model.cpp \
    $$SOURCEDIR/ui.cpp \
    $$SOURCEDIR/variable_declaration_expression_view.cpp
