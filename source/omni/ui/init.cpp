#include <omni/ui/init.hpp>
#include <omni/ui/ui_meta_extension.hpp>
#include <omni/ui/literal_expression_view.hpp>
#include <omni/ui/variable_declaration_expression_view.hpp>
#include <omni/ui/entity_widget_provider.hpp>

#include <omni/core/model/entity.hpp>
#include <omni/core/model/meta_info.hpp>
#include <omni/core/model/external_function.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/parameter.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/function_call_expression.hpp>
#include <omni/core/model/variable_assignment_expression.hpp>
#include <omni/core/model/binary_operator_expression.hpp>
#include <omni/core/model/bitcast_expression.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/variable_expression.hpp>
#include <omni/core/model/if_statement.hpp>
#include <omni/core/model/return_statement.hpp>
#include <omni/core/model/while_statement.hpp>
#include <omni/core/model/do_while_statement.hpp>

#include <memory>

namespace {
// Creator functions:

std::unique_ptr <omni::ui::entity_base_widget> createBuiltinLiteralExpressionView (omni::core::context                       & context,
                                                                                   omni::core::model::module                 &,
                                                                                   QWidget                                   * parent,
                                                                                   std::shared_ptr <omni::core::model::entity> entity)
{
    auto result = std::make_unique <omni::ui::entity_toggle_widget> (context, omni::ui::entity_widget_provider::getProvider ("literal_expression"), parent);
    result->setEntity (entity);
    return std::move (result);
}

std::unique_ptr <omni::ui::entity_base_widget> createVariableDeclarationExpression (omni::core::context       & context,
                                                                                    omni::core::model::module & module,
                                                                                    QWidget                   * parent,
                                                                                    std::shared_ptr <omni::core::model::entity> entity)
{
    auto result = std::make_unique <omni::ui::variable_declaration_expression_view> (context, module, parent);
    result->setEntity (entity);
    return std::move (result);
}

// Helper functions:
template <typename T>
void setUiMeta (omni::ui::ui_meta_extension::CreateViewWidgetFunction viewWidgetCreator)
{
    auto & meta = T::getStaticMetaInfo ();
    meta.setExtension ("omni.ui", std::make_shared <omni::ui::ui_meta_extension> (viewWidgetCreator));
}

}

/*
type
module

[ ] external_function
[ ] function
[ ] parameter
[ ] block
[ ] function_call_expression
[ ] variable_assignment_expression
[ ] binary_operator_expression
[ ] bitcast_expression
[ ] builtin_literal_expression
[ ] variable_declaration_expression
[ ] variable_expression
[ ] if_statement
[ ] return_statement
[ ] while_statement
[ ] do_while_statement
*/

/**
@class init init.hpp omni/ui/init.hpp
@brief Initializes the Omni UI Subsystem. Call this function before using any Omni UI class.
**/
void omni::ui::init ()
{
    using namespace omni::core::model;

    setUiMeta <builtin_literal_expression <unsigned int>> (createBuiltinLiteralExpressionView);
    setUiMeta <variable_declaration_expression>           (createVariableDeclarationExpression);
}
