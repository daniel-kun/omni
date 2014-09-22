#include "sandbox.hpp"

#include <omni/core/model/builtin_literal_expression.hpp>

#include <omni/ui/entity_widget_provider.hpp>

omni::forge::sandbox::sandbox () :
    QWidget (),
    _c (),
    _m (_c, "forge-sandbox"),
    _layout (this),
    _literalView (_c, omni::ui::entity_widget_provider::getProvider ("literal_expression"), this)
{
    _layout.addWidget (& _literalView);

    auto literalExpression = std::make_shared <omni::core::model::builtin_literal_expression <unsigned int>> (_c, 42);
    _literalView.setEntity (literalExpression);
}
