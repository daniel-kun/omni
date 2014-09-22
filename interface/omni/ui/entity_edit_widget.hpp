#ifndef OMNI_UI_ENTITY_EDIT_WIDGET_HPP
#define OMNI_UI_ENTITY_EDIT_WIDGET_HPP

#include <omni/ui/ui.hpp>
#include <omni/ui/entity_base_widget.hpp>

#include <QAction>
#include <QStackedLayout>

namespace omni {
namespace core {
class context;
}
}

namespace omni {
namespace ui {
class entity_widget_provider;

/**
**/
class OMNI_UI_API entity_edit_widget : public entity_base_widget {
    Q_OBJECT
public:
    enum class Mode {
        m_view,
        m_edit
    };

    entity_edit_widget (omni::core::context & context, entity_widget_provider & provider, QWidget * parent);

    std::shared_ptr <omni::core::model::entity> getEntity () override;
    void setEntity (std::shared_ptr <omni::core::model::entity> entity) override;

    Mode currentViewMode ();

public slots:
    Mode toggleViewMode ();

protected:
    void keyPressEvent (QKeyEvent * event) override;

private:
    omni::core::context & _c;
    entity_widget_provider & _provider;
    QAction _toggleAction;
    QStackedLayout _layout;
    std::shared_ptr <omni::core::model::entity> _entity;
    std::unique_ptr <omni::ui::entity_base_widget> _viewWidget;
    std::unique_ptr <omni::ui::entity_base_widget> _editWidget;
};

} // namespace ui
} // namespace omni

#endif // include guard
