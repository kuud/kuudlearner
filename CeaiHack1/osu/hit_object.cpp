#include "hit_object.h"

using namespace ceaihack::osu;

hit_object::hit_object(uintptr_t base_address) {
	base = base_address;

	if (base == NULL) return;

	start_time = make_memptr_var<int>(base + 0x10);
	end_time = make_memptr_var<int>(base + 0x14);
	type = make_memptr_var<int>(base + 0x18);
	is_hit = make_memptr_var<bool>(base + 0x84);
	base_position = make_memptr_var<vector2_t>(base + 0x8C);
}