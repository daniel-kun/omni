#ifndef OMNI_UI_LITERAL_EXPRESSION_VIEW_HPP
#define OMNI_UI_LITERAL_EXPRESSION_VIEW_HPP

#include <omni/ui/ui.hpp>
#include <omni/ui/entity_base_widget.hpp>

#include <QHBoxLayout>
#include <QLabel>

#ifndef Q_MOC_RUN
#include <boost/signals2.hpp>
#endif

#include <memory>

namespace omni {
namespace core {
namespace model {
class literal_expression;
}
}
}

namespace omni {
namespace ui {
/**
@brief Displays an omni::core::model::literal_expression.

It displays the value and the type of the literal_expression that is set via @see setEntity() or @see setLiteral(), with live update when changes are detected.
**/
class OMNI_UI_API literal_expression_view : public omni::ui::entity_base_widget {
    Q_OBJECT
public:
    literal_expression_view (QWidget * parent);

    std::shared_ptr <omni::core::model::entity> getEntity () override;
    void setEntity (std::shared_ptr <omni::core::model::entity> entity) override;

    void setLiteral (std::shared_ptr <omni::core::model::literal_expression> literalExpression);
    std::shared_ptr <omni::core::model::literal_expression> getLiteral ();

protected:
    void focusInEvent (QFocusEvent * event) override;
    void focusOutEvent (QFocusEvent * event) override;

private:
    void updateContent ();

    QHBoxLayout                                             _layout;
    QLabel                                                  _valueLabel;
    QLabel                                                  _typeLabel;
    std::shared_ptr <omni::core::model::literal_expression> _literalExpression;
    boost::signals2::scoped_connection                      _literalValueChangedConnection;
};

} // namespace ui
} // namespace omni

#endif // include guard
