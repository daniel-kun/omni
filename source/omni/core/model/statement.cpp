#include <omni/core/model/statement.hpp>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info statementMetaInfo;
}

omni::core::model::statement::statement () :
    scope ()
{
}

omni::core::model::statement::~statement ()
{
}

omni::core::model::meta_info & omni::core::model::statement::getStaticMetaInfo ()
{
    return omniMetaImpl::statementMetaInfo;
}

omni::core::model::meta_info & omni::core::model::statement::getMetaInfo () const
{
    return getStaticMetaInfo ();
}
