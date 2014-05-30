#include <omni/core/model/entity.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/auto_unit_test.hpp>

/**
Implements the necessary methods that are abstract in entity, so entity can be unit-tested (of course not the abstract parts).
**/
class testable_entity : public omni::core::model::entity {
public:
        void setComponent (omni::core::domain domain, std::string name, std::shared_ptr <entity> entity) override {
            entity::setComponent (domain, name, entity);
        }

        omni::core::domain getDomain () const override {
            throw std::runtime_error ("testable_entity:getDomain (): Not implemented");
        }
};

BOOST_AUTO_TEST_SUITE (entityTests)

/*
Tests the ctors of entity.
*/
BOOST_AUTO_TEST_CASE (ctors)
{
    testable_entity e1;
    BOOST_CHECK_EQUAL (e1.getName (), std::string ());
    //BOOST_CHECK_EQUAL (e1.getId (), )
}

BOOST_AUTO_TEST_SUITE_END ()
