#ifndef OMNI_CORE_CAST_EXPRESSION_HPP
#define OMNI_CORE_CAST_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/expression.hpp>

namespace omni {
namespace core {

/**
cast_expression is an abstract base class for different other, concrete casts.
**/
class OMNI_CORE_API cast_expression : public expression {
};

}
}

#endif // include guard
