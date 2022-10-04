#pragma once
namespace ceaihack::cheat::features::timewarp {
   void init();
   void update();
   void __stdcall rate_change_hook( double rate );
   void unload();
} // namespace ceaihack::cheat::features::timewarp