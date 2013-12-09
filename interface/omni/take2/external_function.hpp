#ifndef OMNI_TAKE2_EXTERNAL_FUNCTION_HPP
#define OMNI_TAKE2_EXTERNAL_FUNCTION_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/function_prototype.hpp>

namespace omni {
namespace take2 {
    class type;

    /**
    An external_function is defined in another module and does not contain a body definition.
    external_function can be seen similar as a function declaration in C that is not defined in the same module, but imported from another static or shared library.
    **/
    class OMNI_TAKE2_API external_function : public function_prototype {
    public:
        external_function (std::string libraryName,
                           std::string functionName,
                           std::shared_ptr <omni::take2::type> returnType,
                           std::vector <std::shared_ptr <omni::take2::parameter>> parameters = std::vector <std::shared_ptr <omni::take2::parameter>> (),
                           bool isDllImport = false);

        std::string getLibraryName () const;
        bool isDllImport () const;

        llvm::Function * llvmFunction (llvm::Module & llvmModule) override;
        void fillLibraries (std::set <std::string> & libraries) override;

    private:
        std::string _libraryName;
        bool        _isDllImport;
    };

} // namespace take2
} // namespace omni

#endif // include guard
