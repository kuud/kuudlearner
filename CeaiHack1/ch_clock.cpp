#include "ch_clock.h"

std::chrono::time_point<std::chrono::high_resolution_clock> ceaihack::cheat::clock::get_current() {
   return std::chrono::high_resolution_clock::now();
}

long long ceaihack::cheat::clock::get_current_time() {
   return get_current().time_since_epoch().count();
}

float ceaihack::cheat::clock::get_delta() {
   auto                                     t     = get_current();
   std::chrono::duration<float, std::milli> delta = t - last_time;
   last_time                                      = t;

   return delta.count();
}