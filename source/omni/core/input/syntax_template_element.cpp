#include <omni/core/input/syntax_template_element.hpp>
#include <omni/core/input/syntax_element.hpp>
#include <omni/core/input/syntax_suggestion.hpp>
#include <omni/core/input/template_visitor.hpp>

omni::core::input::syntax_template_element::syntax_template_element (syntax_element & parent, std::size_t templateIndex, std::shared_ptr <syntax_element> target) :
    template_element (parent, templateIndex),
    _target (target)
{
}

std::vector <std::string> omni::core::input::syntax_template_element::suggest (std::string input)
{
    return std::vector <std::string> ();
}

std::shared_ptr <omni::core::input::syntax_element> omni::core::input::syntax_template_element::dive ()
{
    return _target;
}

std::shared_ptr <omni::core::input::syntax_element> omni::core::input::syntax_template_element::getSyntaxElement () const
{
    return _target;
}

void omni::core::input::syntax_template_element::visit (template_visitor & visitor)
{
    visitor.visitSyntaxTemplateElement (* this);
}
