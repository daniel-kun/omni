#include "sandbox_selector.hpp"

#include <QHeaderView>

omni::forge::sandbox_selector::sandbox_selector (omni::core::context & context, QWidget * parent) :
    QWidget (parent),
    _layout (this),
    _searchField (this),
    _selector (this),
    _model (context),
    _filterModel ()
{
    _searchField.setPlaceholderText ("Search demos...");
    _filterModel.setSourceModel (& _model);
    _layout.addWidget (& _searchField);
    _layout.addWidget (& _selector);
    _selector.setModel (& _filterModel);
    _selector.expandAll ();
    _selector.header ()->hide ();
    connect (& _searchField, SIGNAL(textChanged(QString)), SLOT(setFilter(QString)));
    connect (_selector.selectionModel (), SIGNAL(currentChanged(QModelIndex, QModelIndex)), SLOT (emitDemoSelected(QModelIndex)));
}

/**
@brief Updates the current filter.

Sets the filter criteria to `filterText', showing only demos in the tree view that match the filter (or their children match the filter).
@param filterText The filter-text. case-sensitive, partial matching.
**/
void omni::forge::sandbox_selector::setFilter (QString filterText)
{
    _filterModel.setFilterFixedString (filterText);
    if (! filterText.isEmpty ()) {
        QModelIndex firstMatchingDemo = _filterModel.firstMatchingIndex ();
        if (firstMatchingDemo.isValid ()) {
            _selector.selectionModel ()->clearSelection ();
            _selector.selectionModel ()->select (firstMatchingDemo, QItemSelectionModel::SelectCurrent);
            _selector.setCurrentIndex (firstMatchingDemo);
        }
    } else {
        _selector.clearSelection ();
        _selector.setCurrentIndex (QModelIndex ());
    }
}

void omni::forge::sandbox_selector::focusSearchField ()
{
    _searchField.setFocus (Qt::TabFocusReason);
}

void omni::forge::sandbox_selector::emitDemoSelected (const QModelIndex & current)
{
    if (current != QModelIndex ()) {
        sandbox_widget * demoWidget = _model.createDemoFromModelIndex (* parentWidget (), _filterModel.mapToSource (current));
        if (demoWidget != nullptr) {
            emit demoSelected (*demoWidget);
        }
    }
}
