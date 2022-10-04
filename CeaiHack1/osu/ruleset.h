#pragma once

#include "Windows.h"
#include "sprite.h"
#include "sprite_manager.h"

namespace ceaihack::osu {
	class ruleset {
	public:
		ruleset() {}
		ruleset(uintptr_t base_address);
		~ruleset() {}

		sprite* s_flashlight;
		sprite* s_lights_out;

		sprite_manager* sprite_manager_flashlight;

		uintptr_t base = NULL;
	};
}