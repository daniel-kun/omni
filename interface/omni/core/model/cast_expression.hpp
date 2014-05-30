#ifndef OMNI_CORE_CAST_EXPRESSION_HPP
#define OMNI_CORE_CAST_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/pure_expression.hpp>

namespace omni {
namespace core {
namespace model {

    /**
    Abstract.
    cast_expression is an abstract base class for different other, concrete casts.
    Casts never change the item that is being casted, hence they are "pure".
    **/
    class OMNI_CORE_API cast_expression : public pure_expression {
    public:
        cast_expression ();
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
