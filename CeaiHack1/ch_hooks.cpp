#include "ch_hooks.h"
#include "ch_hooks_vars.h"
#include "ch_logger.h"
#include "ch_memory.h"
#include "ch_ui.h"

// features
#include "ch_aim_assist.h"
#include "ch_timewarp.h"
#include "ch_unmod_fl.h"

#include "MinHook.h"
#include <iostream>

bool ceaihack::hooks::init() {
   while ( !( ceaihack::hooks::variables::opengl_lib = GetModuleHandleA( "opengl32.dll" ) ) )
      ;

   ceaihack::hooks::variables::wgl_swap_buffers = GetProcAddress( ceaihack::hooks::variables::opengl_lib, "wglSwapBuffers" );

   MH_Initialize();

   if ( MH_CreateHook(
            reinterpret_cast<void *>( ceaihack::hooks::variables::wgl_swap_buffers ),
            reinterpret_cast<void *>( &ceaihack::hooks::swap_buffers ),
            reinterpret_cast<void **>( &ceaihack::hooks::variables::original_swap_buffers ) ) != MH_OK ) {
      ceaihack::logger::cheat->error( "Failed to hook wglSwapBuffers!" );
      return 0;
   }

   if ( MH_CreateHook(
            reinterpret_cast<void *>( ceaihack::memory::location::set_rate ),
            reinterpret_cast<void *>( &ceaihack::cheat::features::timewarp::rate_change_hook ),
            reinterpret_cast<void **>( &ceaihack::hooks::variables::o_set_current_playback_rate ) ) != MH_OK ) {
      ceaihack::logger::cheat->error( "Failed to hook set_CurrentPlaybackRate!" );
   }

   if ( MH_CreateHook(
            reinterpret_cast<void *>( ceaihack::memory::location::set_cursor_pos ),
            reinterpret_cast<void *>( &ceaihack::cheat::features::aimassist::set_cursor_position_hook ),
            reinterpret_cast<void **>( &ceaihack::hooks::variables::o_set_cursor_position ) ) != MH_OK ) {
      ceaihack::logger::cheat->error( "Failed to hook set_MousePosition!" );
   }

   MH_EnableHook( MH_ALL_HOOKS );

   return 1;
}

void ceaihack::hooks::unload() {
   ceaihack::logger::cheat->debug( "Unloading CeaiHack..." );
   ceaihack::cheat::ui::unload();

   MH_RemoveHook( MH_ALL_HOOKS );
   MH_Uninitialize();
}

bool __stdcall ceaihack::hooks::swap_buffers( HDC context ) {
   ceaihack::cheat::ui::on_frame( context );
   return ceaihack::hooks::variables::original_swap_buffers( context );
}