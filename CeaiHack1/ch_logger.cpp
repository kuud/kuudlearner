#include "ch_logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>

void ceaihack::logger::init() {
   try {
      spdlog::set_pattern( "[%T]%^ %n: %v%$" );

      cheat = spdlog::stdout_color_mt( "CeaiHack" );
      cheat->set_level( spdlog::level::trace );

      features = spdlog::stdout_color_mt( "CHEATS" );
      features->set_level( spdlog::level::trace );
   }
   catch ( const spdlog::spdlog_ex &ex ) {
      std::cout << "Logger Initialization failed! " << ex.what() << std::endl;
      while ( 1 )
         ;
   }
}