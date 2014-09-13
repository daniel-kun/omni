#ifndef OMNI_FORGE_SANDBOX_HPP
#define OMNI_FORGE_SANDBOX_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>

#ifndef Q_MOC_RUN
#include <boost/signals2.hpp>
#endif

#include <memory>

namespace omni {
namespace core {
namespace model {
class literal_expression;
}}}

namespace omni {
namespace forge {

class literal_expression_view : public QWidget {
    Q_OBJECT
public:
    literal_expression_view (QWidget * parent);

    void setLiteral (std::shared_ptr <omni::core::model::literal_expression> literalExpression);
    std::shared_ptr <omni::core::model::literal_expression> getLiteral ();

private:
    void updateContent ();

    QHBoxLayout                                             _layout;
    QLabel                                                  _valueLabel;
    QLabel                                                  _typeLabel;
    std::shared_ptr <omni::core::model::literal_expression> _literalExpression;
    boost::signals2::scoped_connection                      _literalValueChangedConnection;
};

class sandbox : public QWidget {
    Q_OBJECT
public:
    sandbox ();

private slots:
    void changeLiteralValue ();

private:
    QVBoxLayout _layout;
    literal_expression_view _literalView;
    QPushButton _changeLiteralValueButton;

    omni::core::context _c;
    omni::core::model::module _m;
};

} // namespace forge
} // namespace sandbox

#endif
