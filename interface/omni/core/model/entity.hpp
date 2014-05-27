#ifndef OMNI_CORE_ENTITY_HPP
#define OMNI_CORE_ENTITY_HPP

#include <omni/core/core.hpp>
#include <omni/core/id.hpp>

#include <string>
#include <memory>
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
    Base class for all information that is part of a context, such as variable declarations.
    (later: function declarations, etc.).
    **/
    class OMNI_CORE_API entity {
    public:
        entity (scope * parent);
        entity (scope * parent, std::string const & name);
        entity (scope * parent, id entityId, std::string const & name);
        virtual ~ entity () = 0;

        virtual context * getContext ();
        virtual const context * getContext () const;

        virtual module * getModule ();
        virtual const module * getModule () const;

        scope * getParent ();
        const scope * getParent () const;

        std::string getName () const;
        void setName (const std::string & name);

        void setId (id newId);
        id getId () const;

        virtual void fillLibraries (std::set <std::string> & libraries);

    private:
        scope * _parent;
        std::string _name;
        id _id;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
