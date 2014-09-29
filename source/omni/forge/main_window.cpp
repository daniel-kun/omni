#include "main_window.hpp"

#include <omni/core/model/builtin_literal_expression.hpp>

#include <omni/ui/entity_widget_provider.hpp>

omni::forge::main_window::main_window () :
    QWidget (),
    _c (),
    _m (_c, "forge-sandbox"),
    _layout (this),
    _rightLayout (),
    _selector (_c, this),
    _demoLabel (this),
    _activeDemo (& _demoLabel),
    _compileAndRunButton (this)
{
    setWindowState (Qt::WindowMaximized);
    _layout.addWidget (& _selector);
    _selector.setMaximumWidth (300u);
    _layout.addLayout (& _rightLayout);
    _rightLayout.addWidget (& _demoLabel, 1);
    _rightLayout.addWidget (& _compileAndRunButton, 0, Qt::AlignBottom);
    _compileAndRunButton.setText ("Compile &and run");
    _demoLabel.setText ("Select a demo in the tree on the left side.");

    connect (& _selector, SIGNAL (demoSelected(QWidget&)), SLOT (activateDemo(QWidget&)));
}

void omni::forge::main_window::activateDemo (QWidget & demo)
{
    if (_activeDemo != nullptr) {
        _rightLayout.removeWidget (_activeDemo);
        _activeDemo->hide ();
    }
    _activeDemo = & demo;
    if (_activeDemo != nullptr) {
        _rightLayout.insertWidget (0, _activeDemo, 1, Qt::AlignVCenter);
        _activeDemo->show ();
    }
}
