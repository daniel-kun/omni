#ifndef OMNI_FORGE_SANDBOX_SELECTOR_HPP
#define OMNI_FORGE_SANDBOX_SELECTOR_HPP

#include "sandbox_selector_model.hpp"

#include <omni/ui/tree_sort_filter_proxy_model.hpp>

#include <QWidget>
#include <QHBoxLayout>
#include <QTreeView>
#include <QLineEdit>

namespace omni {
namespace forge {
class sandbox_widget;

/**
@brief A widget that lets you select sandbox demos.

sandbox_selector uses the sandbox_selector_model, which itself contains a standard set of available sandbox demos.
If a demo is selected by the user, demoSelected(sandbox_widget) will be emitted.
**/
class sandbox_selector : public QWidget {
    Q_OBJECT
public:
    sandbox_selector (omni::core::context & context, omni::core::model::module & module, QWidget * parent);

signals:
    void demoSelected (sandbox_widget & demoWidget);

public slots:
    void focusSearchField ();
    void setFilter (QString filterText);

private slots:
    void emitDemoSelected (const QModelIndex & current);

private:
    QVBoxLayout _layout;
    QLineEdit _searchField;
    QTreeView _selector;
    sandbox_selector_model _model;
    omni::ui::tree_sort_filter_proxy_model _filterModel;
};

}
}

#endif
