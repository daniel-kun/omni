#include <omni/core/model/meta_info.hpp>

/**
@brief Initializes this meta_info as a root entity type with the given `name'.
@param name The name of the entity type that this meta-info belong to.
**/
omni::core::model::meta_info::meta_info (const std::string & name) :
    _parent (nullptr),
    _name (name),
    _children (),
    _extensions ()
{
}

/**
@brief Initializes this meta_info as a child entity type of `parent' with the given `name'.
@param parent The parent entity type which the entity type this meta-info belongs to implements or extends.
@param name The name of the entity type that this meta-info belong to.
**/
omni::core::model::meta_info::meta_info (const meta_info & parent, const std::string & name) :
    _parent (const_cast <meta_info *> (& parent)),
    _name (name),
    _children (),
    _extensions ()
{
    _parent->_children.push_back (this);
}

/**
@brief Returns true when the entity type of this meta_info is abstract and is solely a base class for other entity types.

This is identical to checking whether getChildCount() returns > 0u.
@return  True, when the entity type of this meta_info is abstract and is solely a base class for other entity types.
**/
bool omni::core::model::meta_info::isAbstract () const
{
    return getChildCount () > 0u;
}

/**
@brief Returns the name of the entity-type that this meta-info belongs to.
@return The name of the entity-type that this meta-info belongs to.
**/
const std::string & omni::core::model::meta_info::getName () const
{
    return _name;
}

/**
@brief Returns the parent of this entity-type, if any. (e.g. "expression" is the parent of "modifying_expression".)
@return The parent of the entity-type.
**/
const omni::core::model::meta_info * omni::core::model::meta_info::getParent () const
{
    return _parent;
}

/**
@brief Returns the child at index `index'.
@param index The index of the child that is to be retrieved. Needs to be less than getChildCount ().
@return The child at index `index'.
@exceptions Throws std::out_of_range if index is >= getChildCount().
**/
const omni::core::model::meta_info & omni::core::model::meta_info::getChildAt (std::size_t index) const
{
    return * _children.at (index);
}

/**
@brief Returns the number of children of this meta-info.
Children are added to this meta_info by making new meta_info objects and pass this object as it's "parent" parameter to the ctor.
@return The number of children of this meta-info.
**/
std::size_t omni::core::model::meta_info::getChildCount () const
{
    return _children.size ();
}

/**
@brief Returns the extension property with the name extensionName.
@param extensionName The name of the extension property that should be retrieved.
@return The extension property with the name extensionName, if such an extension has been added before. Returns nullptr, if no such extension is registered via setExtension.
**/
const omni::core::model::meta_info_extension * omni::core::model::meta_info::getExtension (const std::string & extensionName) const
{
    auto it = _extensions.find (extensionName);
    if (it == _extensions.end ()) {
        return nullptr;
    } else {
        return it->second.get ();
    }
}

/**
@brief Sets a new extension property or overwrites an existing with the given extensionName.
@param extensionName The name of the extension property that should be added or overwritten.
@param extension The extension object that should be registered by the given name.
**/
void omni::core::model::meta_info::setExtension (const std::string & extensionName, std::shared_ptr <meta_info_extension> extension)
{
    _extensions [extensionName] = extension;
}

// Initialization of all meta_info objects:
// (This has to be done in a central translation unit, because initialization order is undefined across translation units.)
namespace omniMetaImpl {
omni::core::model::meta_info entityMetaInfo ("entity");
    omni::core::model::meta_info typeMetaInfo (entityMetaInfo, "type");
    omni::core::model::meta_info scopeMetaInfo (entityMetaInfo, "scope");
        omni::core::model::meta_info function_prototypeMetaInfo (scopeMetaInfo, "function_prototype");
            omni::core::model::meta_info external_functionMetaInfo (function_prototypeMetaInfo, "external_function");
            omni::core::model::meta_info functionMetaInfo (function_prototypeMetaInfo, "function");
        omni::core::model::meta_info moduleMetaInfo (scopeMetaInfo, "module");
        omni::core::model::meta_info parameterMetaInfo (scopeMetaInfo, "parameter");
        omni::core::model::meta_info statementMetaInfo (scopeMetaInfo, "statement");
            omni::core::model::meta_info blockMetaInfo (statementMetaInfo, "block");
            omni::core::model::meta_info expressionMetaInfo (statementMetaInfo, "expression");
                omni::core::model::meta_info modifying_expressionMetaInfo (expressionMetaInfo, "modifying_expression");
                    omni::core::model::meta_info function_call_expressionMetaInfo (modifying_expressionMetaInfo, "function_call_expression");
                    omni::core::model::meta_info variable_assignment_expressionMetaInfo (modifying_expressionMetaInfo, "variable_assignment_expression");
                omni::core::model::meta_info pure_expressionMetaInfo (expressionMetaInfo, "pure_expression");
                    omni::core::model::meta_info binary_operator_expressionMetaInfo (pure_expressionMetaInfo, "binary_operator_expression");
                    omni::core::model::meta_info cast_expressionMetaInfo (pure_expressionMetaInfo, "cast_expression");
                        omni::core::model::meta_info bitcast_expressionMetaInfo (cast_expressionMetaInfo, "bitcast_expression");
                    omni::core::model::meta_info literal_expressionMetaInfo (pure_expressionMetaInfo, "literal_expression");
                        omni::core::model::meta_info builtin_literal_expressionMetaInfo (literal_expressionMetaInfo, "builtin_literal_expression");
                    omni::core::model::meta_info variable_declaration_expressionMetaInfo (pure_expressionMetaInfo, "variable_declaration_expression");
                    omni::core::model::meta_info variable_expressionMetaInfo (pure_expressionMetaInfo, "variable_expression");
            omni::core::model::meta_info if_statementMetaInfo (statementMetaInfo, "if_statement");
            omni::core::model::meta_info return_statementMetaInfo (statementMetaInfo, "return_statement");
            omni::core::model::meta_info while_statementMetaInfo (statementMetaInfo, "while_statement");
            omni::core::model::meta_info do_while_statementMetaInfo (statementMetaInfo, "do_while_statement");
}
