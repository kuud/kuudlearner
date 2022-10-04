#include "ch_aim_assist.h"
#include "ch_clock.h"
#include "ch_config.h"
#include "ch_logger.h"
#include "ch_memory.h"

using namespace ceaihack::utils;

vector2_t last_point( 0 );
float     last_importance = 1;

int old_d_time = 0;

// megumi AA
// update: he changed something: y1*(1-mu)+y2*mu
// static sdk::vector2f calculate_point(const sdk::vector2f& mouse_pos, const sdk::vector2f& object_pos, float importance) {
//	const auto x = object_pos.x - (object_pos.x * importance + mouse_pos.x * (1.f - importance));
//	const auto y = object_pos.y - (object_pos.y * importance + mouse_pos.y * (1.f - importance));
//
//	return { object_pos.x - x, object_pos.y - y };
//}
//
//
//
// auto       z = std::min(screen_size.x, screen_size.y) / 2;
//
// auto importance = in_radius(last_position, object_position, radius) ? last_importance : powf(1.0f - std::min(1.0f, std::max(dist / z, 0.0f)), power);

void ceaihack::cheat::features::aimassist::update() {}

vector2_t ceaihack::cheat::features::aimassist::calculate_point( vector2_t object, vector2_t cursor ) {
   /*if (last_importance < 0.1f)
      return last_point;*/

   const auto distance    = cursor.delta( object ).length();
   auto       screen_size = get_screen();

   auto amplitude = 120;
   auto power     = 1.f / ( 2.f + ceaihack::config::features::aimassist::power ) * amplitude;

   float half_screen = (float) min( screen_size.width, screen_size.height ) / 2;
   auto  importance  = powf( 1.0f - min( 1.0f, max( distance / half_screen, 0.0f ) ), power );

   const auto x = object.x - ( object.x * importance + cursor.x * ( 1.f - importance ) );
   const auto y = object.y - ( object.y * importance + cursor.y * ( 1.f - importance ) );

   vector2_t calculated_point = { object.x - x, object.y - y };

   last_importance = importance;
   last_point      = calculated_point;

   return calculated_point;
}

void ceaihack::cheat::features::aimassist::perform_aim_correction( osu::player *player, vector2_t pos ) {
   cursor_position = pos;
   auto out        = player->hom->get_current_object();

   if ( out.base != 0 ) {
      object_position    = get_relative_pos_to_gamefield( out.base_position.get() );
      object_radius      = player->get_object_radius();
      predicted_position = calculate_point( object_position, cursor_position );

      auto current_radius = pos.distance( object_position );

      if ( current_radius <= object_radius * ceaihack::config::features::aimassist::radius_start_correction && current_radius > object_radius ) {
         /*cursor_position = cursor_position.interpolate_to(predicted_position, ceaihack::cheat::clock::get_delta() * 0.35);*/
         // cursor_position.interpolate_to(predicted_position, ceaihack::cheat::clock::get_delta() * 0.35);
         cursor_position.interpolate_to( predicted_position, 0.35f );
      }
   }
}

void ceaihack::cheat::features::aimassist::perform_auto_aim( osu::player *player ) {
   auto time    = osu::gamebase::get_time();
   auto delta   = abs( time - old_d_time );
   auto objects = player->hom->hit_objects;

   auto interp_time = ceaihack::config::features::aimassist::auto_interp_time;

   if ( time <= ( objects[0].start_time.get() - 1500 ) )
      cursor_position = get_relative_pos_to_gamefield( { 256, 500 } );
   else {
      if ( time <= ( objects[0].start_time.get() - 1000 ) )
         cursor_position.interpolate_to( get_relative_pos_to_gamefield( { 256, 192 } ), clock::get_delta() * config::features::aimassist::auto_interp_time );
      else {
         auto preempt       = player->hom->calc_preempt_time();
         auto reaction_time = player->hom->apply_mods_to_rate( 100 );

         int wait_time = (int) max( 0.0, preempt - reaction_time );

         for ( int i = 0; i < objects.length; i++ ) {
            auto object = objects[i];

            if ( object.is_hit.get() || time > object.end_time.get() )
               continue; // if our current time is past the current object time, we continue, just to save time.

            if ( time >= ( object.start_time.get() - wait_time ) &&
                 time <= object.end_time.get() ) { // check if time is in the [start - preempt; end] interval.
               auto prev_obj   = objects[max( 0, i - 1 )];
               auto prev_loc   = get_relative_pos_to_gamefield( prev_obj.base_position.get() );
               object_position = get_relative_pos_to_gamefield( object.base_position.get() );

               cursor_position.interpolate_to( object_position, clock::get_delta() * config::features::aimassist::auto_interp_time );
               break;
            }
         }
      }
   }
   old_d_time = osu::gamebase::get_time();
}

void __fastcall ceaihack::cheat::features::aimassist::set_cursor_position_hook( void *ecx, void *edx, vector2_t pos ) {
   s_cursor_position = pos;

   if ( ceaihack::config::features::aimassist::enabled && ceaihack::osu::player::is_instance() ) {
      auto player = ceaihack::osu::player::instance();

      if ( player->hom->beatmap != nullptr && player->hom->hit_objects.is_valid() && player->hom->hit_objects.length > 0 ) {
         if ( !ceaihack::config::features::aimassist::auto_aim )
            perform_aim_correction( player.get(), pos );
         else
            perform_auto_aim( player.get() );
      }
   }
   else
      cursor_position = pos;

   ceaihack::hooks::variables::o_set_cursor_position( ecx, edx, cursor_position );
}