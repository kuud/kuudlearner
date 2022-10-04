#include "hit_object_manager.h"
#include "game_base.h"
#include <stdio.h>

using namespace ceaihack::osu;

hit_object_manager::hit_object_manager(uintptr_t base_address) {
	base = base_address;

	if (base == NULL) return;

	if(*(uintptr_t*)(base + 0x30) != NULL)
		beatmap = new ceaihack::osu::beatmap(*(uintptr_t*) (base + 0x30));

	if(*(uintptr_t*)(base + 0x34) != NULL)
		active_mods = make_memptr_var_obf<int>(*(uintptr_t*)(base + 0x34));

	if (*(uintptr_t*)(base + 0x48) != NULL)
		hit_objects = make_memptr_list<hit_object>(*(uintptr_t*)(base + 0x48));

	preempt = make_memptr_var<int>(base + 0x1C);
}

float hit_object_manager::apply_difficulty(float difficulty, float hr) {
	if ((active_mods.get() & (int)mod_e::easy) > 0)
		return max(0, difficulty / 2);
	else if ((active_mods.get() & (int)mod_e::hard_rock) > 0)
		return min(10, difficulty * hr);

	return difficulty;
}

float hit_object_manager::calc_preempt_time() {
	return map_difficulty_range(beatmap->approach_rate.get(), 1800, 1200, 450);
}

float hit_object_manager::map_difficulty_range(float difficulty, float min, float mid, float max)
{
	auto d = apply_difficulty(difficulty, 1.4f);

	if (d > 5)
		return mid + (max - mid) * (d - 5) / 5;
	if (d < 5)
		return mid - (mid - min) * (5 - d) / 5;
	return mid;
}

float hit_object_manager::apply_mods_to_rate(double rate) {
	auto mods = active_mods.get();

	if (mods & (int) mod_e::double_time) return (float) rate * 1.5f;
	else if (mods & (int) mod_e::double_time) return (float) rate * .75f;
	else return (float) rate;
}

hit_object hit_object_manager::get_current_object() {
	if (hit_objects.is_valid()) {
		const auto time = osu::gamebase::get_time();
		const auto preempt = calc_preempt_time();

		for (int i = 0; i < hit_objects.length; i++) {
			auto object = hit_objects[i];

			if (object.is_hit.get() || time > object.end_time.get()) continue; // if our current time is past the current object time, we continue, just to save time.

			if (time >= (object.start_time.get() - preempt) && time <= object.end_time.get()) // check if time is in the [start - preempt; end] interval.
				return object;
		}
	}

	return { 0 };
}