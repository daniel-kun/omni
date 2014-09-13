#include <omni/core/model/literal_expression.hpp>
#include <omni/core/not_implemented_error.hpp>

/**
@brief Creates a new literal_expression from the human-readable `text'.

The resulting object will be a subclass of literal_expression, for example builtin_literal_expression.
@return A new literal_expression, if text can be converted to any kind of literal_expression. nullptr, if text is empty or can not be converted.
**/
std::shared_ptr <omni::core::model::literal_expression> omni::core::model::literal_expression::fromString (std::string const & text)
{
    throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
}

/**
@brief Connects a handler to the ValueChanged signal that is emitted, after the current value of this builtin_literal has been changed.
@param handler The handler that will be called with the current value changed.
@return A signal connection that can be used disconnect this handler.
**/
boost::signals2::connection omni::core::model::literal_expression::connectValueChanged (ValueChangedSignal::slot_type handler)
{
    return _valueChangedSignal.connect (handler);
}

/**
@brief Emits the signal ValueChanged.

When overriding this function, make sure to call the base class implementation. Otherwise, all other functionality that depends on the ValueChanged signal will break.
@param oldValue The value that this builtin_literal had, before it was changed.
@param newValue The new, current value of this builtin_literal.
**/
void omni::core::model::literal_expression::valueChanged (boost::any oldValue, boost::any newValue)
{
    _valueChangedSignal (* this, oldValue, newValue);
}
