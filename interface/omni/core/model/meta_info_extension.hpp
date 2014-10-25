#ifndef OMNI_CORE_MODEL_META_INFO_EXTENSION_HPP
#define OMNI_CORE_MODEL_META_INFO_EXTENSION_HPP

#include <omni/core/core.hpp>

namespace omni {
namespace core {
namespace model {

    /**
    @class meta_info_extension meta_info_extension.hpp omni/core/model/meta_info_extension.hpp
    @brief This class is abstract. Base-class for custom meta-information properties that can be added to meta_info.

    E.g. the UI subsystem uses this heavily to attach meta-information to entity types.
    **/
    class OMNI_CORE_API meta_info_extension {
    public:
        virtual ~ meta_info_extension () = 0;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
