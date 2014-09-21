#include "sandbox.hpp"

#include <omni/ui/generic_entity_editor.hpp>

#include <omni/core/invalid_argument_error.hpp>
#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/type.hpp>

#include <QKeyEvent>

std::map <std::string, omni::forge::
    entity_widget_provider> s_widgetProviderRegistry = {
        { "literal_expression", omni::forge::entity_widget_provider (
            [] (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget) -> std::unique_ptr <omni::ui::entity_base_widget> {
                std::shared_ptr <omni::core::model::literal_expression> literal;
                if (editWidget != nullptr) {
                    literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (editWidget->getEntity ());
                }
                auto viewWidget = std::make_unique <omni::forge::literal_expression_view> (parent);
                viewWidget->setLiteral (literal);
                return std::move (viewWidget);
            },
            [] (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget) -> std::unique_ptr <omni::ui::entity_base_widget> {
                auto result = std::make_unique <omni::ui::generic_entity_editor> (parent, viewWidget.getEntity ());
                result->setTextToEntityConverter ([&context] (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity) -> std::shared_ptr <omni::core::model::entity> {
                    auto literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (originatingEntity);
                    return omni::core::model::literal_expression::fromString (context, text, literal.get ());
                });
                result->setEntity (viewWidget.getEntity ());
                return std::move (result);
            },
            std::function <bool (QKeyEvent * event)> ())
        }
};

std::unique_ptr <omni::ui::entity_base_widget> omni::forge::entity_widget_provider::createViewWidget (std::string entityType, QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)
{
    auto iterator = s_widgetProviderRegistry.find (entityType);
    if (iterator != s_widgetProviderRegistry.end ()) {
        return iterator->second.createViewWidget (parent, context, editWidget);
    } else {
        throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "entityType", "An entity \"" + entityType + "\" was not found.");
    }
}

std::unique_ptr <omni::ui::entity_base_widget> omni::forge::entity_widget_provider::createEditWidget (std::string entityType, QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)
{
    auto iterator = s_widgetProviderRegistry.find (entityType);
    if (iterator != s_widgetProviderRegistry.end ()) {
        return iterator->second.createEditWidget (parent, context, viewWidget);
    } else {
        throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "entityType", "An entity \"" + entityType + "\" was not found.");
    }
}


omni::forge::entity_widget_provider::entity_widget_provider (
    std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)> viewCreator,
    std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)> editCreator,
    std::function <bool (QKeyEvent * event)> keyHandler) :
    _viewCreator (viewCreator),
    _editCreator (editCreator),
    _keyHandler (keyHandler)
{
}

void omni::forge::entity_widget_provider::setViewWidgetCreator (std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)> creator)
{
    _viewCreator = creator;
}

void omni::forge::entity_widget_provider::setEditWidgetCreator (std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)> creator)
{
    _editCreator = creator;
}

void omni::forge::entity_widget_provider::setKeyPressHandler (std::function <bool (QKeyEvent * event)> keyHandler)
{
    _keyHandler = keyHandler;
}

std::unique_ptr <omni::ui::entity_base_widget> omni::forge::entity_widget_provider::createViewWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)
{
    return _viewCreator (parent, context, editWidget);
}

std::unique_ptr <omni::ui::entity_base_widget> omni::forge::entity_widget_provider::createEditWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)
{
    return _editCreator (parent, context, viewWidget);
}

bool omni::forge::entity_widget_provider::keyPressEvent (QKeyEvent * event)
{
    return _keyHandler (event);
}

omni::forge::literal_expression_view::literal_expression_view (QWidget * parent) :
    entity_base_widget (parent),
    _layout (this),
    _valueLabel (this),
    _typeLabel (this),
    _literalExpression ()
{
    setAutoFillBackground (true);
    setFocusPolicy (Qt::StrongFocus);
    _layout.addWidget (& _valueLabel, 0, Qt::AlignRight);
    _layout.addWidget (& _typeLabel);
}

std::shared_ptr <omni::core::model::entity> omni::forge::literal_expression_view::getEntity () 
{
    return getLiteral ();
}

void omni::forge::literal_expression_view::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    setLiteral (std::dynamic_pointer_cast <omni::core::model::literal_expression> (entity));
}

void omni::forge::literal_expression_view::setLiteral (std::shared_ptr <omni::core::model::literal_expression> literalExpression)
{
    _literalExpression = literalExpression;
    if (_literalExpression) {
        _literalValueChangedConnection = _literalExpression->connectValueChanged ([this] (omni::core::model::literal_expression &, boost::any oldValue, boost::any newValue) -> void {
            updateContent ();
        });
    }
    updateContent ();
}

std::shared_ptr <omni::core::model::literal_expression> omni::forge::literal_expression_view::getLiteral ()
{
    return _literalExpression;
}

void omni::forge::literal_expression_view::focusInEvent (QFocusEvent * event)
{
    QWidget::focusInEvent (event);
    QPalette pal;
    pal.setBrush (QPalette::Background, Qt::red);
    setPalette (pal);
}

