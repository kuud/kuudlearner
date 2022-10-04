#include "beatmap.h"
#include <stdio.h>

using namespace ceaihack::osu;

beatmap::beatmap(uintptr_t base_address) {
	base = base_address;

	if (base == NULL) return;

	approach_rate = make_memptr_var<float>(base + 0x2C);
	circle_size = make_memptr_var<float>(base + 0x30);
	drain_rate = make_memptr_var<float>(base + 0x34);
	overall_diff = make_memptr_var<float>(base + 0x38);

	game_mode = make_memptr_var<ruleset_e>(base + 0x114);
}