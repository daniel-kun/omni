#ifndef OMNI_FORGE_MAIN_WINDOW_HPP
#define OMNI_FORGE_MAIN_WINDOW_HPP

#include "sandbox_selector.hpp"

#include <omni/ui/entity_edit_widget.hpp>

#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

namespace omni {
namespace forge {

/**
@brief Main window for the interactive sandbox demos.

Displays a tree of available sandbox demos on the left side and the selected demo in action on the right side.
**/
class main_window : public QWidget {
    Q_OBJECT
public:
    main_window ();

private slots:
    void activateDemo (QWidget & demo);

private:
    omni::core::context _c;
    omni::core::model::module _m;

    QHBoxLayout _layout;
    QVBoxLayout _rightLayout;
    sandbox_selector _selector;
    QLabel _demoLabel;
    QWidget * _activeDemo;
    QPushButton _compileAndRunButton;
};

} // namespace forge
} // namespace omni

#endif // include guard