void omni::forge::literal_expression_view::focusOutEvent (QFocusEvent * event)
{
    QWidget::focusOutEvent (event);
    QPalette pal;
    setPalette (pal);
}

void omni::forge::literal_expression_view::updateContent ()
{
    if (_literalExpression) {
        _valueLabel.setText (QString::fromStdString (_literalExpression->toString (false)));
        _typeLabel.setText (QString::fromStdString (_literalExpression->getType ()->toString (false)));
    } else {
        _valueLabel.setText (QString ());
        _typeLabel.setText (QString ());
    }
}

omni::forge::sandbox::sandbox () :
    QWidget (),
    _c (),
    _m (_c, "forge-sandbox"),
    _layout (this),
    _literalView (_c, "literal_expression", this),
    _changeLiteralValueButton (this),
    _changeLiteralTypeButton (this)
{
    _layout.addWidget (& _literalView);
    _layout.addWidget (& _changeLiteralValueButton);
    _layout.addWidget (& _changeLiteralTypeButton);
    _changeLiteralValueButton.setText ("Double value");
    _changeLiteralTypeButton.setText ("Toggle types unsigned int/signed byte");
    //connect (& _changeLiteralValueButton, SIGNAL (clicked(bool)), SLOT (changeLiteralValue()));
    connect (& _changeLiteralTypeButton, SIGNAL (clicked(bool)), SLOT (changeLiteralType()));
    _literalView.connect (& _changeLiteralValueButton, SIGNAL (clicked(bool)), SLOT (toggleViewMode()));

    auto literalExpression = std::make_shared <omni::core::model::builtin_literal_expression <unsigned int>> (_c, 42);
    _literalView.setEntity (literalExpression);
}

void omni::forge::sandbox::changeLiteralValue ()
{
}

void omni::forge::sandbox::changeLiteralType ()
{
}

omni::forge::entity_edit_widget::entity_edit_widget (omni::core::context & context, std::string entityType, QWidget * parent) :
    entity_base_widget (parent),
    _c (context),
    _entityType (entityType),
    _toggleAction ("Test", this),
    _layout (this),
    _entity (),
    _viewWidget (),
    _editWidget ()
{
    _toggleAction.setShortcut (QKeySequence (Qt::Key_Return));
    _toggleAction.setShortcutContext (Qt::WidgetWithChildrenShortcut);
    addAction (& _toggleAction);
    connect (& _toggleAction, SIGNAL(triggered()), SLOT (toggleViewMode()));
    toggleViewMode ();
}

std::shared_ptr <omni::core::model::entity> omni::forge::entity_edit_widget::getEntity ()
{
    if (_viewWidget) {
        return _viewWidget->getEntity ();
    } else if (_editWidget) {
        return _editWidget->getEntity ();
    } else {
        return std::shared_ptr <omni::core::model::entity> ();
    }
}

void omni::forge::entity_edit_widget::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    if (_viewWidget) {
        _viewWidget->setEntity (entity);
    } else if (_editWidget) {
        _editWidget->setEntity (entity);
    }
}

omni::forge::entity_edit_widget::Mode omni::forge::entity_edit_widget::currentViewMode ()
{
    if (_viewWidget) {
        return Mode::m_view;
    } else {
        return Mode::m_edit;
    }
}

omni::forge::entity_edit_widget::Mode omni::forge::entity_edit_widget::toggleViewMode ()
{
    if (_viewWidget) {
        // Go into edit mode:
        bool hadFocus = hasFocus () || _viewWidget->hasFocus ();
        _editWidget = entity_widget_provider::createEditWidget (_entityType, this, _c, *_viewWidget);
        _layout.addWidget (_editWidget.get ());
        _viewWidget.reset ();
        if (hadFocus) {
            _editWidget->setFocus (Qt::TabFocusReason);
        }
        return Mode::m_edit;
    } else {
        // Accept input, go into view mode:
        bool hadFocus;
        if (_editWidget) {
            hadFocus = hasFocus () || _editWidget->hasFocus ();
        } else {
            hadFocus = hasFocus ();
        }
        _viewWidget = entity_widget_provider::createViewWidget (_entityType, this, _c, _editWidget.get ());
        _editWidget.reset ();
        _layout.addWidget (_viewWidget.get ());
        if (hadFocus) {
            _viewWidget->setFocus (Qt::TabFocusReason);
        }
        return Mode::m_view;
    }
}

void omni::forge::entity_edit_widget::keyPressEvent (QKeyEvent * event)
{
/*
    if (! _editProvider.keyPressEvent (event)) {
        QWidget::keyPressEvent (event);
    }
*/
}

/*
bool omni::forge::literal_edit_provider::keyPressEvent (QKeyEvent * event)
{
    if (std::isalnum (event->key (), std::locale (""))) {
        return true;
    } else {
        return false;
    }
}
*/

