#ifndef OMNI_TAKE2_CONTEXT_PART_HPP
#define OMNI_TAKE2_CONTEXT_PART_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/id.hpp>
#include <string>

namespace omni {
namespace take2 {

	/**
	Base class for all information that is part of a context, such as variable declarations.
	(later: function declarations, etc.).
	**/
	class OMNI_TAKE2_API context_part {
	public:
        context_part ();
        context_part (std::string const & name);
		virtual ~ context_part () = 0;

		std::string getName () const;
		void setName (const std::string & name);

        void setId (id newId);
		id getId () const;

    private:
        std::string _name;
        id _id;
	};

} // namespace take2
} // namespace omni

#endif // include guard
