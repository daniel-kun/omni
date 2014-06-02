#ifndef OMNI_CORE_ID_HPP
#define OMNI_CORE_ID_HPP

#include <omni/core/core.hpp>
#include <omni/core/domain.hpp>

#include <string>
#include <ostream>

namespace omni {
namespace core {

    /**
    An `id' is a globally unique identifier that is used throughout omni to identify parts of the context such as variables, types,
    functions, classes, enums, and even statements and expressions.
    **/
    class OMNI_CORE_API id {
    public:
        id ();
        id (domain domain, std::string id);

        bool operator<(id const & rhs) const;
        bool operator==(id const & rhs) const;

        bool isValid () const;
        domain getDomain () const;
        std::string getId () const;

    private:
        domain _domain;
        std::string _id;
    };

    std::ostream OMNI_CORE_API & operator << (std::ostream & lhs, id const & rhs);

} // namespace core
} // namespace omni

#endif // include guard
