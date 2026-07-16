#pragma once

// ======================================
//  Std includes

#include <utility>
#include <functional>
#include <algorithm>
#include <memory>
#include <chrono>
#include <filesystem>

#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdint>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// ======================================


// ======================================
//  Mathlib includes

#include "Maths.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix4.h"

// ======================================


#ifdef KL_PLATFORM_WINDOWS
    #include <Windows.h>
#endif