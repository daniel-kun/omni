#ifndef OMNI_CORE_MODEL_LITERAL_EXPRESSION_HPP
#define OMNI_CORE_MODEL_LITERAL_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/pure_expression.hpp>

#ifndef Q_MOC_RUN
#include <boost/any.hpp>
#include <boost/signals2.hpp>
#endif

namespace omni {
namespace core {
class context;
}}

namespace omni {
namespace core {
namespace model {

    /**
    @class literal_expression literal_expression.hpp omni/core/model/literal_expression.hpp
    @brief A literal_expression is an expression that returns a value that was already defined at compile time.

    literal_expression is abstract. Use the subclass builtin_literal_expression to create a literal.
    (class_literal_expression will be coming later, when classes are implemented.)
    **/
    class OMNI_CORE_API literal_expression : public pure_expression {
    public:
        typedef boost::signals2::signal <void (literal_expression & sender, boost::any oldValue, boost::any newValue)> ValueChangedSignal;

        boost::signals2::connection connectValueChanged (ValueChangedSignal::slot_type handler);

        virtual std::string toString (bool fullyQualified = true) const = 0;

        static std::shared_ptr <literal_expression> fromString (omni::core::context & context, std::string const & text, literal_expression * originatingLiteral);

    protected:
        virtual void valueChanged (boost::any oldValue, boost::any newValue);

    private:
        ValueChangedSignal _valueChangedSignal;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
