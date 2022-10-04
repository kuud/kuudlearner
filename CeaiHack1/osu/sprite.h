#pragma once

#include "Windows.h"
#include "memptr_var.h"

using namespace ceaihack::utils;

namespace ceaihack::osu {
	class sprite {
	public:
		sprite() {}
		sprite(uintptr_t base_address);
		~sprite() {}

		memptr_var<float> alpha;

		uintptr_t base = NULL;
	};
}