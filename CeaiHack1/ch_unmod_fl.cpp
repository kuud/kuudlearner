#include "ch_config.h"
#include "ch_game_signature.h"
#include "ch_hooks_vars.h"
#include "ch_logger.h"
#include "ch_memory.h"
#include "ch_memory_addy.h"

#include "ch_unmod_fl.h"
#include "osu/osu.h"

#include "MinHook.h"

void ceaihack::cheat::features::unmod::flashlight::update() {
   // yes our shit code is back! check if it's jitted ofc!
   if ( ( ceaihack::memory::location::check_flashlight_hax == NULL || ceaihack::memory::location::update_flashlight == NULL ) &&
        ceaihack::osu::player::is_instance() ) {
      ceaihack::cheat::memory::dmp_mem_regions();

      if ( ceaihack::memory::location::check_flashlight_hax == NULL )
         ceaihack::memory::location::check_flashlight_hax = (void *) ceaihack::cheat::memory::search_pattern(
             ceaihack::cheat::signatures::player_check_flashlight_hax_signature, "xxxxxxxxxxxxx????xxxxx????xxx" );

      if ( ceaihack::memory::location::update_flashlight == NULL )
         ceaihack::memory::location::update_flashlight =
             (void *) ceaihack::cheat::memory::search_pattern( ceaihack::cheat::signatures::ruleset_osu_update_flashlight_signature, "xxxxxxxxxxx" );

#ifdef _DEBUG
      printf( "FL: CheckFlashlightHax @ %08x\n", (uintptr_t) ceaihack::memory::location::check_flashlight_hax );
      printf( "FL: UpdateFlashlight @ %08x\n", (uintptr_t) ceaihack::memory::location::update_flashlight );
#endif
   }

   // hook checkFlashlightHax
   if ( ceaihack::memory::location::check_flashlight_hax != NULL && ceaihack::hooks::variables::o_check_flashlight_hax == nullptr ) {
      if ( MH_CreateHook(
               ceaihack::memory::location::check_flashlight_hax,
               reinterpret_cast<void *>( &check_flashlight_hax_hook ),
               reinterpret_cast<void **>( &ceaihack::hooks::variables::o_check_flashlight_hax ) ) != MH_OK ) {
         ceaihack::logger::cheat->error( "Failed to hook Player.checkFlashlightHax!" );
      }
      else {
         ceaihack::logger::cheat->info( "Hooked Player.checkFlashlightHax!" );
         MH_EnableHook( ceaihack::memory::location::check_flashlight_hax );
      }
   }

   // hook UpdateFlashlight
   if ( ceaihack::memory::location::update_flashlight != NULL && ceaihack::hooks::variables::o_update_flashlight == nullptr ) {
      if ( MH_CreateHook(
               ceaihack::memory::location::update_flashlight,
               reinterpret_cast<void *>( &update_flashlight_hook ),
               reinterpret_cast<void **>( &ceaihack::hooks::variables::o_update_flashlight ) ) != MH_OK ) {
         ceaihack::logger::cheat->error( "Failed to hook Ruleset.UpdateFlashlight!" );
      }
      else {
         ceaihack::logger::cheat->info( "Hooked Ruleset.UpdateFlashlight!" );
         MH_EnableHook( ceaihack::memory::location::update_flashlight );
      }
   }
}

void __fastcall ceaihack::cheat::features::unmod::flashlight::update_flashlight_hook( void *ecx, void *edx ) {
   // fl unmod code happens here
   if ( ceaihack::osu::player::is_instance() ) {
      auto player = ceaihack::osu::player::instance();

      if ( player->ruleset != nullptr && player->ruleset->sprite_manager_flashlight != nullptr ) {
         player->ruleset->sprite_manager_flashlight->alpha =
             (float) !ceaihack::config::features::game_modifiers::unmod::flashlight; // lazy lol just convert bool to float easy deal!
      }
   }

   if ( !ceaihack::config::features::game_modifiers::unmod::flashlight )
      ceaihack::hooks::variables::o_update_flashlight(
          ecx, edx ); // fuck it we won't call the original function when the unmod is enabled. easy bypass (part 2) lol
}

void __fastcall ceaihack::cheat::features::unmod::flashlight::check_flashlight_hax_hook( void *ecx, void *edx ) {
   if ( !ceaihack::config::features::game_modifiers::unmod::flashlight )
      ceaihack::hooks::variables::o_check_flashlight_hax(
          ecx, edx ); // fuck it we won't call the original function when the unmod is enabled. easy bypass (part 1) lol
}