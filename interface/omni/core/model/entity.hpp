#ifndef OMNI_CORE_ENTITY_HPP
#define OMNI_CORE_ENTITY_HPP

#include <omni/core/core.hpp>
#include <omni/core/id.hpp>

#include <string>
#include <memory>
#include <map>
#include <set>

namespace omni {
namespace core {
    class context;
}
}

namespace omni {
namespace core {
namespace model {
    class scope;
    class module;

    /**
    Abstract.
    Base class for all information that is part of a context, such as variable declarations.
    (later: function declarations, etc.).
    **/
    class OMNI_CORE_API entity {
    public:
        typedef std::map <std::string, std::shared_ptr <entity>> name_to_entities_map;
        typedef std::map <domain, name_to_entities_map> domain_to_name_to_entities_map;

        entity ();
        entity (std::string const & name);
        entity (id entityId, std::string const & name);
        virtual ~ entity () = 0;

        virtual context * getContext ();
        virtual const context * getContext () const;

        virtual module * getModule ();
        virtual const module * getModule () const;

        virtual domain getDomain () const = 0;

        scope * getParent ();
        const scope * getParent () const;
        void setParent (scope * parent);

        const domain_to_name_to_entities_map & getComponents () const;
        domain_to_name_to_entities_map getComponents ();
        const name_to_entities_map getComponents (domain domain) const;
        name_to_entities_map getComponents (domain domain);
        std::shared_ptr <entity> getComponent (domain domain, std::string name) const;
        template <typename T>
        std::shared_ptr <T> getComponentAs (domain domain, std::string name) const;
        std::map <std::string, std::shared_ptr <entity>> getComponentsStartingWith (domain domain, std::string name) const;
        template <typename T>
        std::map <std::string, std::shared_ptr <T>> getComponentsStartingWithAs (domain domain, std::string name) const;
        virtual void setComponent (domain domain, std::string name, std::shared_ptr <entity> entity) = 0;
        void clearComponents ();
        void clearComponents (domain domain);
        bool removeComponent (domain domain, std::string name);
        bool removeComponent (domain domain, std::shared_ptr <entity> component);

        std::string getName () const;
        void setName (const std::string & name);

        void setId (id newId);
        id getId () const;

        virtual void fillLibraries (std::set <std::string> & libraries);

    private:
        void updateIds ();

        scope * _parent;
        std::string _name;
        id _id;
        domain_to_name_to_entities_map _components;
    };

} // namespace model
} // namespace core
} // namespace omni

template <typename T>
std::shared_ptr <T> omni::core::model::entity::getComponentAs (omni::core::domain domain, std::string name) const
{
    return std::dynamic_pointer_cast <T> (getComponent (domain, name));
}

template <typename T>
std::map <std::string, std::shared_ptr <T>> omni::core::model::entity::getComponentsStartingWithAs (omni::core::domain domain, std::string name) const
{
    std::map <std::string, std::shared_ptr <T>> result;
    for (auto i : getComponentsStartingWith (domain, name)) {
        result [i.first] = std::dynamic_pointer_cast <T> (i.second);
    }
    return result;
}

#endif // include guard
