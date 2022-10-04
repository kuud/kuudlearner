#pragma once
#include "./osu/osu.h"
#include "ch_hooks_vars.h"
#include "vector2.h"

// kat.— Today at 12:00 PM
// @x_k0tori
// std::max(1.f, std::min(1.f + ((distance / powf(distance, 2.f)) * 10.f), 1.5f));
// perfect distance based multiplier for ur aa
// closer = higher

namespace ceaihack::cheat::features::aimassist {
   void update();
   void __fastcall set_cursor_position_hook( void *ecx, void *edx, vector2_t pos );

   vector2_t calculate_point( vector2_t object, vector2_t cursor );

   inline vector2_t cursor_position    = vector2_t( 0.0f );
   inline vector2_t s_cursor_position  = vector2_t( 0.0f );
   inline vector2_t object_position    = vector2_t( 0.0f );
   inline vector2_t predicted_position = vector2_t( 0.0f );

   inline float object_radius = 10;

   void perform_aim_correction( ceaihack::osu::player *player, vector2_t pos );
   void perform_auto_aim( ceaihack::osu::player *player );
} // namespace ceaihack::cheat::features::aimassist