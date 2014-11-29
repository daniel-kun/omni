#ifndef OMNI_CORE_PARSER_HPP
#define OMNI_CORE_PARSER_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/statement.hpp>
#include <omni/core/model/expression.hpp>

#include <memory>
#include <vector>

namespace omni {
namespace core {
namespace core {
class scope;
}
}
}

namespace omni {
namespace core {

/**
@class parser parser.hpp omni/core/parser.hpp
@brief The parser can parse text and create statements and expressions from it's content.

The parser is used to interpret input and create entities from it. The parser distinguishes between parsing statements and expressions. 
**/
class OMNI_CORE_API parser {
public:
    /**
    @brief Contains the result of parsing a text as a statement or an expression. T may only be omni::core::model::statement or expression.
    **/
    template <typename T>
    struct parser_result {
        std::shared_ptr <T> entity; ///< The entity that the parsed text can represent.
        bool exact; ///< True, if the parsed text matches exactly the entities textual representation. False, if it is only a partial match.
    };

    using StatementList = std::vector <parser_result <omni::core::model::statement>>;
    using ExpressionList = std::vector <parser_result <omni::core::model::expression>>;

    static StatementList parseStatement (omni::core::model::scope & scope, std::string const & text);
    static StatementList parseIfStatement (omni::core::model::scope & scope, std::string const & text);

    static ExpressionList parseExpression (omni::core::model::scope & scope, std::string const & text);
    static ExpressionList parseVariableDeclaration (omni::core::model::scope & scope, std::string const & text);
    static ExpressionList parseBuiltinLiteral (omni::core::model::scope & scope, std::string const & text);
};

} // namespace core
} // namespace omni

#endif // include guard
