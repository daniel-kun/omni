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

class entity_widget : public QWidget {
    Q_OBJECT
public:
    entity_widget (QWidget * parent);

    virtual std::shared_ptr <omni::core::model::entity> getEntity ();
    virtual void setEntity (std::shared_ptr <omni::core::model::entity> entity);
};

class generic_entity_editor : public entity_widget {
    Q_OBJECT
public:
    generic_entity_editor (QWidget * parent, std::shared_ptr <omni::core::model::entity> entity = std::shared_ptr <omni::core::model::entity> ());

    boost::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> getTextToEntityConverter ();
    void setTextToEntityConverter (boost::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> converter);

    std::shared_ptr <omni::core::model::entity> getEntity () override;
    void setEntity (std::shared_ptr <omni::core::model::entity> entity) override;

private:
    boost::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> _converter;
    std::shared_ptr <omni::core::model::entity> _entity;
    QStackedLayout _layout;
    QLineEdit _edit;
};

class literal_expression_view : public entity_widget {
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

class entity_type_chooser : public QWidget {
    Q_OBJECT
public:
    entity_type_chooser (QWidget * parent, std::string entityType);

private:
    std::string _entityType;
    QMenu _selectorPopup;
};

class entity_edit_provider {
public:
    virtual std::unique_ptr <entity_widget> createViewWidget (QWidget * parent, omni::core::context & context, entity_widget * editWidget) = 0;
    virtual std::unique_ptr <entity_widget> createEditWidget (QWidget * parent, omni::core::context & context, entity_widget & viewWidget) = 0;
    virtual bool keyPressEvent (QKeyEvent * event);
};

class entity_edit_widget : public entity_widget {
    Q_OBJECT
public:
    enum class Mode {
        m_view,
        m_edit
    };

    entity_edit_widget (omni::core::context & context, entity_edit_provider & editProvider, QWidget * parent);

    std::shared_ptr <omni::core::model::entity> getEntity () override;
    void setEntity (std::shared_ptr <omni::core::model::entity> entity) override;

    Mode currentViewMode ();

public slots:
    Mode toggleViewMode ();

protected:
    void keyPressEvent (QKeyEvent * event) override;

private:
    omni::core::context & _c;
    entity_edit_provider & _editProvider;
    QAction _toggleAction;
    QStackedLayout _layout;
    std::shared_ptr <omni::core::model::entity> _entity;
    std::unique_ptr <entity_widget> _viewWidget;
    std::unique_ptr <entity_widget> _editWidget;
};

class literal_edit_provider : public entity_edit_provider {
public:
    std::unique_ptr <entity_widget> createViewWidget (QWidget * parent, omni::core::context & context, entity_widget * editWidget) override;
    std::unique_ptr <entity_widget> createEditWidget (QWidget * parent, omni::core::context & context, entity_widget & viewWidget) override;
    bool keyPressEvent (QKeyEvent * event) override;
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
    literal_edit_provider _literalEditProvider;
    entity_edit_widget _literalView;
    QPushButton _changeLiteralValueButton;
    QPushButton _changeLiteralTypeButton;
};

} // namespace omni
} // namespace forge

#endif
