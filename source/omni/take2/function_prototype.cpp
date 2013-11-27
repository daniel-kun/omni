#include <omni/take2/function_prototype.hpp>

omni::take2::function_prototype::function_prototype (std::string const & name,
                                                     std::shared_ptr <type> returnType) :
    context_part (name),
    _llvmFunction (nullptr),
    _linkageType (linkage_type::internal),
    _returnType (returnType),
    _parameters ()
{
}

omni::take2::function_prototype::~function_prototype ()
{
}

/**
Returns the type that this function returns when it is called at runtime.
**/
const std::shared_ptr <omni::take2::type> omni::take2::function_prototype::getReturnType () const
{
    return _returnType;
}

/**
Returns the type that this function returns when it is called at runtime.
**/
std::shared_ptr <omni::take2::type> omni::take2::function_prototype::getReturnType ()
{
    return _returnType;
}


omni::take2::linkage_type omni::take2::function_prototype::getLinkageType () const
{
    return _linkageType;
}

void omni::take2::function_prototype::setLinkageType (omni::take2::linkage_type linkageType)
{          
    _linkageType = linkageType;
}

/**
Adds a parameter at the end of the list of parameters that this function should take.
@param parameters The parameter that should be added to the list of parameters for this function.
**/
void omni::take2::function_prototype::addParameter (std::shared_ptr <omni::take2::parameter> parameter)
{
    _parameters.push_back (parameter);
}

/**
Sets the list of parameters that this function takes to the given parameters;
@param parameters The list of parameters that this function should take.
**/
void omni::take2::function_prototype::setParameters (std::vector <std::shared_ptr <omni::take2::parameter>> parameters)
{
    _parameters = parameters;
}

/**
@return Returns the list of parameters that this function takes.
**/
std::vector <std::shared_ptr <omni::take2::parameter>> omni::take2::function_prototype::getParameters () const
{
    return _parameters;
}
