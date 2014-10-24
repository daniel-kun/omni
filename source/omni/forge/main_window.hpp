#ifndef OMNI_FORGE_MAIN_WINDOW_HPP
#define OMNI_FORGE_MAIN_WINDOW_HPP

#include "sandbox_selector.hpp"
#include "sandbox_widget.hpp"

#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QShortcut>

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
    void showEvent (QShowEvent * event) override;
    void activateDemo (sandbox_widget & demo);
    void compileAndRunActiveDemo ();

private:
    omni::core::context _c;
    omni::core::model::module _m;

    QHBoxLayout _layout;
    QVBoxLayout _rightLayout;
    QGroupBox _groupDemoList;
    QVBoxLayout _groupDemoListLayout;
    sandbox_selector _selector;
    sandbox_widget _demoLabel;
    QLabel _demoChildLabel;
    sandbox_widget * _activeDemo;
    QPushButton _compileAndRunButton;
    QShortcut _searchShortcut;
};

} // namespace forge
} // namespace omni

#endif // include guard
