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
    @class external_function external_function.hpp omni/core/model/external_function.hpp
    @brief Declares an external function that can be called with a function_call_expression.

    An external function is defined in a different module than the function_call_expression is called in.
    An external function consists of a name that should be unique within a scope, a return-type, a number of parameters and a library name
    that it is defined in.
    
    The library name of an external_function declaration will be added to the list of linked libraries at link-time.
    Each library will only be added once - multiple external_function s that have the same libraryName will not lead to a library linked multiple times.
    **/
    class OMNI_CORE_API external_function : public function_prototype {
    public:
        external_function (std::string libraryName = std::string (),
                           std::string functionName = std::string (),
                           std::shared_ptr <type> returnType = std::shared_ptr <type> (),
                           std::vector <std::shared_ptr <parameter>> parameters = std::vector <std::shared_ptr <parameter>> (),
                           bool isDllImport = false);

        domain getDomain () const override;

        void setLibraryName (std::string libraryName);
        std::string getLibraryName () const;
        void setDllImport (bool isDllImport);
        bool isDllImport () const;

        llvm::Function * llvmFunction () override;
        void fillLibraries (std::set <std::string> & libraries) override;

    private:
        llvm::Function * _llvmFunction;
        std::string _libraryName;
        bool        _isDllImport;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
