#include <omni/core/object.hpp>

/**
Implementation details for object
**/
class omni::core::object_impl {
public:
    boost::signal <void (object & sender, std::string const & propertyName)> _propertyChangedSignal;
};

// Implementation of object

omni::core::object::object () :
    _impl (new object_impl ())
{
}

omni::core::object::~ object ()
{
}

/**
Returns the signal that is emitted when a property of this object has changed.
Use it like this:
void myclass::example ()
{
    _someObject.propertyChangedSignal ().connect (bind(& myclass::handleObjectPropertyChanged, this));
}

void myclass::handleObjectPropertyChanged (object & sender, std::string propertyName)
{
    // handle changes of the property "propertyName" of the object "sender";
}

Hint: You should usually publically derive your object from boost::signal::trackable when connecting
to a signal. Otherwise, you have to store the result of signal.connect and call disconnect () to a appropriate time.
**/
boost::signal <void (omni::core::object & sender, std::string const & propertyName)> & omni::core::object::propertyChangedSignal ()
{
    return _impl->_propertyChangedSignal;
}

/**
Emits the propertyChangedSignal with this as the sender and the argument propertyName.
**/
void omni::core::object::onPropertyChanged (std::string const & propertyName)
{
    _impl->_propertyChangedSignal (* this, propertyName);
}

/**
Returns "object", the name of this type.
**/
std::string const & omni::core::object::getTypeName ()
{
    static std::string result ("object");
    return result;
}

