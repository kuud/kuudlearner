#pragma once
#include "spdlog/spdlog.h"

namespace ceaihack::logger {
   void init();

   inline std::shared_ptr<spdlog::logger> cheat;
   inline std::shared_ptr<spdlog::logger> features;
} // namespace ceaihack::logger