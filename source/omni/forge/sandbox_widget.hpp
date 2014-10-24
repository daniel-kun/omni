#ifndef OMNI_FORGE_SANDBOX_WIDGET_HPP
#define OMNI_FORGE_SANDBOX_WIDGET_HPP

#include <QWidget>

#include <functional>

namespace omni {
namespace core {
class context;
namespace model {
class module;
}
}
}

namespace omni {
namespace forge {

/**
@brief A base class for sandbox demo widgets that are displayed in the main_window.

Sandbox demo widgets contain a "live", interactive demo of some view that is used in Omni Forge.

A demo can be compiled and run so that the piece of code-generation for the corresponding view can be tested.
**/
class sandbox_widget : public QWidget {
    Q_OBJECT
public:
    using CompileAndRunFun = std::function <void (omni::core::context & context, omni::core::model::module & module)>;

    sandbox_widget (QWidget & parent, CompileAndRunFun compileAndRunFunction = CompileAndRunFun ());

    virtual void compileAndRun (omni::core::context & context, omni::core::model::module & module);

private:
    CompileAndRunFun _compileAndRunFun;
};

}
}

#endif // include guard
