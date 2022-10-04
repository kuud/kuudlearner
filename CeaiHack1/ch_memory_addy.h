#pragma once
#include <Windows.h>

namespace ceaihack::memory::location {
   inline uintptr_t state_base;
   inline uintptr_t player_base;
   inline uintptr_t time_base;
   inline uintptr_t gb_time_base;
   inline uintptr_t gb_window_manager_base;

   inline void *set_rate;
   inline void *update_playback_rate;
   inline void *set_cursor_pos;
   inline void *check_flashlight_hax;
   inline void *update_flashlight;
   inline void *update_timing;
} // namespace ceaihack::memory::location