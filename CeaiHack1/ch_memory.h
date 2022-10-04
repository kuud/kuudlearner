#pragma once
#include <Windows.h>
#include <string>
#include <vector>

#include "ch_memory_addy.h"

namespace ceaihack::cheat::memory {
   void      init();
   uintptr_t search_pattern( const char *pattern, const char *mask );
   void      dmp_mem_regions();
} // namespace ceaihack::cheat::memory