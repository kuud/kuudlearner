#pragma once
#include "Windows.h"
#include <memory>

#include "beatmap.h"
#include "ruleset.h"
#include "hit_object_manager.h"
#include "memptr_var.h"

using namespace ceaihack::utils;

namespace ceaihack::osu {
	class player {
	public:
		player(uintptr_t player_address);
		~player() {}

		hit_object_manager* hom;
		ruleset* ruleset;
		memptr_var<bool> fl_check;

		float get_object_radius();

		static std::unique_ptr<player> instance();
		static bool is_instance();

		uintptr_t base = NULL;
	};
}