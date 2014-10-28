#include <omni/core/model/pure_expression.hpp>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info pure_expressionMetaInfo;
}

omni::core::model::pure_expression::pure_expression () :
    expression ()
{
}

omni::core::model::meta_info & omni::core::model::pure_expression::getStaticMetaInfo ()
{
    return omniMetaImpl::pure_expressionMetaInfo;
}

omni::core::model::meta_info & omni::core::model::pure_expression::getMetaInfo () const
{
    return getStaticMetaInfo ();
}
