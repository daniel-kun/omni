#ifndef OMNI_CORE_MODEL_PARAMETER_HPP
#define OMNI_CORE_MODEL_PARAMETER_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/scope.hpp>

namespace omni {
namespace core {
namespace model {
    class type;

    /**
    @class parameter parameter.hpp omni/core/model/parameter.hpp

    @brief Defines a parameter that can be passed to an external_function or a omni::core::model::function.

    A parameter consists of a type and a name.

    @see function_prototype::getParameters ().
    **/
    class OMNI_CORE_API parameter : public scope {
    public:
        parameter (std::shared_ptr <type> parameterType = std::shared_ptr <type> (), std::string name = std::string ());

        static meta_info & getStaticMetaInfo ();

        meta_info & getMetaInfo () const override;

        domain getDomain () const override;

        void setType (std::shared_ptr <type> type);
        const std::shared_ptr <type> getType () const;
        std::shared_ptr <type>  getType ();

    private:
        std::shared_ptr <type> _type;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
