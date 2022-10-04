#include "ruleset.h"
#include <stdio.h>

using namespace ceaihack::osu;

ruleset::ruleset(uintptr_t base_address) {
	base = base_address;

	if (base == NULL) return;

	// init sprites
	if (*(uintptr_t*)(base + 0x5C) != NULL)
		s_flashlight = new sprite(*(uintptr_t*)(base + 0x5C));

	if (*(uintptr_t*)(base + 0x60) != NULL)
		s_lights_out = new sprite(*(uintptr_t*)(base + 0x60));
	
	if (*(uintptr_t*)(base + 0x54) != NULL)
		sprite_manager_flashlight = new sprite_manager(*(uintptr_t*)(base + 0x54));
}