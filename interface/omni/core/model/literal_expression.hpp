#ifndef OMNI_CORE_MODEL_LITERAL_EXPRESSION_HPP
#define OMNI_CORE_MODEL_LITERAL_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/pure_expression.hpp>

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
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
