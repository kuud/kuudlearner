#pragma once
#include <cstring>

#define CH_AUTH_DEFAULT_CHECK_VALUE 0x7271337

enum ch_user_role_e { Member = 0, VIP = 1 << 1, Developer = 1 << 2 };

struct ch_auth_data_t {
   char           username[256];
   char           token[128];
   ch_user_role_e role = Member;
   int            check;
};

namespace ceaihack::cheat::auth {
   void init();

   inline ch_auth_data_t auth_data;
} // namespace ceaihack::cheat::auth