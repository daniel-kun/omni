#include "sandbox_widget.hpp"

omni::forge::sandbox_widget::sandbox_widget (QWidget & parent, omni::forge::sandbox_widget::CompileAndRunFun compileAndRunFunction) :
    QWidget (& parent),
    _compileAndRunFun (compileAndRunFunction)
{

}

void omni::forge::sandbox_widget::compileAndRun (omni::core::context & context, omni::core::model::module & module)
{
    if (_compileAndRunFun) {
        _compileAndRunFun (context, module);
    }
}
