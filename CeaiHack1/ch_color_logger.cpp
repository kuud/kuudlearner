#include "ch_color_logger.h"

ch_color_logger::ch_color_logger( std::string tag ) {
   colors[log_level::debug]   = FOREGROUND_GREEN | FOREGROUND_BLUE;
   colors[log_level::info]    = FOREGROUND_GREEN;
   colors[log_level::warning] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
   colors[log_level::error]   = FOREGROUND_RED | FOREGROUND_INTENSITY;

   console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
}

void ch_color_logger::log( log_level level, std::string message ) {
   if ( console_handle != NULL && console_handle != INVALID_HANDLE_VALUE ) {
      DWORD written = 0;
      WriteConsoleA( console_handle, message.c_str(), strlen( message.c_str() ), &written, NULL );
#ifdef _DEBUG
      OutputDebugStringW( std::wstring( message.begin(), message.end() ).c_str() );
#endif
   }
}