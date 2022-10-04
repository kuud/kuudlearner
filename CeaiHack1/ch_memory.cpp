#include "ch_memory.h"
#include "ch_game_signature.h"
#include "ch_logger.h"

#include <iostream>
#include <list>

void      dmp_mem_regions();
uintptr_t search_pattern( const char *pattern, const char *mask );

// memory shit because we like to paste

struct MemoryRegion {
   DWORD  BaseAddress;
   SIZE_T RegionSize;
   DWORD  State;
   DWORD  Protect;
   DWORD  Type;

   MemoryRegion( MEMORY_BASIC_INFORMATION32 mbi ) {
      BaseAddress = mbi.BaseAddress;
      RegionSize  = mbi.RegionSize;
      State       = mbi.State;
      Protect     = mbi.Protect;
      Type        = mbi.Type;
   }
};

std::list<MemoryRegion> memoryRegions;

// end of shit

void ceaihack::cheat::memory::init() {
   dmp_mem_regions();
   ceaihack::memory::location::state_base  = *(uintptr_t *) ( search_pattern( ceaihack::cheat::signatures::state_signature, "xxxx????x????x????x" ) + 0x13 );
   ceaihack::memory::location::player_base = *(uintptr_t *) ( search_pattern( ceaihack::cheat::signatures::player_signature, "xxxxxxx" ) + 0x7 );
   ceaihack::memory::location::set_rate    = (void *) search_pattern( ceaihack::cheat::signatures::set_current_playback_rate_signature, "xxxxxx????xxxxx" );
   ceaihack::memory::location::update_playback_rate =
       (void *) ( search_pattern( ceaihack::cheat::signatures::update_playback_rate_signature, "xxxxxxxxxxxxxxxx" ) );
   ceaihack::memory::location::time_base      = *(uintptr_t *) ( search_pattern( ceaihack::cheat::signatures::time_signature, "xx????x????xxx????x" ) + 0x13 );
   ceaihack::memory::location::set_cursor_pos = (void *) ( search_pattern( ceaihack::cheat::signatures::set_cursor_pos_signature, "xxxxxxx????x" ) );
   ceaihack::memory::location::gb_time_base =
       *(uintptr_t *) ( search_pattern( ceaihack::cheat::signatures::gamebase_time_signature, "x????xxxxxxxxxxxxxxx" ) + 0x14 );
   ceaihack::memory::location::gb_window_manager_base =
       *(uintptr_t *) ( search_pattern( ceaihack::cheat::signatures::gamebase_windowmanager_signature, "xxx????xxx????xxx????xx" ) + 0x17 );
   ceaihack::memory::location::update_timing = (void *) search_pattern( ceaihack::cheat::signatures::gamebase_update_timing_signature, "xxxxxxxxxxxxxxx" );
   // ceaihack::cheat::memory::hax_check_audio = (void*)(search_pattern(ceaihack::cheat::signatures::hax_check_audio_signature, "xxxxxx????xxxxx"));

   /*ceaihack::logger::memory->info("BASS handle at {0:x}", ceaihack::cheat::memory::bass_handle);*/

   /*ceaihack::logger::memory->info("state base at {0:x}", ceaihack::cheat::memory::state_base);
   ceaihack::logger::memory->info("player addy at {0:x}", ceaihack::cheat::memory::player_base);
   ceaihack::logger::memory->info("AudioTrack.set_CurrentPlaybackRate at {0:x}", ceaihack::cheat::memory::set_rate);
   ceaihack::logger::memory->info("BASS_ChannelSetAttribute at {0:x}", *ceaihack::cheat::memory::bass_channel_set_attribute);*/
}

void ceaihack::cheat::memory::dmp_mem_regions() {
   memoryRegions.clear();

   MEMORY_BASIC_INFORMATION32 mbi;
   LPCVOID                    address = 0;

   while ( VirtualQueryEx( GetCurrentProcess(), address, reinterpret_cast<PMEMORY_BASIC_INFORMATION>( &mbi ), sizeof( mbi ) ) != 0 ) {

      if ( mbi.State == MEM_COMMIT && mbi.Protect >= 0x10 && mbi.Protect <= 0x80 ) {
         memoryRegions.push_back( *new MemoryRegion( mbi ) );
      }
      address = reinterpret_cast<LPCVOID>( mbi.BaseAddress + mbi.RegionSize );
   }
}

uintptr_t ceaihack::cheat::memory::search_pattern( const char *pattern, const char *mask ) {
   for ( const auto &region : memoryRegions ) {
      size_t patternLength = strlen( mask );

      for ( uintptr_t i = 0; i < region.RegionSize - patternLength; i++ ) {
         bool found = true;
         for ( uintptr_t j = 0; j < patternLength; j++ ) {
            if ( mask[j] != '?' && pattern[j] != *(char *) ( region.BaseAddress + i + j ) ) {
               found = false;
               break;
            }
         }

         if ( found ) {
            ceaihack::logger::cheat->info( "Signature at {0:x}!", region.BaseAddress + i );
            return region.BaseAddress + i;
         }
      }
   }

   return NULL;
}