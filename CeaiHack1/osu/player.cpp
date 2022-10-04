#include "player.h"
#include "window_utils.h"

#include "../ch_memory_addy.h"
#include <stdio.h>

using namespace ceaihack::osu;

uintptr_t get_player() {
	return *(uintptr_t*)ceaihack::memory::location::player_base;
}

std::unique_ptr<player> player::instance() {
	auto player_instance = get_player();

	if (player_instance) return std::make_unique<player>(player_instance);

	return nullptr;
}

bool player::is_instance() {
	return get_player() != NULL;
}

player::player(uintptr_t player_address) {
	base = player_address;

	if (base == NULL) return;

	hom = new ceaihack::osu::hit_object_manager(*(uintptr_t*)(base + 0x40));
	ruleset = new ceaihack::osu::ruleset(*(uintptr_t*)(base + 0x60));
	fl_check = make_memptr_var<bool>(base + 0x186);
}

float player::get_object_radius() {
	if (hom == nullptr) return 1;

	float width = 512.0f * get_window_ratio();
	float difficulty = hom->apply_difficulty(hom->beatmap->circle_size.get());

	float sprite_display_size = (width / 8 * (1 - 0.7f * ((difficulty - 5) / 5)));
	return sprite_display_size / 2.0f / get_window_ratio() * 1.00041f;
}