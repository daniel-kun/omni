#ifndef OMNI_CORE_SYNTAX_TREE_PARSER_XML_HPP
#define OMNI_CORE_SYNTAX_TREE_PARSER_XML_HPP

#include <omni/core/core.hpp>

#include <istream>
#include <memory>

namespace omni {
namespace core {
namespace input {
class syntax_element;

/**
Parses an XML file and emits a root syntax_element (usually for the 'statement' model entity).

The XML syntax is as follows:

<syntax> <!-- Obligatory root node -->
    <abstract name="some_syntax_element"> <!-- read as an abstract_syntax_element, contains other abstract_syntax_elements or concrete_syntax_elements. -->
        <concrete name="some_other_name> <!-- read as an concrete_syntax_element, contains template_elements. -->
            <fixed text="asdf"/> <!-- a fixed_template_element with the text "asdf" -->
            <repeater prefix=","> <!-- a repeater_template_element that repeats it's context and prefixes "," in front of every other repeated element. -->
                <syntax name="foo" type="some_syntax_element"/> <!-- A placeholder for a syntax_element (abstract or concrete) of the given type. -->
            </repeater>
        </concrete>
    </abstract>
</syntax>
**/
class OMNI_CORE_API syntax_tree_parser_xml {
public:
    static std::shared_ptr <syntax_element> parse (std::istream & stream);
};

}
}
}

#endif // include guard
