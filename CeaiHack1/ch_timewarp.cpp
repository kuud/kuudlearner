#include "ch_timewarp.h"

#include "ch_config.h"
#include "ch_hooks_vars.h"
#include "ch_logger.h"

#include "./osu/osu.h"
#include "ch_game_signature.h"
#include "ch_memory.h"

#include <iostream>

uintptr_t player_update_addy = NULL;

constexpr double sixty_frame_time = 16.666666666666668; // 1000.0f / 60.0f

void ceaihack::cheat::features::timewarp::init() {
   player_update_addy =
       ceaihack::cheat::memory::search_pattern( ceaihack::cheat::signatures::player_update_signature, "xxxxxxxx????xxxx????x????xxxxxxxx????xx????xx????x" );
#ifdef _DEBUG
   printf( "TW: Player::Update @ %08X\n", player_update_addy );
#endif
}

// to do: fix
void patch_timewarp_check() {
   uintptr_t tw_check_location = player_update_addy + 0x142C;

   if ( ceaihack::config::features::timewarp::enabled ) {
      if ( *(uint16_t *) ( tw_check_location ) != 0xE990 ) {
         *(uint16_t *) ( tw_check_location ) = 0xE990;
         ceaihack::logger::features->info( "Patched the Timewarp Player::Update check!" );
      }
   }
   else {
      if ( *(uint16_t *) ( tw_check_location ) != 0x8E0F ) {
         *(uint16_t *) ( tw_check_location ) = 0x8E0F;
         ceaihack::logger::features->info( "Restored the original Timewarp Player::Update check!" );
      }
   }
}

void patch_gamebase_update_timings() {
   uintptr_t location = (uintptr_t) ceaihack::memory::location::update_timing;

   auto new_frame_ms = sixty_frame_time;

   if ( ceaihack::config::features::timewarp::enabled && ceaihack::osu::player::is_instance() )
      new_frame_ms *= ( 1.0f / ceaihack::config::features::timewarp::rate );

   uintptr_t frame_ms_1 = *(uintptr_t *) ( location + 0x185 ), frame_ms_2 = *(uintptr_t *) ( location + 0x1FC ),
             frame_ms_3 = *(uintptr_t *) ( location + 0x21C );

   *(double *) frame_ms_1 = *(double *) frame_ms_2 = *(double *) frame_ms_3 = new_frame_ms;
}

void ceaihack::cheat::features::timewarp::update() {
   // if it was not jitted yet just make sure to wait until a proper player instance has been found lol
   // if a player instance exists and the pointer to the jitted function doesn't exist, we go and search for it(aka call init)
   if ( player_update_addy == NULL && osu::player::is_instance() ) {
      ceaihack::cheat::memory::dmp_mem_regions();
      init();
   }

   // run what depends on player_update_addy.
   if ( player_update_addy != NULL ) {
      // patch the Timewarp check once and for all!
      patch_timewarp_check();
   }

   // update gamebase timings to make better replays
   patch_gamebase_update_timings();
}

void ceaihack::cheat::features::timewarp::unload() {
   // disable stuff
   config::features::timewarp::enabled = false;

   // call the patcher one more time(yes, lazy).
   patch_timewarp_check();
   patch_gamebase_update_timings();
}

void __stdcall ceaihack::cheat::features::timewarp::rate_change_hook( double rate ) {
   ceaihack::logger::features->debug( "set_CurrentPlaybackRate called! Rate = {}", rate );
   ceaihack::config::features::timewarp::o_rate = rate;

   if ( ceaihack::config::features::timewarp::enabled ) {
      ceaihack::logger::features->debug( "Timewarp enabled. Forcing new rate to be {}", (double) ( ceaihack::config::features::timewarp::rate * 100 ) );
      ceaihack::hooks::variables::o_set_current_playback_rate( ceaihack::config::features::timewarp::rate * 100 );
      return;
   }

   ceaihack::hooks::variables::o_set_current_playback_rate( rate );
}
