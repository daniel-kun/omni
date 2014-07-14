#ifndef OMNI_CORE_MODEL_META_INFO_HPP
#define OMNI_CORE_MODEL_META_INFO_HPP

#include <omni/core/core.hpp>

#include <boost/any.hpp>

#include <memory>
#include <vector>

namespace omni {
namespace core {
namespace input {
class syntax_element;
}
}
}

namespace omni {
namespace core {
namespace model {
class entity;

class meta_info {
public:
    meta_info ();

    virtual std::shared_ptr <entity> createInstance (std::vector <boost::any> parameters) = 0;

    virtual std::string getName() const = 0;
    virtual std::shared_ptr <omni::core::input::syntax_element> getSyntaxElement () const = 0;
};

}
}
}

#endif // include guard
