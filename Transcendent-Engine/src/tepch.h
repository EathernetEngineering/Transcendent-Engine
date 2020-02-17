#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <ostream>

#include <string>
#include <sstream>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Transcendent-Engine/core/Log.h"
#include "Transcendent-Engine/Debug/Instumentor.h"

#ifdef _WIN32
	#ifdef _WIN64
		#include <Windows.h>
	#endif
#endif