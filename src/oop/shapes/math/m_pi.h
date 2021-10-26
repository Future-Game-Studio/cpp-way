#pragma once

#define ISCPP20 __cplusplus > 201703L

#ifdef ISCPP20
#include <numbers>
#else
#include <math.h>
#endif

constexpr double pi()
{
#ifdef ISCPP20
    return std::numbers::pi;
#else
    return std::atan(1) * 4;
#endif
} 
