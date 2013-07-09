#ifndef OMNI_CORE_OBJECT_HPP
#define OMNI_CORE_OBJECT_HPP

#include <omni/core/core.hpp>
#include <boost/signal.hpp>
#include <string>
#include <memory>

// class definition

namespace omni {
namespace core {

class object_impl;

/**
object is the base class for all classes that belong to the Omni Language Structure (OLS) in the omni source code.
object defines a static function getTypeName returning the string "object";
By convention, every type directly or indirectly deriving from object needs to declare a function with the
same name getTypeName and the return type std::string const &, too. This is a minimal type of RTTI.
**/
class OMNI_CORE_API object {
public:
			  object ();
	virtual ~ object ();

	boost::signal <void (object & sender, std::string const & propertyName)> & propertyChangedSignal ();

	static std::string const & getTypeName ();

protected:
	void onPropertyChanged (std::string const & propertyName);

private:
	std::shared_ptr <object_impl> _impl;
}; // class object

} // namespace core
} // namespace omni

#endif // include guard
