#include <omni/core/model/entity.hpp>
#include <omni/core/model/meta_info.hpp>
#include <omni/core/model/if_statement.hpp>

#include <vector>
#include <string>
#include <memory>

#include <boost/test/unit_test.hpp>

namespace omni {
namespace core {
namespace syntax {
class syntax_component;
class syntax_text_validator;

class syntax_template {
public:
    std::vector <syntax_component> _components;
};

class syntax_component {
public:
    virtual ~ syntax_component () { }
};

class syntax_fixed_component : public syntax_component {
public:
    std::string _text;
};

class syntax_text_validator;

class syntax_named_component : public syntax_component {
public:
    std::string _name;
};

class syntax_text_component : public syntax_named_component {
public:
    std::shared_ptr <syntax_text_validator> _validator;
};

class syntax_entity_component : public syntax_named_component {
public:
    syntax_entity_component () = delete;
    omni::core::model::meta_info & _metaInfo;
};

class syntax_text_validator {
public:
    bool validate (std::string text);
    std::vector <std::string> suggest (std::string text);
};

class syntax_node {
public:
    syntax_node () = delete;

    syntax_template & _template;
    std::map <std::string, std::shared_ptr <omni::core::model::entity>> _entities;
    std::map <std::string, std::string> _text;
};

} // namespace syntax
} // namespace core
} // namespace omni

namespace omni {
namespace core {
namespace model {

class meta_if_statement : public meta_info {
public:
    std::string getName() const override;
    std::shared_ptr <omni::core::syntax::syntax_template> getSyntax () const override;
    std::shared_ptr <entity> createFromSyntax (omni::core::syntax::syntax_node syntax) override;
};

} // namespace model
} // namespace core
} // namespace omni

std::string omni::core::model::meta_if_statement::getName() const
{
    return "if_statement";
}

std::shared_ptr <omni::core::syntax::syntax_template> omni::core::model::meta_if_statement::getSyntax () const
{
    return std::make_shared <omni::core::syntax::syntax_template> ();
}

std::shared_ptr <omni::core::model::entity> omni::core::model::meta_if_statement::createFromSyntax (omni::core::syntax::syntax_node syntax)
{
    return std::make_shared <if_statement> ();
}
