#include <omni/core/model/entity.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/scope.hpp>
#include <omni/core/model/meta_info.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/while_statement.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/auto_unit_test.hpp>

/**
Implements the necessary methods that are abstract in entity, so entity can be unit-tested (of course not the abstract parts).
**/
class testable_entity : public omni::core::model::entity {
public:
    testable_entity () :
        entity ()
    {
    }

    testable_entity (std::string const & name) :
        entity (name)
    {
    }

    testable_entity (omni::core::id entityId, std::string const & name) :
        entity (entityId, name)
    {
    }

    omni::core::model::meta_info & getMetaInfo () const override
    {
        return entity::getMetaInfo ();
    }

    void setComponent (omni::core::domain domain, std::string name, std::shared_ptr <entity> entity) override {
        entity::setComponent (domain, name, entity);
    }

    omni::core::domain getDomain () const override {
        throw std::runtime_error ("testable_entity:getDomain (): Not implemented");
    }
};

class test_entity_fixture {
public:
    test_entity_fixture () :
        c           (),
        mod         (c),
        varDecl     (std::make_shared <omni::core::model::variable_declaration_expression> ()),
        varBlock    (std::make_shared <omni::core::model::block> ()),
        whileStmt   (std::make_shared <omni::core::model::while_statement> ()),
        entity      ()
    {
        entity.setComponent (varDecl->getDomain (), "varDecl", varDecl);
        entity.setComponent (varBlock->getDomain (), "varBlock", varBlock);
        entity.setComponent (whileStmt->getDomain (), "whileStmt", whileStmt);
    }
protected:
    omni::core::context c;
    omni::core::model::module mod;
    std::shared_ptr <omni::core::model::variable_declaration_expression> varDecl;
    std::shared_ptr <omni::core::model::block> varBlock;
    std::shared_ptr <omni::core::model::while_statement> whileStmt;
    testable_entity entity;
};

BOOST_FIXTURE_TEST_SUITE (entityTests, test_entity_fixture)

/*
Tests the default-constructors of entity.
*/
BOOST_AUTO_TEST_CASE (ctor1)
{
    using namespace omni::core;
    testable_entity e1;
    BOOST_CHECK_EQUAL (e1.getMetaInfo ().getName (), "entity");
    BOOST_CHECK_EQUAL (e1.getName (), std::string ());
    BOOST_CHECK_EQUAL (e1.getId (), id ());
    BOOST_CHECK (! e1.getId ().isValid ());
}

/*
Tests the constructors of entity that specifies a name.
*/
BOOST_AUTO_TEST_CASE (ctor2)
{
    using namespace omni::core;
    std::string name = "Hello, World";
    testable_entity e1 (name);
    BOOST_CHECK_EQUAL (e1.getName (), name);
    BOOST_CHECK_EQUAL (e1.getId (), id ());
    BOOST_CHECK (! e1.getId ().isValid ());
}

/*
Tests the constructors of entity that specifies a name and an id.
*/
BOOST_AUTO_TEST_CASE (ctor3)
{
    using namespace omni::core;
    std::string name = "Hello, World";
    id i = id (domain::function, "ABCDEFG");
    testable_entity e1 (i, name);
    BOOST_CHECK_EQUAL (e1.getName (), name);
    BOOST_CHECK_EQUAL (e1.getId (), i);
    BOOST_CHECK_EQUAL (e1.getId ().isValid (), i.isValid ());
}

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;
    testable_entity e;
    meta_info & meta = entity::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (& meta, & e.getMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getName (), "entity");
    BOOST_CHECK (meta.getParent () == nullptr);
    BOOST_CHECK_EQUAL (meta.getChildCount (), 2u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & type::getStaticMetaInfo (),
        & scope::getStaticMetaInfo (),
    }));
}

