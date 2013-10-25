#ifndef OMNI_TAKE2_CONTEXT_PART_HPP
#define OMNI_TAKE2_CONTEXT_PART_HPP

#include <omni/take2/take2.hpp>
#include <string>

namespace omni {
namespace take2 {
    class id;

	/**
	Base class for all information that is part of a context, such as variable declarations.
	(later: function declarations, etc.).
	**/
	class OMNI_TAKE2_API context_part {
	public:
		virtual ~ context_part () = 0;

		std::string getName () const;
		std::string setName (const std::string & name);

		const id & getId () const;
	};

} // namespace take2
} // namespace omni

#endif // include guard
