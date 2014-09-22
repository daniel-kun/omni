#ifndef OMNI_FORGE_SANDBOX_HPP
#define OMNI_FORGE_SANDBOX_HPP

#include <omni/ui/entity_edit_widget.hpp>

#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>

#include <QVBoxLayout>

namespace omni {
namespace forge {

class sandbox : public QWidget {
    Q_OBJECT
public:
    sandbox ();

private:
    omni::core::context _c;
    omni::core::model::module _m;

    QVBoxLayout _layout;
    omni::ui::entity_edit_widget _literalView;
};

} // namespace omni
} // namespace forge

#endif
