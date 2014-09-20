#ifndef OMNI_CORE_MODEL_ENTITY_HPP
#define OMNI_CORE_MODEL_ENTITY_HPP

#include <omni/core/core.hpp>
#include <omni/core/id.hpp>

#ifndef Q_MOC_RUN
#include <boost/signals2.hpp>
#endif

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
    @class entity entity.hpp omni/core/model/entity.hpp
    @brief This class is abstract. Base class for all objects that are part of a context, such as any kinds of statements and expressions, like variable declarations, if-statements, etc.

    The Omni Programming Language Model consists of a network of entities. The highest level entity in the model is the module. A module, in turn, mainly contains functions.
    Functions contain a block that builds up it's body, which in turn contains a list of statements, such as variable declarations, etc.

    See one of the many base-classes for further description of what they do.
    **/
    class OMNI_CORE_API entity {
    public:
        typedef boost::signals2::signal <void (entity & sender)> ChangedSignal;

        /**
        Used to store lists that map a component's name to an entity.
        @see getComponents(omni::core::domain)
        **/
        typedef std::map <std::string, std::shared_ptr <entity>> name_to_entities_map;
        /**
        Used to store lists that map a component's domain to a list of entities.
        @see getComponents()
        **/
        typedef std::map <domain, name_to_entities_map> domain_to_name_to_entities_map;

        explicit entity ();
        explicit entity (std::string const & name);
        explicit entity (id entityId, std::string const & name);
        virtual ~ entity () = 0;

        void setId (id newId);
        id getId () const;

        virtual domain getDomain () const = 0;

        void setName (const std::string & name);
        std::string getName () const;

        void setParent (entity * parent);
        entity * getParent ();
        const entity * getParent () const;

        virtual module * getModule ();
        virtual const module * getModule () const;

        virtual context * getContext ();
        virtual const context * getContext () const;

        virtual void setComponent (domain domain, std::string name, std::shared_ptr <entity> entity);
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
        std::shared_ptr <entity> lookupComponentById (id id);
        void clearComponents ();
        void clearComponents (domain domain);
        bool removeComponent (domain domain, std::string name);
        bool removeComponent (domain domain, std::shared_ptr <entity> component);

        boost::signals2::connection connectChanged (ChangedSignal::slot_type handler);

        virtual void fillLibraries (std::set <std::string> & libraries);

    protected:
        virtual void changed ();

    private:
        void updateIds ();

        entity * _parent;
        std::string _name;
        id _id;
        domain_to_name_to_entities_map _components;
        ChangedSignal _changedSignal;
    };

} // namespace model
} // namespace core
} // namespace omni

/**
@brief Returns the component that is stored for the given domain with the given name, if it is of type `T'.

For an explanation of what a component is, @see getComponents()

Which domains and names are used to store the components depends on the actual entity, see the respective documentation of the actual entity's class.

Note that a component's name has nothing to do with an entity's name that can be retrieved by getName().
@param domain The domain that the component is stored in.
@param name The name that the component is stored as.
@return The component that is stored for the given domain with the given name. Returns nullptr if the component does not exist or can not by dynamic_cast'ed to `T'.
**/
template <typename T>
std::shared_ptr <T> omni::core::model::entity::getComponentAs (omni::core::domain domain, std::string name) const
{
    return std::dynamic_pointer_cast <T> (getComponent (domain, name));
}

/**
@brief Returns a list of components for the given domain whose names start with the given prefix, if they are of type `T'.

For an explanation of what a component is, @see getComponents()

This function can be used when an entity contains a list of components with the same meaning, such as a function contains a list of parameters.
All parameters start with the same name, so a list of parameters can be retrieved by calling getComponentsStartingWith(omni::core::domain::parameter, "parameter").

@param domain The domain that the components are stored in.
@param prefix The prefix that the names of the components start with.
@return A list that maps the component's name to the stored entity. Only entities that can be dynamic_cast'ed to `T' are listed.
**/
template <typename T>
std::map <std::string, std::shared_ptr <T>> omni::core::model::entity::getComponentsStartingWithAs (omni::core::domain domain, std::string prefix) const
{
    std::map <std::string, std::shared_ptr <T>> result;
    for (auto i : getComponentsStartingWith (domain, prefix)) {
        result [i.first] = std::dynamic_pointer_cast <T> (i.second);
    }
    return result;
}

#endif // include guard
