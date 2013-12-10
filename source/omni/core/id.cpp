#include <omni/core/id.hpp>

/**
Initializes this id with an invalid domain and an empty string id.
**/
omni::core::id::id () :
    _domain (domain::invalid),
    _id ()
{
}


/**
Initializes this id for the domain `domain' and the string id `id'.
@param domain The domain for this id.
@param id The string id for this id.
**/
omni::core::id::id (omni::core::domain domain, std::string id) :
    _domain (domain),
    _id (id)
{
}

bool omni::core::id::operator<(id const & rhs) const
{
    if (! isValid () && ! rhs.isValid ()) {
        return false;
    }
    if (getDomain () == rhs.getDomain ()) {
        return getId () < rhs.getId ();
    } else {
        return getDomain () < rhs.getDomain ();
    }
}

/**
Returns false if this id does not have valid domain and a valid string id.
An invalid id is created by the default constructor.
**/
bool omni::core::id::isValid () const
{
    return _domain != domain::invalid;
}

/**
Returns the domain that this id is valid for.
**/
omni::core::domain omni::core::id::getDomain () const
{
    return _domain;
}

/**
Returns the string id for this id.
**/
std::string omni::core::id::getId () const
{
    return _id;
}
