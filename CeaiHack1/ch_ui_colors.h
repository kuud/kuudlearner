#pragma once
#include "imgui.h"

namespace ceaihack::cheat::ui::color {
   inline ImColor background( 37, 37, 37 );

   inline ImColor tab_selected( 91, 174, 238 );
   inline ImColor button_color( 59, 59, 59 );
   inline ImColor background_content( 25, 25, 25 );

   inline ImVec2 tab_btn_size( 115, 25 );
   inline ImVec2 ui_size( 650, 400 );
   inline ImVec2 ui_size_auth( 550, 300 );

   // role colors
   inline ImColor role_member( 240, 69, 144 );
   inline ImColor role_vip( 255, 204, 0 );
   inline ImColor role_developer( 91, 174, 238 );
} // namespace ceaihack::cheat::ui::color