/**
Tests the const and non-const versions of entity::getContext ().
**/
BOOST_AUTO_TEST_CASE (getContext)
{
    using namespace omni::core;
    using namespace omni::core::model;
    context c;
    module mod (c);
    auto body = std::make_shared <block> ();
    auto entity = std::make_shared <function> ("foo", c.sharedBasicType (type_class::t_boolean), body);

    BOOST_CHECK_EQUAL (entity->getContext (), static_cast <context *> (nullptr));
    BOOST_CHECK_EQUAL (static_cast <const function &> (* entity).getContext (), static_cast <const context *> (nullptr));

    BOOST_CHECK_EQUAL (body->getContext (), static_cast <context *> (nullptr));
    BOOST_CHECK_EQUAL (static_cast <const block &> (* body).getContext (), static_cast <const context *> (nullptr));

    mod.addFunction (entity);

    BOOST_CHECK_EQUAL (entity->getContext (), & c);
    BOOST_CHECK_EQUAL (static_cast <const function &> (* entity).getContext (),  & c);

    BOOST_CHECK_EQUAL (body->getContext (), & c);
    BOOST_CHECK_EQUAL (static_cast <const block &> (* body).getContext (), & c);
}

/**
Tests the const and non-const versions of entity::getModule ().
**/
BOOST_AUTO_TEST_CASE (getModule)
{
    using namespace omni::core;
    using namespace omni::core::model;
    context c;
    module mod (c);
    auto body = std::make_shared <block> ();
    auto entity = std::make_shared <function> ("foo", c.sharedBasicType (type_class::t_boolean), body);

    BOOST_CHECK_EQUAL (entity->getModule (), static_cast <module *> (nullptr));
    BOOST_CHECK_EQUAL (static_cast <const function &> (* entity).getModule (), static_cast <const module *> (nullptr));

    BOOST_CHECK_EQUAL (body->getModule (), static_cast <module *> (nullptr));
    BOOST_CHECK_EQUAL (static_cast <const block &> (* body).getModule (), static_cast <const module *> (nullptr));

    mod.addFunction (entity);

    BOOST_CHECK_EQUAL (entity->getModule (), & mod);
    BOOST_CHECK_EQUAL (static_cast <const function &> (* entity).getModule (),  & mod);

    BOOST_CHECK_EQUAL (body->getModule (), & mod);
    BOOST_CHECK_EQUAL (static_cast <const block &> (* body).getModule (), & mod);
}

/**
Tests the const and non-const versions of entity::getId ().
It especially tests whether an id is created as soon as an entity becomes part of a context.
**/
BOOST_AUTO_TEST_CASE (getId)
{
    using namespace omni::core;
    using namespace omni::core::model;
    context c;
    module mod (c);
    auto body = std::make_shared <block> ();
    auto entity = std::make_shared <function> ("foo", c.sharedBasicType (type_class::t_boolean), body);

    BOOST_CHECK_EQUAL (entity->getId (), id ());
    BOOST_CHECK_EQUAL (static_cast <const function &> (* entity).getId (), id ());

    BOOST_CHECK_EQUAL (body->getId (), id ());
    BOOST_CHECK_EQUAL (static_cast <const block &> (* body).getId (), id ());

    mod.addFunction (entity);

    BOOST_CHECK (entity->getId ().isValid ());
    BOOST_CHECK (static_cast <const function &> (* entity).getId ().isValid ());

    BOOST_CHECK (body->getId ().isValid ());
    BOOST_CHECK (static_cast <const block &> (* body).getId ().isValid ());
}

/*
Tests various functions that implement the `components' concept.
*/
BOOST_AUTO_TEST_CASE (getComponent)
{
    using namespace omni::core;
    using namespace omni::core::model;

    BOOST_CHECK_EQUAL (entity.getComponent (varDecl->getDomain (), "varDecl"), varDecl);
    BOOST_CHECK_EQUAL (entity.getComponent (varBlock->getDomain (), "varBlock"), varBlock);
    BOOST_CHECK_EQUAL (entity.getComponent (whileStmt->getDomain (), "whileStmt"), whileStmt);
    BOOST_CHECK (entity.getComponent (domain::while_statement, "varDecl") == nullptr);
    BOOST_CHECK (entity.getComponent (varDecl->getDomain (), "varDecl2") == nullptr);
    const omni::core::model::entity & constEntity = entity;
    BOOST_CHECK (constEntity.getComponent (domain::while_statement, "varDecl") == nullptr);
    BOOST_CHECK (constEntity.getComponent (varDecl->getDomain (), "varDecl2") == nullptr);
}


