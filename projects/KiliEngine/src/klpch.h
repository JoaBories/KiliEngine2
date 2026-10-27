#pragma once

#include "Kili/Core/Core.h"

#pragma // Std includes
#include <utility>
#include <functional>
#include <algorithm>
#include <memory>
#include <chrono>
#include <filesystem>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include <cstdint>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#pragma // Vendor includes
#include "SDL.h"
#include "glad/gl.h"

#pragma // GLM includes
#include <glm/vec2.hpp>               // vec2, bvec2, dvec2, ivec2 and uvec2
#include <glm/vec3.hpp>               // vec3, bvec3, dvec3, ivec3 and uvec3
#include <glm/vec4.hpp>               // vec4, bvec4, dvec4, ivec4 and uvec4
#include <glm/mat4x4.hpp>             // mat4, dmat4
#include <glm/gtc/quaternion.hpp>     // quat, etc

#include <glm/common.hpp>             // all the GLSL common functions: abs, min, mix, isnan, fma, etc.
#include <glm/exponential.hpp>        // all the GLSL exponential functions: pow, log, exp2, sqrt, etc.
#include <glm/geometric.hpp>          // all the GLSL geometry functions: dot, cross, reflect, etc.
#include <glm/matrix.hpp>             // all the GLSL matrix functions: transpose, inverse, etc.
#include <glm/trigonometric.hpp>      // all the GLSL trigonometric functions: radians, cos, asin, etc.
#include <glm/vector_relational.hpp>  // all the GLSL vector relational functions: equal, less, etc.
#include <glm/gtc/type_ptr.hpp>       // value_ptr conversion