#include "ch_game_modifier.h"
#include "ch_config.h"
#include "ch_game_signature.h"
#include "ch_logger.h"
#include "ch_memory.h"

#include "./osu/osu.h"
#include <stdio.h>

uintptr_t hom_update_variables_addy = NULL;

constexpr auto original_code = "\xDD\x5D\xE0\xDD\x45\xE0"; // it's the same lol

void ceaihack::cheat::features::game_modifier::init() {
   hom_update_variables_addy =
       ceaihack::cheat::memory::search_pattern( ceaihack::cheat::signatures::hom_update_variables_signature, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" );
#ifdef _DEBUG
   printf( "GMod: HitObjectManager::UpdateVariables @ %08X\n", hom_update_variables_addy );
#endif
}

// the shit is so common so i'll just make a function that does it automatically
void patcher( uintptr_t offset, bool enabled, void *value ) {
   uintptr_t location = hom_update_variables_addy + offset;

   if ( enabled ) {
      if ( *(uint16_t *) ( location ) != 0x05D9 ) {
         *(uint16_t *) ( location )        = 0x05D9;
         *(uintptr_t *) ( location + 0x2 ) = (uintptr_t) value;
         ceaihack::logger::features->info( "Patched code in memory at {0:X}!", location );
      }
   }
   else {
      if ( memcmp( (BYTE *) location, (BYTE *) original_code, 6 ) != 0 ) {
         memcpy( (BYTE *) location, (BYTE *) original_code, 6 );
         ceaihack::logger::features->info( "Restored original code in memory at {0:X}!", location );
      }
   }
}

void patch_preempt() {
   // ar changer aka preempt modifier
   patcher( 0x1A7, ceaihack::config::features::game_modifiers::approach_rate::enabled, &ceaihack::config::features::game_modifiers::approach_rate::new_value );
}

void patch_sprite_display_size() {
   // cs changer aka spritedisplaysize modifier
   patcher( 0x210, ceaihack::config::features::game_modifiers::circle_size::enabled, &ceaihack::config::features::game_modifiers::circle_size::new_value );
}

void ceaihack::cheat::features::game_modifier::update() {
   // if it was not jitted yet just make sure to wait until a proper player instance has been found lol
   if ( hom_update_variables_addy == NULL && !osu::player::is_instance() )
      return;

   // if a player instance exists and the pointer to the jitted function doesn't exist, we go and search for it(aka call init)
   if ( hom_update_variables_addy == NULL ) {
      ceaihack::cheat::memory::dmp_mem_regions();
      init();
   }

   // if it still doesn't exist, just return out of this.
   if ( hom_update_variables_addy == NULL )
      return;

   // now let the fun begin!
   patch_preempt();
   patch_sprite_display_size();
}

void ceaihack::cheat::features::game_modifier::unload() {
   // disable stuff
   config::features::game_modifiers::approach_rate::enabled = false;
   config::features::game_modifiers::circle_size::enabled   = false;

   // call patchers one more time(yes, lazy).
   patch_preempt();
   patch_sprite_display_size();
}