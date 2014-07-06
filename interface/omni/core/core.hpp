#ifndef OMNI_CORE_CORE_HPP
#define OMNI_CORE_CORE_HPP

#ifdef MSVC
#   ifdef omnicore_BUILD_LIB
#       define OMNI_CORE_API __declspec (dllexport)
#   else
#       define OMNI_CORE_API __declspec (dllimport)
#   endif
#else
#   define OMNI_CORE_API
#endif

// Check for 32 or 64 bit environment:
// Check windows
#if _WIN32 || _WIN64
#    if _WIN64
#        define ENVIRONMENT64
#    else
#        define ENVIRONMENT32
#    endif
#endif

// Check GCC
#if __GNUC__
#    if __x86_64__ || __ppc64__
#        define ENVIRONMENT64
#    else
#        define ENVIRONMENT32
#    endif
#endif

#endif
