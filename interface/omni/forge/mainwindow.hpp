#ifndef OMNI_FORGE_MAINWINDOW_HPP
#define OMNI_FORGE_MAINWINDOW_HPP

#include <omni/ui/blueprint.hpp>
#include <omni/ui/syntax_input.hpp>

namespace omni {
namespace forge {

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow ();

private:
    QGridLayout _layout;    
    omni::ui::blueprint _blueprint;
    omni::ui::syntax_input _syntaxInput;
};

} // namespace omni
} // namespace forge

#endif // include guard

