#include "sandbox.hpp"

#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/type.hpp>

omni::forge::literal_expression_view::literal_expression_view (QWidget * parent) :
    QWidget (parent),
    _layout (this),
    _valueLabel (this),
    _typeLabel (this),
    _literalExpression ()
{
    _layout.addWidget (& _valueLabel, 0, Qt::AlignRight);
    _layout.addWidget (& _typeLabel);
}

void omni::forge::literal_expression_view::setLiteral (std::shared_ptr <omni::core::model::literal_expression> literalExpression)
{
    _literalExpression = literalExpression;
    _literalValueChangedConnection = _literalExpression->connectValueChanged ([this] (omni::core::model::literal_expression &, boost::any oldValue, boost::any newValue) -> void {
        updateContent ();
    });
    updateContent ();
}

std::shared_ptr <omni::core::model::literal_expression> omni::forge::literal_expression_view::getLiteral ()
{
    return _literalExpression;
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
    _layout (this),
    _literalView (this),
    _changeLiteralValueButton (this),
    _c (),
    _m (_c, "forge-sandbox")
{
    _layout.addWidget (& _literalView);
    _layout.addWidget (& _changeLiteralValueButton);
    _changeLiteralValueButton.setText ("Change value");
    connect (& _changeLiteralValueButton, SIGNAL (clicked(bool)), SLOT (changeLiteralValue()));

    auto literalExpression = std::make_shared <omni::core::model::builtin_literal_expression <int>> (_c, 42);
    _literalView.setLiteral (literalExpression);
}

void omni::forge::sandbox::changeLiteralValue ()
{
    auto literalExpr = std::dynamic_pointer_cast <omni::core::model::builtin_literal_expression <int>> (_literalView.getLiteral ());
    literalExpr->setValue (literalExpr->getValue () + literalExpr->getValue ());
}
