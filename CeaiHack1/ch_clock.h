#pragma once
#include <chrono>

namespace ceaihack::cheat::clock {
   std::chrono::time_point<std::chrono::high_resolution_clock> get_current();
   long long                                                   get_current_time();

   float get_delta();

   inline auto last_time = get_current();
} // namespace ceaihack::cheat::clock