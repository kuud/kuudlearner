#pragma once
#include <Windows.h>
#include <iostream>

namespace ceaihack::cheat {
   DWORD WINAPI init( LPVOID lpParam );

   inline HMODULE hModule;
} // namespace ceaihack::cheat