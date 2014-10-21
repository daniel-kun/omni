#include <omni/ui/literal_expression_view.hpp>
#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/type.hpp>

omni::ui::literal_expression_view::literal_expression_view (QWidget * parent) :
    entity_base_widget (parent),
    _layout (this),
    _valueLabel (this),
    _typeLabel (this),
    _literalExpression ()
{
    setAutoFillBackground (true);
    _layout.addWidget (& _valueLabel, 0, Qt::AlignRight);
    _layout.addWidget (& _typeLabel);
}

std::shared_ptr <omni::core::model::entity> omni::ui::literal_expression_view::getEntity () 
{
    return getLiteral ();
}

void omni::ui::literal_expression_view::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    setLiteral (std::dynamic_pointer_cast <omni::core::model::literal_expression> (entity));
}

void omni::ui::literal_expression_view::setLiteral (std::shared_ptr <omni::core::model::literal_expression> literalExpression)
{
    _literalExpression = literalExpression;
    if (_literalExpression) {
        _literalValueChangedConnection = _literalExpression->connectValueChanged ([this] (omni::core::model::literal_expression &, boost::any oldValue, boost::any newValue) -> void {
            updateContent ();
        });
    }
    updateContent ();
}

std::shared_ptr <omni::core::model::literal_expression> omni::ui::literal_expression_view::getLiteral ()
{
    return _literalExpression;
}

void omni::ui::literal_expression_view::updateContent ()
{
    if (_literalExpression) {
        _valueLabel.setText (QString::fromStdString (_literalExpression->toString (false)));
        _typeLabel.setText (QString::fromStdString (_literalExpression->getType ()->toString (false)));
    } else {
        _valueLabel.setText (QString ());
        _typeLabel.setText (QString ());
    }
}
