#pragma once
#include <Windows.h>

namespace ceaihack::hooks {
   bool init();
   void unload();

   // detours
   bool __stdcall swap_buffers( HDC context );
} // namespace ceaihack::hooks