#ifndef OMNI_UI_SUGGESTION_TEXT_EDIT_HPP
#define OMNI_UI_SUGGESTION_TEXT_EDIT_HPP

#include <omni/ui/ui.hpp>
#include <omni/ui/suggestion_list_model.hpp>

#include <QLineEdit>
#include <QCompleter>

namespace omni {
namespace core {
namespace input {
class syntax_suggestion;
}
}
}

namespace omni {
namespace ui {

class OMNI_UI_API suggestion_text_edit : public QLineEdit {
    Q_OBJECT

public:
    explicit suggestion_text_edit (QWidget * parent = 0);
    explicit suggestion_text_edit (QString const & text, QWidget * parent = 0);

Q_SIGNALS:
    void suggestionsRequested (QString const & text, std::vector <omni::core::input::syntax_suggestion> & suggestions);    
    void suggestionAccepted (omni::core::input::syntax_suggestion const & suggestion);

private slots:
    void showSuggestionsWhenTextChanged (QString const & text);
    void acceptCompletion (QString const & text);

private:
    suggestion_list_model _model;
    QCompleter _completer;
};

}
}

#endif // include guard
