#pragma once

#include "Windows.h"
#include "memptr_var.h"
#include "../vector2.h"

using namespace ceaihack::utils;

namespace ceaihack::osu {
	class hit_object {
	public:
		hit_object(uintptr_t base_address);
		~hit_object() {}

		memptr_var<int> start_time;
		memptr_var<int> end_time;
		memptr_var<int> type;
		memptr_var<bool> is_hit;
		memptr_var<vector2_t> base_position;

		uintptr_t base = NULL;
	};
}
