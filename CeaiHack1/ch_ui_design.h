#pragma once

#include "ch_ui_colors.h"
#include <string>

namespace ceaihack::cheat::ui::design {
   // CeaiHack UI Header
   void header();

   // CeaiHack UI Tabs
   void tabs();

   // Visuals Menu
   void visuals();

   // Timewarp Menu
   void timewarp();

   // Aim Assist Menu
   void aim_assist();

#ifdef _DEBUG
   // CeaiHack Debug
   void debug();

   // CeaiHack Objects Debug
   void beatmap_debug();
#endif

   // role helpers
   ImColor     user_role_to_color();
   std::string user_role_to_string();
} // namespace ceaihack::cheat::ui::design