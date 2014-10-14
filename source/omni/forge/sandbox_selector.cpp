#include "sandbox_selector.hpp"

omni::forge::sandbox_selector::sandbox_selector (omni::core::context & context, QWidget * parent) :
    QWidget (parent),
    _layout (this),
    _selector (this),
    _model (context)
{
    _layout.addWidget (& _selector);
    _selector.setModel (& _model);
    connect (_selector.selectionModel (), SIGNAL(currentChanged(QModelIndex, QModelIndex)), SLOT (emitDemoSelected(QModelIndex, QModelIndex)));
}

void omni::forge::sandbox_selector::emitDemoSelected (const QModelIndex & current, const QModelIndex &)
{
    if (current != QModelIndex ()) {
        sandbox_widget * demoWidget = _model.createDemoFromModelIndex (* parentWidget (), current);
        if (demoWidget != nullptr) {
            emit demoSelected (*demoWidget);
        }
    }
}
