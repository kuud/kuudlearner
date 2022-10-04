#include "ch_auth.h"

void ceaihack::cheat::auth::init() {
#ifdef _DEBUG
   ceaihack::cheat::auth::auth_data.role = (ch_user_role_e) ( Member | VIP | Developer );
   strcpy( ceaihack::cheat::auth::auth_data.username, "debug_build" );
   strcpy( ceaihack::cheat::auth::auth_data.token, "70ce5999-1734-4666-957c-d5a9386b728d" );
   ceaihack::cheat::auth::auth_data.check = CH_AUTH_DEFAULT_CHECK_VALUE;
#else
   ceaihack::cheat::auth::auth_data.role = (ch_user_role_e) ( Member | VIP );
   strcpy( ceaihack::cheat::auth::auth_data.username, "release_build" );
   strcpy( ceaihack::cheat::auth::auth_data.token, "009ddc15-8247-4510-87ea-dcf3b702b5b3" );
   ceaihack::cheat::auth::auth_data.check = CH_AUTH_DEFAULT_CHECK_VALUE;
#endif
}