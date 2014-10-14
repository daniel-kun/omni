#ifndef OMNI_UI_SANDBOX_SELECTOR_MODEL_HPP
#define OMNI_UI_SANDBOX_SELECTOR_MODEL_HPP

#include <QAbstractItemModel>

#include <memory>

namespace omni {
namespace core {
class context;
}
}

namespace omni {
namespace forge {
class sandbox_widget;

/**
@brief The hierarchical data model that contains all available sandbox demos. Suitable for QTreeView.

The available sandbox demos are "hardcoded" in this model.

The model has currently one column: title, which displays a title of the corresponding sandbox demo.
**/
class sandbox_selector_model : public QAbstractItemModel {
public:
    class sandbox_selector_data_base;

    enum class columns {
        title
    };

    sandbox_selector_model (omni::core::context & context);
    ~ sandbox_selector_model ();

    sandbox_widget * createDemoFromModelIndex (QWidget & parent, const QModelIndex & index);

    QModelIndex index (int row, int column, const QModelIndex & parent) const override;
    QModelIndex parent (const QModelIndex & index) const override;
    int rowCount (const QModelIndex & parent) const override;
    int columnCount (const QModelIndex & parent) const override;
    QVariant data (const QModelIndex & index, int role) const override;

private:
    omni::core::context & _context;
    std::unique_ptr <sandbox_selector_data_base> _root;
};

}
}

#endif
