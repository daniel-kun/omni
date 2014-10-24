#include <omni/ui/tree_sort_filter_proxy_model.hpp>

/**
@return Returns the QModelIndex of the first row that matches the current filter criteria exactly.
**/
QModelIndex omni::ui::tree_sort_filter_proxy_model::firstMatchingIndex () const
{
    return firstMatchingIndexImpl (QModelIndex ());
}

/**
@brief Recursive implementation detail to firstMatchingIndex ().
**/
QModelIndex omni::ui::tree_sort_filter_proxy_model::firstMatchingIndexImpl (const QModelIndex & parent) const
{
    for (int r = 0; r < rowCount (parent); ++ r) {
        if (filterAcceptsRowExactly (r, mapToSource (parent))) {
            return index (r, 0, parent);
        }
        QModelIndex result = firstMatchingIndexImpl (index (r, 0, parent));
        if (result.isValid ()) {
            return result;
        }
    }
    return QModelIndex ();
}

/**
@brief Provides the original functionality of QSortFilterProxyModel's filterAcceptRow() function.

@return True, if the given row itself matches the current filter criteria. Children are not checked.
**/
bool omni::ui::tree_sort_filter_proxy_model::filterAcceptsRowExactly (int sourceRow, const QModelIndex & sourceParent) const
{
    return QSortFilterProxyModel::filterAcceptsRow (sourceRow,  sourceParent);
}

bool omni::ui::tree_sort_filter_proxy_model::filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const
{
    // If this row matches, return true:
    if (filterAcceptsRowExactly (sourceRow,  sourceParent)) {
        return true;
    }
    // Now check whether any of this row's child rows matches:
    QModelIndex row = sourceModel ()->index (sourceRow, filterKeyColumn (), sourceParent);
    for (int i = 0; i < sourceModel ()->rowCount (row); ++ i) {
        if (filterAcceptsRow (i, row)) {
            return true;
        }
    }
    // Neither this row, nor any children, match.
    return false;
}
