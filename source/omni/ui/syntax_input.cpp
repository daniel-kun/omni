#include <omni/ui/syntax_input.hpp>
#include <omni/ui/suggestion_text_edit.hpp>

#include <omni/core/input/syntax_element.hpp>
#include <omni/core/input/syntax_template_element.hpp>
#include <omni/core/input/regex_template_element.hpp>
#include <omni/core/input/variable_template_element.hpp>
#include <omni/core/input/fixed_template_element.hpp>
#include <omni/core/input/repeater_template_element.hpp>
#include <omni/core/input/template_visitor.hpp>

#include <QLabel>

omni::ui::syntax_input::syntax_input (QWidget * parent, omni::core::input::syntax_element & syntaxElement) :
    QWidget (parent),
    _syntaxElement (syntaxElement),
    _layout (this, 0, 0, 0),
    _widgets ()
{
    //setContentsMargins (QMargins (5, 5, 5, 5));
    _layout.setMargin (0);
    //QPalette pal;
    //pal.setBrush (QPalette::Background, Qt::red);
    // fromRgb (0xE3, 0xE3, 0xE5)
    //setPalette (pal);
    //setAutoFillBackground (true);

    addRootTextEdit ();
}

void omni::ui::syntax_input::addRootTextEdit ()
{
    auto textEdit = std::make_shared <suggestion_text_edit> (this);
    connect (
        textEdit.get (),
        SIGNAL (suggestionsRequested(QString const &, std::vector <omni::core::input::syntax_suggestion> &)),
        this,
        SLOT (provideSuggestions(QString const &, std::vector <omni::core::input::syntax_suggestion> &)));
    connect (
        textEdit.get (),
        SIGNAL (suggestionAccepted (omni::core::input::syntax_suggestion)),
        this,
        SLOT (acceptSuggestion (omni::core::input::syntax_suggestion)));
    _layout.addWidget (textEdit.get ());
    _widgets.push_back (textEdit);
}

void omni::ui::syntax_input::provideSuggestions (QString const & text, std::vector <omni::core::input::syntax_suggestion> & suggestions)
{
    std::vector <omni::core::input::syntax_suggestion> newSuggestions = _syntaxElement.suggest (text.toStdString ());
    suggestions.insert (suggestions.end (), newSuggestions.begin (), newSuggestions.end ());
}

void omni::ui::syntax_input::clearWidgets ()
{
    for (auto widget : _widgets) {
        _layout.removeWidget (widget.get ());
        widget->setParent (nullptr);
    }
    _widgets.clear ();
}

void omni::ui::syntax_input::acceptSuggestion (omni::core::input::syntax_suggestion suggestion)
{
    clearWidgets ();

    using namespace omni::core::input;

    class template_create_widget_visitor : public template_visitor {
    public:
        template_create_widget_visitor (
            QWidget & parent,
            QLayout & layout,
            std::list <std::shared_ptr <QWidget>> & widgets) :
            _parent (parent),
            _layout (layout),
            _widgets (widgets)
        {
        }

        void visitSyntaxTemplateElement     (syntax_template_element & syntaxTemplateElement) override
        {
            auto textEdit = std::make_shared <syntax_input> (& _parent, * syntaxTemplateElement.getSyntaxElement ());
            _layout.addWidget (textEdit.get ());
            _widgets.push_back (textEdit);
        }

        void visitVariableTemplateElement   (variable_template_element &) override
        {
            auto textEdit = std::make_shared <QLineEdit> (& _parent);
            textEdit->setPlaceholderText ("(variable)");
            _layout.addWidget (textEdit.get ());
            _widgets.push_back (textEdit);
        }

        void visitRegexTemplateElement      (regex_template_element &) override
        {
            auto textEdit = std::make_shared <QLineEdit> (& _parent);
            textEdit->setPlaceholderText ("(regex)");
            _layout.addWidget (textEdit.get ());
            _widgets.push_back (textEdit);
        }

        void visitFixedTemplateElement      (fixed_template_element & element) override
        {
            auto label = std::make_shared <QLabel> (& _parent);
            label->setText (QString::fromStdString (element.getText ()));
            _layout.addWidget (label.get ());
            _widgets.push_back (label);
        }

        void visitRepeaterTemplateElement   (repeater_template_element &) override
        {
            auto textEdit = std::make_shared <QLineEdit> (& _parent);
            textEdit->setPlaceholderText ("(repeater)");
            _layout.addWidget (textEdit.get ());
            _widgets.push_back (textEdit);
        }

    private:
        QWidget & _parent;
        QLayout & _layout;
        std::list <std::shared_ptr <QWidget>> & _widgets;
    } visitor (* this, _layout, _widgets);

    syntax_element & e = * suggestion.syntaxElement;
    for (std::size_t i = 0; i < e.templateElementCount (); ++i) {
        template_element & t = * e.templateElementAt (i);
        t.visit (visitor);
    }
}
