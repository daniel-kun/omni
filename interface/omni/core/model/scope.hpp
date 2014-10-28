#ifndef OMNI_CORE_MODEL_SCOPE_HPP
#define OMNI_CORE_MODEL_SCOPE_HPP

#include <omni/core/core.hpp>
#include <omni/core/id.hpp>
#include <omni/core/model/entity.hpp>

#include <memory>
#include <map>
#include <vector>

namespace omni {
namespace core {
    class context;
}
}

namespace omni {
namespace core {
namespace model {
    class type;
    class function_prototype;
    class function;
    class block;
    class module;
    class parameter;
    
    /**
    @class scope scope.hpp omni/core/model/scope.hpp
    @brief This class is abstract. A scope contains a list of top-level entities, which are accessible within this scope and it's children's scopes.

    Top-level entities currently are functions, only.
    **/
    class OMNI_CORE_API scope : public entity {
    public:

        explicit scope ();
        explicit scope (std::string name);
        explicit scope (id scopeId, std::string name = std::string ());
        ~ scope () = 0;

        static meta_info & getStaticMetaInfo ();

        virtual meta_info & getMetaInfo () const = 0;

        std::shared_ptr <function> createFunction (
            std::string const & name,
            std::shared_ptr <type> returnType,
            std::shared_ptr <block> body,
            std::vector <std::shared_ptr <parameter>> parameters = std::vector <std::shared_ptr <parameter>> (),
            bool isExported = false);
        std::shared_ptr <function_prototype> findFunctionByName (std::string const & name);
        void addFunction (std::shared_ptr <function_prototype> function);
        bool removeFunction (std::shared_ptr <function_prototype> function);
    };
} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
