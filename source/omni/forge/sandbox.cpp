#include "sandbox.hpp"

#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/type.hpp>

#include <QKeyEvent>

omni::forge::entity_widget::entity_widget (QWidget * parent) :
    QWidget (parent)
{
}

std::shared_ptr <omni::core::model::entity> omni::forge::entity_widget::getEntity ()
{
    return std::shared_ptr <omni::core::model::entity> ();
}

void omni::forge::entity_widget::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    // nop
}

bool omni::forge::entity_edit_provider::keyPressEvent (QKeyEvent *)
{
    return false;
}

omni::forge::literal_expression_view::literal_expression_view (QWidget * parent) :
    entity_widget (parent),
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
    _literalEditProvider (),
    _literalView (_c, _literalEditProvider, this),
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


omni::forge::entity_edit_widget::entity_edit_widget (omni::core::context & context, entity_edit_provider & editProvider, QWidget * parent) :
    entity_widget (parent),
    _c (context),
    _editProvider (editProvider),
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
        _editWidget = _editProvider.createEditWidget (this, _c, *_viewWidget);
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
        _viewWidget = _editProvider.createViewWidget (this, _c, _editWidget.get ());
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
    if (! _editProvider.keyPressEvent (event)) {
        QWidget::keyPressEvent (event);
    }
}

std::unique_ptr <omni::forge::entity_widget> omni::forge::literal_edit_provider::createViewWidget (QWidget * parent, omni::core::context & context, entity_widget * editWidget)
{
    std::shared_ptr <omni::core::model::literal_expression> literal;
    if (editWidget != nullptr) {
        literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (editWidget->getEntity ());
    }
    auto viewWidget = std::make_unique <literal_expression_view> (parent);
    viewWidget->setLiteral (literal);
    return std::move (viewWidget);
}

std::unique_ptr <omni::forge::entity_widget> omni::forge::literal_edit_provider::createEditWidget (QWidget * parent, omni::core::context & context, entity_widget & viewWidget)
{
    auto result = std::make_unique <generic_entity_editor> (parent, viewWidget.getEntity ());
    result->setTextToEntityConverter ([&context] (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity) -> std::shared_ptr <omni::core::model::entity> {
        auto literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (originatingEntity);
        return omni::core::model::literal_expression::fromString (context, text, literal.get ());
    });
    result->setEntity (viewWidget.getEntity ());
    return std::move (result);
}

bool omni::forge::literal_edit_provider::keyPressEvent (QKeyEvent * event)
{
    if (std::isalnum (event->key (), std::locale (""))) {
        return true;
    } else {
        return false;
    }
}

omni::forge::generic_entity_editor::generic_entity_editor (QWidget * parent, std::shared_ptr <omni::core::model::entity> entity) :
    entity_widget (parent),
    _entity (entity),
    _layout (this),
    _edit (this)
{
    _layout.addWidget (& _edit);
    setFocusProxy (& _edit);
}

boost::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> omni::forge::generic_entity_editor::getTextToEntityConverter ()
{
    return _converter;
}

void omni::forge::generic_entity_editor::setTextToEntityConverter (boost::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> converter)
{
    _converter = converter;
}

std::shared_ptr <omni::core::model::entity> omni::forge::generic_entity_editor::getEntity ()
{
    if (_converter) {
        return _converter (_edit.text ().toStdString (), _entity);
    } else {
        return _entity;
    }
}

void omni::forge::generic_entity_editor::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    _entity = entity;
    auto literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (entity);
    _edit.setText (QString::fromStdString (literal->toString (false)));
}
