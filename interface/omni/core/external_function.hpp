#ifndef OMNI_CORE_EXTERNAL_FUNCTION_HPP
#define OMNI_CORE_EXTERNAL_FUNCTION_HPP

#include <omni/core/core.hpp>
#include <omni/core/function_prototype.hpp>

namespace omni {
namespace core {
    class type;
    class module;

    /**
    An external_function is defined in another module and does not contain a body and therefore no definition.
    external_function can be seen similar as a function declaration in C that is not defined in the same module, but imported from another static or shared library.
    **/
    class OMNI_CORE_API external_function : public function_prototype {
    public:
        external_function (module & module,
                           std::string libraryName,
                           std::string functionName,
                           std::shared_ptr <omni::core::type> returnType,
                           std::vector <std::shared_ptr <omni::core::parameter>> parameters = std::vector <std::shared_ptr <omni::core::parameter>> (),
                           bool isDllImport = false);

        std::string getLibraryName () const;
        bool isDllImport () const;

        llvm::Function * llvmFunction () override;
        void fillLibraries (std::set <std::string> & libraries) override;

    private:
        std::string _libraryName;
        bool        _isDllImport;
    };

} // namespace core
} // namespace omni

#endif // include guard
