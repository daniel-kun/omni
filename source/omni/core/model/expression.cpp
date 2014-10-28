#include <omni/core/model/expression.hpp>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info expressionMetaInfo;
}

omni::core::model::expression::expression () :
    statement ()
{
}

omni::core::model::meta_info & omni::core::model::expression::getStaticMetaInfo ()
{
    return omniMetaImpl::expressionMetaInfo;
}

omni::core::model::meta_info & omni::core::model::expression::getMetaInfo () const
{
    return getStaticMetaInfo ();
}