BOOST_AUTO_TEST_CASE (getComponents)
{
    using namespace omni::core;
    using namespace omni::core::model;
    BOOST_CHECK (entity.getComponents (domain::while_statement).find ("whileStmt")->second != nullptr);
    BOOST_CHECK (entity.getComponents ().find (domain::while_statement)->second.find ("whileStmt")->second != nullptr);
    const omni::core::model::entity & constEntity = entity;
    BOOST_CHECK (constEntity.getComponents (domain::while_statement).find ("whileStmt")->second != nullptr);
    BOOST_CHECK (constEntity.getComponents ().find (domain::while_statement)->second.find ("whileStmt")->second != nullptr);
}

BOOST_AUTO_TEST_CASE (getComponentAs)
{
    using namespace omni::core;
    using namespace omni::core::model;
    const omni::core::model::entity & constEntity = entity;
    // correct type, correct domain, correct name:
    BOOST_CHECK (constEntity.getComponentAs <variable_declaration_expression> (domain::variable_declaration_expression, "varDecl") != nullptr);
    BOOST_CHECK (constEntity.getComponentAs <block> (domain::block, "varBlock") != nullptr);
    BOOST_CHECK (constEntity.getComponentAs <while_statement> (domain::while_statement, "whileStmt") != nullptr);

    // correct type, correct domain, incorrect name:
    BOOST_CHECK (constEntity.getComponentAs <variable_declaration_expression> (domain::variable_declaration_expression, "varDecl2") == nullptr);
    BOOST_CHECK (constEntity.getComponentAs <block> (domain::block, "varBlock2") == nullptr);
    BOOST_CHECK (constEntity.getComponentAs <while_statement> (domain::while_statement, "whileStmt2") == nullptr);

    // correct type, incorrect domain, correct name:
    BOOST_CHECK (constEntity.getComponentAs <variable_declaration_expression> (domain::block, "varDecl") == nullptr);
    BOOST_CHECK (constEntity.getComponentAs <block> (domain::while_statement, "varBlock") == nullptr);
    BOOST_CHECK (constEntity.getComponentAs <while_statement> (domain::variable_declaration_expression, "whileStmt") == nullptr);

    // incorrect type, correct domain, correct name:
    BOOST_CHECK (constEntity.getComponentAs <block> (domain::variable_declaration_expression, "varDecl") == nullptr);
    BOOST_CHECK (constEntity.getComponentAs <while_statement> (domain::block, "varBlock") == nullptr);
    BOOST_CHECK (constEntity.getComponentAs <variable_declaration_expression> (domain::while_statement, "whileStmt") == nullptr);

}

BOOST_AUTO_TEST_CASE (getComponentsStartingWith)
{
    using namespace omni::core;
    using namespace omni::core::model;

    variable_declaration_expression * found1 = nullptr;
    // we expect to find exactly one result:
    for (auto i : entity.getComponentsStartingWith (domain::variable_declaration_expression, "var")) {
        BOOST_CHECK (found1 == nullptr);
        if (found1 == nullptr) {
            found1 = dynamic_cast <variable_declaration_expression *> (i.second.get ());
            BOOST_CHECK (found1 != nullptr);
        }
    }
    BOOST_CHECK (found1 == varDecl.get ());

    auto varDecl2 = std::make_shared <variable_declaration_expression> ();
    entity.setComponent (domain::variable_declaration_expression, "varDecl2", varDecl2);
    found1 = nullptr;
    variable_declaration_expression * found2 = nullptr;
    for (auto i : entity.getComponentsStartingWith (domain::variable_declaration_expression, "varDecl")) {
        auto iDecl = dynamic_cast <variable_declaration_expression *> (i.second.get ());
        if (iDecl == varDecl.get ()) {
            found1 = iDecl;
        }
        if (iDecl == varDecl2.get ()) {
            found2 = iDecl;
        }
    }
    BOOST_CHECK_EQUAL (found1, varDecl.get ());
    BOOST_CHECK_EQUAL (found2, varDecl2.get ());

    auto varDecl3 = std::make_shared <variable_declaration_expression> ();
    entity.setComponent (domain::variable_declaration_expression, "varDecl3", varDecl3);
    found1 = nullptr;
    found2 = nullptr;
    variable_declaration_expression * found3 = nullptr;
    for (auto i : entity.getComponentsStartingWith (domain::variable_declaration_expression, "varDecl")) {
        auto iDecl = dynamic_cast <variable_declaration_expression *> (i.second.get ());
        if (iDecl == varDecl.get ()) {
            found1 = iDecl;
        }
        if (iDecl == varDecl2.get ()) {
            found2 = iDecl;
        }
        if (iDecl == varDecl3.get ()) {
            found3 = iDecl;
        }
    }
    BOOST_CHECK_EQUAL (found1, varDecl.get ());
    BOOST_CHECK_EQUAL (found2, varDecl2.get ());
    BOOST_CHECK_EQUAL (found3, varDecl3.get ());
}

