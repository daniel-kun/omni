#include <omni/ui/entity_placeholder_widget.hpp>

#include <QContextMenuEvent>
#include <QMessageBox>
#include <QStringBuilder>

omni::ui::entity_placeholder_widget::entity_placeholder_widget (QWidget * parent, omni::core::model::meta_info const & entityMeta) :
    QWidget (parent),
    _entityMeta (entityMeta),
    _selectorPopup (this)
{
    setMinimumSize (100, 100);
    setAutoFillBackground (true);
    QPalette pal = palette ();
    pal.setBrush (QPalette::Background, Qt::gray);
    setPalette (pal);
}

void omni::ui::entity_placeholder_widget::contextMenuEvent (QContextMenuEvent * event)
{
    _selectorPopup.clear ();
    populateMenu (_entityMeta, _selectorPopup);
    _selectorPopup.popup (QPoint (event->globalX (), event->globalY ()));
}

void omni::ui::entity_placeholder_widget::switchToEntityType ()
{
    QAction * action = dynamic_cast <QAction*> (sender ());
    QMessageBox::warning (
        this,
        "Not yet implemented",
        action->text () % " is not yet implemented. Coming soon!");
}

void omni::ui::entity_placeholder_widget::populateMenu (omni::core::model::meta_info const & meta, QMenu & menu)
{
    if (! meta.isAbstract ()) {
        auto * action = new QAction (QString::fromStdString (meta.getName ()), & menu);
        connect (action, SIGNAL(triggered()), SLOT(switchToEntityType()));
        menu.addAction (action);
    }
    for (std::size_t i = 0u; i < meta.getChildCount (); ++ i) {
        auto & child = meta.getChildAt (i);
        populateMenu (child, menu);
    }
}
