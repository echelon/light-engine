#ifndef LIGHT_ENGINE_GFX_TRANSFORMATION_HPP
#define LIGHT_ENGINE_GFX_TRANSFORMATION_HPP

#include "object.hpp"
#include "point.hpp"

// TODO: Look up ILDA hardware scales
#define HARDWARE_SCALE 35000

Points get_transformed_points(const Object& obj);

#endif
