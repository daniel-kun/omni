#ifndef OMNI_CORE_MODEL_META_INFO_HPP
#define OMNI_CORE_MODEL_META_INFO_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/meta_info_extension.hpp>

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace omni {
namespace core {
namespace model {

    /**
    @class meta_info meta_info.hpp omni/core/model/meta_info.hpp
    @brief Provides meta-information about different entity types in the Omni Programming Language.

    Meta-information include the name of the specific kind of entity, it's hierarchical parent type and it's decendant types.
    E.g. modifying_expression's hierarchical parent is expression, and it's decendant (implementing) types are function_call_expression and variable_assignment_expression.

    Additional meta_info_extensions can be registered under arbitrary names to attach any value to an entity type.
    Other omni subsystems make use of these extensions. The extension properties' names start with "omni.", such as "omni.ui".
    **/
    class OMNI_CORE_API meta_info {
    public:
        meta_info (const std::string & name);
        meta_info (const meta_info & parent, const std::string & name);

        bool isAbstract () const;
        const std::string & getName () const;
        const meta_info * getParent () const;
        const meta_info & getChildAt (std::size_t index) const;
        std::size_t getChildCount () const;

        const meta_info_extension * getExtension (const std::string & extensionName) const;        
        void setExtension (const std::string & extensionName, std::shared_ptr <meta_info_extension> extension);        

    private:
        meta_info * _parent;
        std::string _name;
        std::vector <meta_info*> _children;
        std::map <std::string, std::shared_ptr <meta_info_extension>> _extensions;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
