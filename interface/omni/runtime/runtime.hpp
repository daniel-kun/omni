#ifndef OMNI_RUNTIME_RUNTIME_HPP
#define OMNI_RUNTIME_RUNTIME_HPP

#ifdef omniruntime_BUILD_LIB
#define OMNI_RUNTIME_API __declspec (dllexport)
#else
#define OMNI_RUNTIME_API __declspec (dllimport)
#endif


#endif
