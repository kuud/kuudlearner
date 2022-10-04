#pragma once

namespace ceaihack::cheat::features::unmod::flashlight {
   void update();
   void __fastcall check_flashlight_hax_hook( void *ecx, void *edx );
   void __fastcall update_flashlight_hook( void *ecx, void *edx );
} // namespace ceaihack::cheat::features::unmod::flashlight