#pragma once
#include "../vector2.h"
#include "../ch_memory_addy.h"

struct screen_t {
	int width, height;
};

namespace ceaihack::utils {
	inline screen_t get_screen() {
		if (*(uintptr_t*)memory::location::gb_window_manager_base != NULL) {
			uintptr_t real_addy = *(uintptr_t*)memory::location::gb_window_manager_base;
			return *(screen_t*) (real_addy + 0x4);
		}
			
		return screen_t { 0, 0 };
	}

	inline float get_window_ratio() {
		return get_screen().height / 480.0f;
	}

	inline vector2_t get_gamefield_origin() {
		float ratio = get_window_ratio();
		float width = 512 * ratio;
		float height = 384 * ratio;

		auto window = get_screen();

		float num = -16 * ratio;

		auto gf_origin = vector2_t(
			(window.width - width) / 2,
			(window.height - height) / 4 * 3 + num
		);

		return gf_origin;
	}

	inline vector2_t get_relative_pos_to_gamefield(vector2_t position) {
		return position * get_window_ratio() + get_gamefield_origin();
	}
}