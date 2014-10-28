#include <omni/core/model/cast_expression.hpp>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info cast_expressionMetaInfo;
}

omni::core::model::cast_expression::cast_expression () :
    pure_expression ()
{
}

omni::core::model::meta_info & omni::core::model::cast_expression::getStaticMetaInfo ()
{
    return omniMetaImpl::cast_expressionMetaInfo;
}

omni::core::model::meta_info & omni::core::model::cast_expression::getMetaInfo () const
{
    return getStaticMetaInfo ();
}
