#ifndef OMNI_FORGE_SANDBOX_HPP
#define OMNI_FORGE_SANDBOX_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QStackedLayout>
#include <QMenu>

#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>

#include <omni/ui/entity_base_widget.hpp>

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

/**
@brief Displays an omni::core::model::literal_expression.

It displays the value and the type of the literal_expression that is set via @see setEntity() or @see setLiteral(), with live update when changes are detected.
**/
class literal_expression_view : public omni::ui::entity_base_widget {
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

/**
@brief entity_type_chooser is a placeholder for any entity_base_widget that displays an entity that implements the given entityType.

The entityType is usually a very generic type such as "expression" or "statement". If the entitType is "expression", the entity_type_chooser can choose literal_expressions,
variable_assignment_expressions, binary_operator_expressions, and so on. If the entitType is statement, the entity_type_chooser can choose blocks, if_statements, 
while_statements, and so on.

TODO: Should the entity_type_chooser be permanent and have the chosen entity_base_widget as children, or should the entity_type_chooser be deleted after a type has been
chosen and replaced with the entity_base_widget for the given type?
**/
class entity_type_chooser : public QWidget {
    Q_OBJECT
public:
    entity_type_chooser (QWidget * parent, std::string entityType);

private:
    std::string _entityType;
    QMenu _selectorPopup;
};

/**
@brief Creates edit- and view-widgets for a specific type of entity.


**/
class entity_widget_provider {
public:
    static std::unique_ptr <omni::ui::entity_base_widget> createViewWidget (std::string entityType, QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget);
    static std::unique_ptr <omni::ui::entity_base_widget> createEditWidget (std::string entityType, QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget);


    entity_widget_provider (
        std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)> viewCreator,
        std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)> editCreator,
        std::function <bool (QKeyEvent * event)> keyHandler);

    void setViewWidgetCreator (std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)> creator);
    void setEditWidgetCreator (std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)> creator);
    void setKeyPressHandler   (std::function <bool (QKeyEvent * event)> keyHandler);

    virtual std::unique_ptr <omni::ui::entity_base_widget> createViewWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget);
    virtual std::unique_ptr <omni::ui::entity_base_widget> createEditWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget);
    virtual bool keyPressEvent (QKeyEvent * event);

private:
    std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)> _viewCreator;
    std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)> _editCreator;
    std::function <bool (QKeyEvent * event)> _keyHandler;
};

class entity_edit_widget : public omni::ui::entity_base_widget {
    Q_OBJECT
public:
    enum class Mode {
        m_view,
        m_edit
    };

    entity_edit_widget (omni::core::context & context, std::string entityType, QWidget * parent);

    std::shared_ptr <omni::core::model::entity> getEntity () override;
    void setEntity (std::shared_ptr <omni::core::model::entity> entity) override;

    Mode currentViewMode ();

public slots:
    Mode toggleViewMode ();

protected:
    void keyPressEvent (QKeyEvent * event) override;

private:
    omni::core::context & _c;
    std::string _entityType;
    QAction _toggleAction;
    QStackedLayout _layout;
    std::shared_ptr <omni::core::model::entity> _entity;
    std::unique_ptr <omni::ui::entity_base_widget> _viewWidget;
    std::unique_ptr <omni::ui::entity_base_widget> _editWidget;
};

class sandbox : public QWidget {
    Q_OBJECT
public:
    sandbox ();

private slots:
    void changeLiteralValue ();
    void changeLiteralType ();

private:
    omni::core::context _c;
    omni::core::model::module _m;

    QVBoxLayout _layout;
    entity_edit_widget _literalView;
    QPushButton _changeLiteralValueButton;
    QPushButton _changeLiteralTypeButton;
};

} // namespace omni
} // namespace forge

#endif
