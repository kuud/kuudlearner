#pragma once

// small note before the importing of ch's reflection shit: credit to kat for madoka library
// here i am being a retard and pasting it
// no, I didn't do the madoka library because i'm a retard
// note to future self if they see this cheat: retard i hope you learned to code shit this time
// ~ x_k0tori, 29/07/2021, somewhere at 12:30PM Romanian Time

#include "app_domain/ch_app_domain.h"

using namespace ceaihack::clr;

namespace ceaihack::reflection {
	void init();

	inline app_domain domain;
	inline assembly osu_assembly = { nullptr };

	// now the fun starts
	inline type osu_player_t = { nullptr };
}