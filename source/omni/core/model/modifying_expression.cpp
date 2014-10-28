#include <omni/core/model/modifying_expression.hpp>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info modifying_expressionMetaInfo;
}

omni::core::model::modifying_expression::modifying_expression () :
    expression ()
{
}

omni::core::model::meta_info & omni::core::model::modifying_expression::getStaticMetaInfo ()
{
    return omniMetaImpl::modifying_expressionMetaInfo;
}

omni::core::model::meta_info & omni::core::model::modifying_expression::getMetaInfo () const
{
    return getStaticMetaInfo ();
}
