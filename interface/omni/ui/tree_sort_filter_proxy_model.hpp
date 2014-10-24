#ifndef OMNI_UI_TREE_SORT_FILTER_PROXY_MODEL_HPP
#define OMNI_UI_TREE_SORT_FILTER_PROXY_MODEL_HPP

#include <omni/ui/ui.hpp>

#include <QSortFilterProxyModel>

namespace omni {
namespace ui {

/**
@brief Provides pragmatic filter semantics for tree models. This means, that parent nodes are not 
filtered as long as any of their child nodes matches the filter.
**/
class OMNI_UI_API tree_sort_filter_proxy_model : public QSortFilterProxyModel {
public:
    QModelIndex firstMatchingIndex () const;
    bool filterAcceptsRowExactly (int sourceRow, const QModelIndex & sourceParent) const;

protected:
    bool filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const;
private:
    QModelIndex firstMatchingIndexImpl (const QModelIndex & parent) const;
};

}
}

#endif // include guard
