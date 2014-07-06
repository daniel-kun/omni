#include <omni/core/input/syntax_tree_parser_xml.hpp>
#include <omni/core/input/syntax_element.hpp>
#include <omni/core/input/abstract_syntax_element.hpp>
#include <omni/core/input/concrete_syntax_element.hpp>

#include <rapidxml/rapidxml.hpp>

#include <memory>
#include <stdexcept>

namespace {
std::shared_ptr <omni::core::input::abstract_syntax_element> parseAbstract (rapidxml::xml_node <char> * node)
{
    /*
    using namespace rapidxml;

    auto result = std::make_shared <omni::core::input::abstract_syntax_element> ();
    result->setName (node->first_attribute ("name")->value ());
    xml_node <char> * child = node->first_node ();
    return result;
    */
    return std::make_shared <omni::core::input::abstract_syntax_element> ();
}
}

template <typename T>
class array_deleter : public std::default_delete <char> {
public:
    void operator() (T *p)
    {
        delete [] p;
    }
};

std::shared_ptr <omni::core::input::syntax_element> omni::core::input::syntax_tree_parser_xml::parse (std::istream & stream)
{
    using namespace rapidxml;

    const std::string nodeNameConcrete = "concrete";
    const std::string nodeNameAbstract = "abstract";
    const std::string nodeNameFixed = "fixed";
    const std::string nodeNameVariable = "variable";
    const std::string nodeNameSyntax = "syntax";
    const std::string nodeNameIndentRight = "indentright";
    const std::string nodeNameIndentLeft = "indentleft";

    std::string content;
    while (stream >> content) {
    }
    xml_document <> doc;
    auto deleter = [] (char *p) -> void { delete [] p;};
    std::unique_ptr <char, decltype (deleter)> buffer (new char [content.size ()], deleter);
    std::copy (content.begin (), content.end (), buffer.get ());
    doc.parse <0> (buffer.get ());
    xml_node <char> * root = doc.first_node ();
    if (root->name () != std::string ("syntax")) {
        throw std::logic_error ("Invalid XML syntax for syntax description file.");
    }

    xml_node <char> * node = root->first_node ();
    while (node != nullptr) {
        if (node->name () == nodeNameAbstract) {
            auto abstract = parseAbstract (node);
        } else if (node->name () == nodeNameConcrete) {
        }        
    }

    return nullptr;
}
