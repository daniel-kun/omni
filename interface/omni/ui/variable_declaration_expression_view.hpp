#ifndef OMNI_UI_VARIABLE_DECLARATION_EXPRESSION_VIEW_HPP
#define OMNI_UI_VARIABLE_DECLARATION_EXPRESSION_VIEW_HPP

#include <omni/ui/ui.hpp>
#include <omni/ui/entity_base_widget.hpp>
#include <omni/ui/entity_toggle_widget.hpp>
#include <omni/ui/entity_widget_provider_base.hpp>
#include <omni/ui/entity_placeholder_widget.hpp>

#include <omni/core/model/variable_declaration_expression.hpp>

#include <QHBoxLayout>
#include <QLabel>

namespace omni {
namespace ui {

/**
@brief BRIEF
DOCS
**/
class OMNI_UI_API variable_declaration_expression_view : public entity_base_widget {
    Q_OBJECT
public:
    variable_declaration_expression_view (omni::core::context & context, omni::core::model::module & module, QWidget * parent);

    std::shared_ptr <omni::core::model::entity> getEntity () override;
    void setEntity (std::shared_ptr <omni::core::model::entity> entity) override;
    void startEdit () override;

private:
    void updateInitializationExpression (std::shared_ptr <omni::core::model::entity> initializationExpression);

    QHBoxLayout _layout;
    std::unique_ptr <entity_widget_provider_base> _nameWidgetProvider;
    QLabel _varFixedText;
    entity_toggle_widget _nameWidget;
    QLabel _assignmentOperator;
    entity_placeholder_widget _initializationExpression;
    std::shared_ptr <omni::core::model::variable_declaration_expression> _variableDeclExpression;
    boost::signals2::connection _initExpressionExpandedConnection;
};

}
}

#endif // include guard
