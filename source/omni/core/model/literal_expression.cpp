#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/not_implemented_error.hpp>

#include <sstream>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info literal_expressionMetaInfo;
}

/**
@brief Creates a new literal_expression from the human-readable `text'.

The format of a human-readable text that can be converted to a literal follows this form:
<number> <type specifier>

The numer can be typed in the current locale's form, e.g. in English environments, it uses "," as the thousands separator and "." as the decimal separator,
whereas e.g. in German environments, "." as the thousands separator and "," as the decimal separator.

When the same literal will be converted to text on a different locale, it will automatically adapt to the new environment. The internal storage is binary and
therefore independent from the locale.

The resulting object will be a subclass of literal_expression, for example builtin_literal_expression.
@param context The context that the literal should be created in.
@param text The text that represents the literal and should be converted to a literal.
@param originatingLiteral If the text was provided as a modification of an existing literal, pass that literal as the `originatingLiteral'. A missing
type specifier will then be derived from the origin.
@return A new literal_expression, if text can be converted to any kind of literal_expression. nullptr, if text is empty or can not be converted.
**/
std::shared_ptr <omni::core::model::literal_expression> omni::core::model::literal_expression::fromString (
    context & context,
    std::string const & text,
    literal_expression * originatingLiteral)
{
    unsigned int value = 0u;
    std::stringstream str (text);
    str >> value;
    auto result = std::make_shared <builtin_literal_expression <int>> (context, value);
    return result;
}

omni::core::model::meta_info & omni::core::model::literal_expression::getStaticMetaInfo ()
{
    return omniMetaImpl::literal_expressionMetaInfo;
}

omni::core::model::meta_info & omni::core::model::literal_expression::getMetaInfo () const
{
    return literal_expression::getStaticMetaInfo ();
}

/**
@brief Connects a handler to the ValueChanged signal that is emitted, after the current value of this builtin_literal has been changed.
@param handler The handler that will be called after the current value changed.
@return A signal connection that can be used disconnect this handler.
**/
boost::signals2::connection omni::core::model::literal_expression::connectValueChanged (ValueChangedSignal::slot_type handler)
{
    return _valueChangedSignal.connect (handler);
}

/**
@brief Emits the signals ValueChanged and Changed, int his order.

When overriding this function, make sure to call the base class implementation. Otherwise, all other functionality that depends on the ValueChanged and Changed signals will break.
@param oldValue The value that this builtin_literal had, before it was changed.
@param newValue The new, current value of this builtin_literal.
**/
void omni::core::model::literal_expression::valueChanged (boost::any oldValue, boost::any newValue)
{
    _valueChangedSignal (* this, oldValue, newValue);
    changed ();
}
