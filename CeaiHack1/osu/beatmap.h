#pragma once

#include "Windows.h"
#include "rulesets.h"
#include "memptr_var.h"
#include "hit_object.h"
#include <list>

using namespace ceaihack::utils;

namespace ceaihack::osu {
	class beatmap {
	public:
		beatmap(uintptr_t base_address);
		~beatmap() {}

		memptr_var<float> circle_size;
		memptr_var<float> drain_rate;
		memptr_var<float> overall_diff;
		memptr_var<float> approach_rate;

		memptr_var<ruleset_e> game_mode;

		uintptr_t base = NULL;
	};
}