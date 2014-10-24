#include <omni/ui/suggestion_text_edit.hpp>

omni::ui::suggestion_text_edit::suggestion_text_edit (QWidget * parent) :
    suggestion_text_edit (QString (), parent)
{
}

omni::ui::suggestion_text_edit::suggestion_text_edit (QString const & text, QWidget * parent) :
    QLineEdit (text, parent),
    _model (),
    _completer (& _model)
{
    connect (this, SIGNAL(textChanged(QString const &)), this, SLOT (showSuggestionsWhenTextChanged(QString const &)));
    _completer.setCompletionMode (QCompleter::UnfilteredPopupCompletion);
    _completer.setWidget (this);
    connect (& _completer, SIGNAL(activated(QString const &)), this, SLOT (acceptCompletion(QString const &)));
}

void omni::ui::suggestion_text_edit::showSuggestionsWhenTextChanged (QString const & text)
{
    std::vector <omni::core::input::syntax_suggestion> suggestions;
    emit suggestionsRequested (text, suggestions);
    _model.clear ();
    for (auto suggestion : suggestions) {
        _model.addSuggestion (suggestion);
    }
    _completer.complete ();
}

void omni::ui::suggestion_text_edit::acceptCompletion (QString const & text)
{
    disconnect (this, SIGNAL(textChanged(QString const &)), this, SLOT (showSuggestionsWhenTextChanged(QString const &)));
    setText (text);
    connect (this, SIGNAL(textChanged(QString const &)), this, SLOT (showSuggestionsWhenTextChanged(QString const &)));
    emit suggestionAccepted (_model.getSuggestion (text));
}

