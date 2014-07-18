#ifndef OMNI_CORE_MODEL_META_INFO_HPP
#define OMNI_CORE_MODEL_META_INFO_HPP

#include <omni/core/core.hpp>

#include <memory>
#include <vector>

namespace omni {
namespace core {
namespace syntax {
class syntax_template;
class syntax_node;
}
}
}

namespace omni {
namespace core {
namespace model {
class entity;
class meta_if_statement;

class meta_info {
public:
    meta_info ();

    virtual std::string getName() const = 0;
    virtual std::shared_ptr <omni::core::syntax::syntax_template> getSyntax () const = 0;
    virtual std::shared_ptr <entity> createFromSyntax (omni::core::syntax::syntax_node syntax) = 0;

    static meta_if_statement & metaIfStatement ();
};

}
}
}

#endif // include guard
