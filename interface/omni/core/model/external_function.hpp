#ifndef OMNI_CORE_EXTERNAL_FUNCTION_HPP
#define OMNI_CORE_EXTERNAL_FUNCTION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/function_prototype.hpp>

namespace omni {
namespace core {
namespace model {
    class module;
    class type;

    /**
    An external_function is defined in another module and does not contain a body and therefore no definition.
    external_function can be seen similar as a function declaration in C that is not defined in the same module, but imported from another static or shared library.
    **/
    class OMNI_CORE_API external_function : public function_prototype {
    public:
        external_function (std::string libraryName,
                           std::string functionName,
                           std::shared_ptr <type> returnType,
                           std::vector <std::shared_ptr <parameter>> parameters = std::vector <std::shared_ptr <parameter>> (),
                           bool isDllImport = false);

        std::string getLibraryName () const;
        bool isDllImport () const;

        llvm::Function * llvmFunction () override;
        void fillLibraries (std::set <std::string> & libraries) override;

    private:
        std::string _libraryName;
        bool        _isDllImport;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
