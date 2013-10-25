#ifndef OMNI_TAKE2_TAKE2_HPP
#define OMNI_TAKE2_TAKE2_HPP

#ifdef omnitake2_BUILD_LIB
#define OMNI_TAKE2_API __declspec (dllexport)
#else
#define OMNI_TAKE2_API __declspec (dllimport)
#endif

#endif
