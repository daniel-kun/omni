#include <omni/core/function.hpp>
#include <omni/core/module.hpp>
#include <omni/core/context.hpp>

int main (int argc, char * argv[])
{
	omni::core::context context;
	omni::core::module module (context, "test");
	omni::core::type type (module, "class");
	omni::core::function & func (type.addFunction ("add"));
}
