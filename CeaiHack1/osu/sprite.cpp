#include "sprite.h"
#include <stdio.h>

using namespace ceaihack::osu;

sprite::sprite(uintptr_t base_address) {
	base = base_address;

	if (base == NULL) return;

	alpha = make_memptr_var<float>(base + 0x2C);
}