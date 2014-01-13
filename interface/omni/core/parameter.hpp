#ifndef OMNI_CORE_PARAMETER_HPP
#define OMNI_CORE_PARAMETER_HPP

#include <omni/core/core.hpp>
#include <omni/core/entity.hpp>

namespace omni {
namespace core {
namespace model {
    class type;

    /**
    Function parameter, @see function::getParameters ().
    **/
    class OMNI_CORE_API parameter : public entity {
    public:
        parameter (std::shared_ptr <type> type, std::string name);

        const std::shared_ptr <type> getType () const;
        std::shared_ptr <type>  getType ();

    private:
        std::shared_ptr <type> _type;
        std::string _name;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
