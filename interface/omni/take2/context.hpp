#ifndef OMNI_TAKE2_CONTEXT_HPP
#define OMNI_TAKE2_CONTEXT_HPP

#include <omni/take2/take2.hpp>
#include <memory>
#include <string>
#include <vector>

namespace omni {
namespace take2 {
    class function;
	/**
	The "context" is an instance of the omni compiler that store some global information, caches, etc.
	**/
	class OMNI_TAKE2_API context {
	public:
        void setEntryPoint (std::shared_ptr <function> function);
        void emitAssemblyFile (std::string const & fileName);

        void addFunction (std::shared_ptr <function> function);
        void removeFunction (std::shared_ptr <function> function);

	private:
        std::shared_ptr <function> _entryPoint;
        std::vector <std::shared_ptr <function>> _functions;
	};

} // namespace take2
} // namespace omni

#endif // include guard
