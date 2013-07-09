#include <omni/core/instruction.hpp>

omni::core::instruction::instruction ()
{
}

omni::core::instruction::~ instruction ()
{
}

std::string const & omni::core::instruction::getTypeName ()
{
    static std::string const result;
    return result;
}
