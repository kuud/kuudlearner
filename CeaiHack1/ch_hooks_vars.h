#pragma once
#include "vector2.h"
#include <Windows.h>

namespace ceaihack::hooks::variables {
   // type definitions
   typedef bool( __stdcall *swap_buffers_t )( HDC );
   typedef void( __stdcall *set_current_playback_rate_t )( double );
   typedef void( __stdcall *hax_check_audio_t )();
   typedef void( __fastcall *update_playback_rate_t )( void *ecx, void *edx );

   typedef void( __fastcall *set_cursor_position_t )( void *ecx, void *edx, vector2_t pos );
   typedef void( __fastcall *check_flashlight_hax_t )( void *ecx, void *edx );
   typedef void( __fastcall *update_flashlight_t )( void *ecx, void *edx );

   // variables
   inline HMODULE        opengl_lib;
   inline void *         wgl_swap_buffers;
   inline swap_buffers_t original_swap_buffers = nullptr;

   inline set_current_playback_rate_t o_set_current_playback_rate = nullptr;
   inline hax_check_audio_t           o_hax_check_audio           = nullptr;
   inline update_playback_rate_t      o_update_playback_rate      = nullptr;

   inline set_cursor_position_t  o_set_cursor_position  = nullptr;
   inline check_flashlight_hax_t o_check_flashlight_hax = nullptr;
   inline update_flashlight_t    o_update_flashlight    = nullptr;
} // namespace ceaihack::hooks::variables