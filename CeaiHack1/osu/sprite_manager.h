#pragma once

#include "Windows.h"
#include "memptr_var.h"

using namespace ceaihack::utils;

namespace ceaihack::osu {
	class sprite_manager {
	public:
		sprite_manager() {}
		sprite_manager(uintptr_t base_address);
		~sprite_manager() {}

		memptr_var<float> alpha;

		uintptr_t base = NULL;
	};
}