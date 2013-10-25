#ifndef OMNI_TAKE2_ID_DOMAIN_HPP
#define OMNI_TAKE2_ID_DOMAIN_HPP

#include <omni/take2/take2.hpp>

namespace omni {
namespace take2 {

	/**
	Every object in the omni context that has an `id' resides in a specific domain to minimize potential id collision and
	to easily see what kind of object is referenced by a specifid id. When storing, showing or reading an id the domain should
	always be accompanying the actual id - e.g. as a prefix.
	**/
	enum domain {
		variable_domain,
		function_domain,
		block_domain,
		variable_declaration_domain,
	};

} // namespace take2
} // namespace omni

#endif // include guard
