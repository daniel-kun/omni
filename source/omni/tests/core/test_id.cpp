#include <omni/core/id.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (idTests)

/*
Tests the most common functions omni::core::id:
* the constructors
* isValid ()
* getId ()
* getDomain ()
*/
BOOST_AUTO_TEST_CASE (common)
{
    using namespace omni::core;
    id i1;
    BOOST_CHECK (! i1.isValid ());
    BOOST_CHECK_EQUAL (i1.getId (), std::string ());
    BOOST_CHECK_EQUAL (i1.getDomain (), domain::invalid);

    const std::string idString = "ABCDEFG";
    id i2 (domain::function, idString);
    BOOST_CHECK (i2.isValid ());
    BOOST_CHECK_EQUAL (i2.getId (), idString);
    BOOST_CHECK_EQUAL (i2.getDomain (), domain::function);
}

/*
Tests the operator< of omni::core::id with two invalid ids.
*/
BOOST_AUTO_TEST_CASE (operatorLessWithTwoInvalids)
{
    using namespace omni::core;
    id invalid1;
    id invalid2;
    BOOST_CHECK (! (invalid1 < invalid2));
}

/*
Tests the operator< of omni::core::id with two ids in the same domain, but with different ids.
*/
BOOST_AUTO_TEST_CASE (operatorLessWithSameDomainAndDifferentIds)
{
    using namespace omni::core;
    const std::string idString1 = "ABCDEFG";
    const std::string idString2 = "HIJKLMN";
    id id1 (domain::function, idString1);
    id id2 (domain::function, idString2);
    BOOST_CHECK_EQUAL (id1 < id2, idString1 < idString2);
    BOOST_CHECK_EQUAL (id2 < id1, idString2 < idString1);
}

/*
Tests the operator< of omni::core::id with two ids in different domains, but with the same id.
*/
BOOST_AUTO_TEST_CASE (operatorLessWithDifferentDomainsAndSameId)
{
    using namespace omni::core;
    const std::string idString = "ABCDEFG";
    domain domain1 = domain::function;
    domain domain2 = domain::expression;
    id id1 (domain1, idString);
    id id2 (domain2, idString);
    BOOST_CHECK_EQUAL (id1 < id2, domain1 < domain2);
    BOOST_CHECK_EQUAL (id2 < id1, domain2 < domain1);
}

/*
Tests the operator< of omni::core::id with two ids in different domains and different ids.
*/
BOOST_AUTO_TEST_CASE (operatorLessWithDifferentDomainsAndDifferentIds)
{
    using namespace omni::core;
    const std::string idString1 = "ABCDEFG";
    const std::string idString2 = "HIJKLMN";
    domain domain1 = domain::function;
    domain domain2 = domain::expression;
    id id1 (domain1, idString1);
    id id2 (domain2, idString2);
    // When the domain differs, only the domain is relevant for the comparison:
    BOOST_CHECK_EQUAL (id1 < id2, domain1 < domain2);
    BOOST_CHECK_EQUAL (id2 < id1, domain2 < domain1);
}

BOOST_AUTO_TEST_SUITE_END ()
