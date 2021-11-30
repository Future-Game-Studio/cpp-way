#pragma once

#define ISCPP20 __cplusplus > 201703L

#include <numbers>
 
double pi()
{
    return std::atan(1) * 4;
}
