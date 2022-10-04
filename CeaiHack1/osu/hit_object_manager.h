#pragma once

#include "Windows.h"
#include "memptr_list.h"
#include "memptr_var_obf.h"

#include "mods.h"
#include "beatmap.h"
#include "rulesets.h"

using namespace ceaihack::utils;

namespace ceaihack::osu {
	class hit_object_manager {
	public:
		hit_object_manager() {}
		hit_object_manager(uintptr_t base_address);
		~hit_object_manager() {}

		beatmap* beatmap;
		memptr_var_obf<int> active_mods;
		memptr_list<hit_object> hit_objects;
		memptr_var<int> preempt;

		float apply_difficulty(float difficulty, float hr = 1.3f);
		float map_difficulty_range(float difficulty, float min, float mid, float max);
		float calc_preempt_time();
		float apply_mods_to_rate(double rate);

		hit_object get_current_object();

		ruleset_e game_mode = ruleset_e::standard;
	private:
		uintptr_t base = NULL;
	};
}