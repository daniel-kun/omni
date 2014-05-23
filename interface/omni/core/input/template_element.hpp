#ifndef OMNI_CORE_TEMPLATE_ELEMENT_HPP
#define OMNI_CORE_TEMPLATE_ELEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/input/syntax_suggestion.hpp>

#include <string>
#include <vector>

namespace omni {
namespace core {
namespace input {
class template_visitor;

/**
**/
class OMNI_CORE_API template_element {
public:
    template_element (
        syntax_element & parent,
        std::size_t templateIndex);

    virtual std::vector <std::string> suggest (std::string input) = 0;

    virtual std::shared_ptr <syntax_element> dive ();

    virtual void visit (template_visitor & visitor) = 0;

protected:
    syntax_element & _parent;
    std::size_t _templateIndex;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
