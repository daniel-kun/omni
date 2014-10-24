#ifndef OMNI_UI_SYNTAX_INPUT_HPP
#define OMNI_UI_SYNTAX_INPUT_HPP

#include <omni/ui/ui.hpp>
#include <omni/ui/flowlayout.hpp>

#include <omni/core/input/syntax_suggestion.hpp>

#include <QWidget>

namespace omni {
namespace core {
namespace input {
class syntax_element;
}
}
}

namespace omni {
namespace ui {

/**
syntax_input is an control that can populate an omni::core model from user input via an omni::core::input::syntax_element.
**/
class OMNI_UI_API syntax_input : public QWidget {
    Q_OBJECT

public:
    syntax_input (QWidget * parent, omni::core::input::syntax_element & syntaxElement);

protected:

private slots:
    void provideSuggestions (QString const & text, std::vector <omni::core::input::syntax_suggestion> & suggestions);
    void acceptSuggestion (omni::core::input::syntax_suggestion suggestion);

private:
    void addRootTextEdit ();
    void clearWidgets ();

    omni::core::input::syntax_element & _syntaxElement;
    FlowLayout _layout;
    std::list <std::shared_ptr <QWidget>> _widgets;
};


}
}

#endif // include guard
