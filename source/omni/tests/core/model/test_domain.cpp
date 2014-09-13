#include <omni/core/domain.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/binary_operator_expression.hpp>
#include <omni/core/model/bitcast_expression.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/do_while_statement.hpp>
#include <omni/core/model/external_function.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/function_call_expression.hpp>
#include <omni/core/model/if_statement.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/parameter.hpp>
#include <omni/core/model/return_statement.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/variable_assignment_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/variable_expression.hpp>
#include <omni/core/model/while_statement.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (domainTests)

BOOST_AUTO_TEST_CASE (allDomains)
{
    using namespace omni::core;
    using namespace omni::core::model;
    context c;
    auto literal1 = std::make_shared <builtin_literal_expression <int>> (c, 10);
    auto literal2 = std::make_shared <builtin_literal_expression <int>> (c, 20);
    BOOST_CHECK_EQUAL (domain::binary_operator_expression,
                       binary_operator_expression (c, binary_operator_expression::binary_operation::binary_plus_operation, literal1, literal2).getDomain ());
    BOOST_CHECK_EQUAL (domain::bitcast_expression,
                       bitcast_expression (nullptr, nullptr).getDomain ());
    BOOST_CHECK_EQUAL (domain::block,
                       block ().getDomain ());
    BOOST_CHECK_EQUAL (domain::builtin_literal_expression,
                       literal1->getDomain ());
    BOOST_CHECK_EQUAL (domain::do_while_statement,
                       do_while_statement ().getDomain ());
    BOOST_CHECK_EQUAL (domain::external_function,
                       external_function (std::string (), std::string (), nullptr).getDomain ());
    BOOST_CHECK_EQUAL (domain::function,
                       function (std::string (), nullptr, nullptr).getDomain ());
    BOOST_CHECK_EQUAL (domain::function_call_expression,
                       function_call_expression ().getDomain ());
    BOOST_CHECK_EQUAL (domain::if_statement,
                       if_statement (nullptr, nullptr, nullptr).getDomain ());
    BOOST_CHECK_EQUAL (domain::module,
                       module (c).getDomain ());
    BOOST_CHECK_EQUAL (domain::parameter,
                       parameter (nullptr, std::string ()).getDomain ());
    BOOST_CHECK_EQUAL (domain::return_statement,
                       return_statement ().getDomain ());
    BOOST_CHECK_EQUAL (domain::type,
                       type (c, type_class::t_boolean).getDomain ());
    BOOST_CHECK_EQUAL (domain::variable_assignment_expression,
                       variable_assignment_expression (std::make_shared <variable_declaration_expression> (literal1->getType ()), literal1).getDomain ());
    BOOST_CHECK_EQUAL (domain::variable_declaration_expression,
                       variable_declaration_expression ().getDomain ());
    BOOST_CHECK_EQUAL (domain::variable_expression,
                       variable_expression (std::make_shared <variable_declaration_expression> (c.sharedBasicType (type_class::t_boolean))).getDomain ());
    BOOST_CHECK_EQUAL (domain::while_statement,
                       while_statement ().getDomain ());
}

BOOST_AUTO_TEST_SUITE_END ()