BOOST_AUTO_TEST_CASE (getComponentsStartingWithAs)
{
    using namespace omni::core;
    using namespace omni::core::model;

    variable_declaration_expression * found1 = nullptr;
    // we expect to find exactly one result:
    for (auto i : entity.getComponentsStartingWithAs <variable_declaration_expression> (domain::variable_declaration_expression, "var")) {
        BOOST_CHECK (found1 == nullptr);
        if (found1 == nullptr) {
            found1 = i.second.get ();
            BOOST_CHECK (found1 != nullptr);
        }
    }
    BOOST_CHECK (found1 == varDecl.get ());

    auto varDecl2 = std::make_shared <variable_declaration_expression> ();
    entity.setComponent (domain::variable_declaration_expression, "varDecl2", varDecl2);
    found1 = nullptr;
    variable_declaration_expression * found2 = nullptr;
    for (auto i : entity.getComponentsStartingWithAs <variable_declaration_expression> (domain::variable_declaration_expression, "varDecl")) {
        auto iDecl = i.second.get ();
        if (iDecl == varDecl.get ()) {
            found1 = iDecl;
        }
        if (iDecl == varDecl2.get ()) {
            found2 = iDecl;
        }
    }
    BOOST_CHECK_EQUAL (found1, varDecl.get ());
    BOOST_CHECK_EQUAL (found2, varDecl2.get ());

    auto varDecl3 = std::make_shared <variable_declaration_expression> ();
    entity.setComponent (domain::variable_declaration_expression, "varDecl3", varDecl3);
    found1 = nullptr;
    found2 = nullptr;
    variable_declaration_expression * found3 = nullptr;
    for (auto i : entity.getComponentsStartingWithAs <variable_declaration_expression> (domain::variable_declaration_expression, "varDecl")) {
        auto iDecl = i.second.get ();
        if (iDecl == varDecl.get ()) {
            found1 = iDecl;
        }
        if (iDecl == varDecl2.get ()) {
            found2 = iDecl;
        }
        if (iDecl == varDecl3.get ()) {
            found3 = iDecl;
        }
    }
    BOOST_CHECK_EQUAL (found1, varDecl.get ());
    BOOST_CHECK_EQUAL (found2, varDecl2.get ());
    BOOST_CHECK_EQUAL (found3, varDecl3.get ());
}

BOOST_AUTO_TEST_CASE (clearComponents)
{
    BOOST_CHECK_EQUAL (entity.getComponents ().size (), 3u);
    entity.clearComponents ();
    BOOST_CHECK_EQUAL (entity.getComponents ().size (), 0u);
}

BOOST_AUTO_TEST_CASE (clearComponentsByDomain)
{
    using namespace omni::core;
    BOOST_CHECK_EQUAL (entity.getComponents (domain::block).size (), 1u);
    entity.clearComponents (domain::block);
    BOOST_CHECK_EQUAL (entity.getComponents (domain::block).size (), 0u);
}

BOOST_AUTO_TEST_CASE (removeComponentByDomainAndName)
{
    using namespace omni::core;
    BOOST_CHECK_EQUAL (entity.getComponents (domain::block).size (), 1u);
    BOOST_CHECK (entity.removeComponent (domain::block, "varBlock"));
    BOOST_CHECK_EQUAL (entity.getComponents (domain::block).size (), 0u);
}

BOOST_AUTO_TEST_CASE (removeComponentByDomainAndPointer)
{
    using namespace omni::core;
    BOOST_CHECK_EQUAL (entity.getComponents (domain::block).size (), 1u);
    BOOST_CHECK (entity.removeComponent (domain::block, varBlock));
    BOOST_CHECK_EQUAL (entity.getComponents (domain::block).size (), 0u);
}

BOOST_AUTO_TEST_SUITE_END ()
