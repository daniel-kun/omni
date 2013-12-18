#ifndef OMNI_CORE_ID_DOMAIN_HPP
#define OMNI_CORE_ID_DOMAIN_HPP

#include <omni/core/core.hpp>

namespace omni {
namespace core {

    /**
    Every object in the omni context that has an `id' resides in a specific domain to minimize potential id collision and
    to easily see what kind of object is referenced by a specifid id. When storing, showing or reading an id the domain should
    always be accompanying the actual id - e.g. as a prefix.
    **/
    enum class domain {
        invalid,
        first,
        variable = first,
        function,
        block,
        last = block,
    };

} // namespace core
} // namespace omni

#endif // include guard
