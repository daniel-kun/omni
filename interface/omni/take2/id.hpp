#ifndef OMNI_TAKE2_ID_HPP
#define OMNI_TAKE2_ID_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/id_domain.hpp>
#include <string>

namespace omni {
namespace take2 {

	/**
	An `id' is a globally unique identifier that is used throughout omni to identify parts of the context such as variables, types,
	functions, classes, enums, and even statements and expressions.
	**/
	class OMNI_TAKE2_API id {
	public:
		std::string getId () const;
	};

} // namespace take2
} // namespace omni

#endif // include guard
