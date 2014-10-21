#include <omni/ui/entity_toggle_widget.hpp>
#include <omni/ui/entity_widget_provider_base.hpp>

omni::ui::entity_toggle_widget::entity_toggle_widget (omni::core::context & context, entity_widget_provider_base & provider, QWidget * parent) :
    entity_base_widget (parent),
    _c (context),
    _provider (provider),
    _toggleAction ("Test", this),
    _layout (this),
    _entity (),
    _viewWidget (),
    _editWidget ()
{
    _toggleAction.setShortcut (QKeySequence (Qt::Key_Return));
    _toggleAction.setShortcutContext (Qt::WidgetWithChildrenShortcut);
    addAction (& _toggleAction);
    connect (& _toggleAction, SIGNAL(triggered()), SLOT (toggleViewMode()));
    toggleViewMode ();
    setAutoFillBackground (true);
    setFocusPolicy (Qt::StrongFocus);
}

std::shared_ptr <omni::core::model::entity> omni::ui::entity_toggle_widget::getEntity ()
{
    if (_viewWidget) {
        return _viewWidget->getEntity ();
    } else if (_editWidget) {
        return _editWidget->getEntity ();
    } else {
        return std::shared_ptr <omni::core::model::entity> ();
    }
}

void omni::ui::entity_toggle_widget::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    if (_viewWidget) {
        _viewWidget->setEntity (entity);
    } else if (_editWidget) {
        _editWidget->setEntity (entity);
    }
}

void omni::ui::entity_toggle_widget::focusInEvent (QFocusEvent * event)
{
    QWidget::focusInEvent (event);
    QPalette pal;
    pal.setBrush (QPalette::Background, Qt::red);
    setPalette (pal);
}

void omni::ui::entity_toggle_widget::focusOutEvent (QFocusEvent * event)
{
    QWidget::focusOutEvent (event);
    QPalette pal;
    setPalette (pal);
}

omni::ui::entity_toggle_widget::Mode omni::ui::entity_toggle_widget::currentViewMode ()
{
    if (_viewWidget) {
        return Mode::m_view;
    } else {
        return Mode::m_edit;
    }
}

omni::ui::entity_toggle_widget::Mode omni::ui::entity_toggle_widget::toggleViewMode ()
{
    if (_viewWidget) {
        // Go into edit mode:
        bool hadFocus = hasFocus () || _viewWidget->hasFocus ();
        _editWidget = _provider.createEditWidget (this, _c, *_viewWidget);
        _layout.addWidget (_editWidget.get ());
        _viewWidget.reset ();
        if (hadFocus) {
            _editWidget->setFocus (Qt::TabFocusReason);
        }
        setFocusProxy (_editWidget.get ());
        return Mode::m_edit;
    } else {
        // Accept input, go into view mode:
        bool hadFocus;
        if (_editWidget) {
            hadFocus = hasFocus () || _editWidget->hasFocus ();
        } else {
            hadFocus = hasFocus ();
        }
        _viewWidget = _provider.createViewWidget (this, _c, _editWidget.get ());
        _editWidget.reset ();
        _layout.addWidget (_viewWidget.get ());
        setFocusProxy (nullptr);
        if (hadFocus) {
            setFocus (Qt::TabFocusReason);
        }
        return Mode::m_view;
    }
}

void omni::ui::entity_toggle_widget::keyPressEvent (QKeyEvent * /*event*/)
{
/*
    if (! _editProvider.keyPressEvent (event)) {
        QWidget::keyPressEvent (event);
    }
*/
}

/*
bool omni::forge::literal_edit_provider::keyPressEvent (QKeyEvent * event)
{
    if (std::isalnum (event->key (), std::locale (""))) {
        return true;
    } else {
        return false;
    }
}
*/

