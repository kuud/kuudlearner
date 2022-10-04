#include "ch.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD reason, LPVOID lpReserved ) {
   if ( reason == DLL_PROCESS_ATTACH ) {
#ifdef _DEBUG
      // alloc a console
      AllocConsole();

      // setup console IO
      freopen_s( (FILE **) stderr, "CONOUT$", "w", stderr );
      freopen_s( (FILE **) stdout, "CONOUT$", "w", stdout );

      // set title
      SetConsoleTitle( L"CeaiHack Debug Console" );

#endif

      ceaihack::cheat::hModule = hModule;
      CreateThread( nullptr, 0, &ceaihack::cheat::init, nullptr, 0, nullptr );
      DisableThreadLibraryCalls( hModule );
   }

   return 1;
}
