#ifndef OMNI_CORE_MODEL_SCOPE_HPP
#define OMNI_CORE_MODEL_SCOPE_HPP

#include <omni/core/core.hpp>
#include <omni/core/id.hpp>
#include <omni/core/model/entity.hpp>

#include <memory>
#include <map>

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
    
    /**
    A scope contains a list of entities, which are themselves scopes.
    **/
    class OMNI_CORE_API scope : public entity {
    public:

        scope (std::string name = std::string ());
        scope (id scopeId, std::string name = std::string ());

        void setComponent (domain domain, std::string name, std::shared_ptr <omni::core::model::entity> entity) override;

        std::shared_ptr <model::entity> findContentById (id id);

        std::shared_ptr <model::function> createFunction (std::string const & name, std::shared_ptr <model::type> returnType, std::shared_ptr <model::block> body);
        std::shared_ptr <model::function_prototype> findFunctionByName (std::string const & name);
        void addFunction (std::shared_ptr <model::function_prototype> function);
        bool removeFunction (std::shared_ptr <model::function_prototype> function);
    };
} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
