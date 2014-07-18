#ifndef OMNI_CORE_MODEL_META_TEMPLATE_HPP
#define OMNI_CORE_MODEL_META_TEMPLATE_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/meta_info.hpp>

namespace omni {
namespace core {
namespace model {
class entity;

/**
@class meta_template meta_template.hpp omni/core/model/meta_template.hpp
@brief Provides meta-information about the class `template'.
@see meta_info
**/
class meta_template : public meta_info {
public:
    meta_template ();

    std::string getName() const override;
    std::shared_ptr <omni::core::syntax::syntax_template> getSyntax () const override;
    std::shared_ptr <entity> createFromSyntax (omni::core::syntax::syntax_node syntax) override;
};

}
}
}

#endif // include guard
