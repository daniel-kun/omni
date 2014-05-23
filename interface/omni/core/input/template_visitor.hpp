#ifndef OMNI_CORE_INPUT_TEMPLATE_VISITOR_HPP
#define OMNI_CORE_INPUT_TEMPLATE_VISITOR_HPP

#include <omni/core/core.hpp>

namespace omni {
namespace core {
namespace input {
class syntax_template_element;
class variable_template_element;
class regex_template_element;
class fixed_template_element;
class repeater_template_element;

/**
**/
class OMNI_CORE_API template_visitor {
public:
    virtual void visitSyntaxTemplateElement     (syntax_template_element & element) = 0;
    virtual void visitVariableTemplateElement   (variable_template_element & element) = 0;
    virtual void visitRegexTemplateElement      (regex_template_element & element) = 0;
    virtual void visitFixedTemplateElement      (fixed_template_element & element) = 0;
    virtual void visitRepeaterTemplateElement   (repeater_template_element & element) = 0;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
