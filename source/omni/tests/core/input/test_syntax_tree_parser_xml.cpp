#include <omni/core/input/syntax_tree_parser_xml.hpp>
#include <omni/core/input/syntax_element.hpp>

#include <boost/test/unit_test.hpp>

#include <fstream>

/*
BOOST_AUTO_TEST_SUITE (inputSyntaxTreeParserXmlTests)

BOOST_AUTO_TEST_CASE (basic)
{
    using namespace omni::core::input;
    
    std::ifstream str ("../resources/syntax.xml");
    std::shared_ptr <syntax_element> statement = syntax_tree_parser_xml::parse (str);
    BOOST_CHECK_EQUAL (statement->getName (), "statement");
}

BOOST_AUTO_TEST_SUITE_END ()
*/
