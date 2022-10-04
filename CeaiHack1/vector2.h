#pragma once
// vector2 class done by kat - thank him, not me. i'm still a retard

#include <algorithm>
#include <cmath>
#include <imgui.h>
#include <limits>
#include <numeric>

#define M_PI 3.14159265358979323846

struct vector2_t {
   float x, y;

   vector2_t() = default;
   vector2_t( float x, float y ) : x( x ), y( y ){};
   vector2_t( float value ) : x( value ), y( value ){};
   vector2_t( const vector2_t &vector ) {
      *this = vector;
   }

   vector2_t( const ImVec2 &vector ) : x( vector.x ), y( vector.y ){};

   inline bool operator==( const vector2_t &rhs ) const {
      return this->x == rhs.x && this->y == rhs.y;
   }

   inline vector2_t &operator+=( const vector2_t &rhs ) {
      this->x += rhs.x;
      this->y += rhs.y;

      return *this;
   }

   inline vector2_t &operator-=( const vector2_t &rhs ) {
      this->x -= rhs.x;
      this->y -= rhs.y;

      return *this;
   }

   inline vector2_t &operator/=( const vector2_t &rhs ) {
      this->x /= rhs.x;
      this->y /= rhs.y;

      return *this;
   }

   inline vector2_t &operator*=( const vector2_t &rhs ) {
      this->x *= rhs.x;
      this->y *= rhs.y;

      return *this;
   }

   inline vector2_t operator+( const vector2_t &rhs ) const {
      return { this->x + rhs.x, this->y + rhs.y };
   }

   inline vector2_t operator-( const vector2_t &rhs ) const {
      return { this->x - rhs.x, this->y - rhs.y };
   }

   inline vector2_t operator/( const vector2_t &rhs ) const {
      return { this->x / rhs.x, this->y / rhs.y };
   }

   inline vector2_t operator*( const vector2_t &rhs ) const {
      return { this->x * rhs.x, this->y * rhs.y };
   }

   inline vector2_t operator<( const vector2_t &rhs ) const {
      return this->x < rhs.x && this->y < rhs.y;
   }

   inline vector2_t operator>( const vector2_t &rhs ) const {
      return this->x > rhs.x && this->y > rhs.y;
   }

   inline vector2_t operator<=( const vector2_t &rhs ) const {
      return this->x <= rhs.x && this->y <= rhs.y;
   }

   inline vector2_t operator>=( const vector2_t &rhs ) const {
      return this->x >= rhs.x && this->y >= rhs.y;
   }

   inline float dot( const vector2_t &rhs ) const {
      return this->x * rhs.x + this->y * rhs.y;
   }

   // x_k0tori lol
   inline double distance( const vector2_t &target ) const {
      auto x_sqrd = std::pow( x - target.x, 2 );
      auto y_sqrd = std::pow( y - target.y, 2 );

      return sqrt( x_sqrd + y_sqrd );
   }

   // from kat
   inline vector2_t cos_interpolate_to( const vector2_t &transformation, float transformation_time ) {
      auto c = ( 1 - cosf( transformation_time * (float) M_PI ) ) / 2;

      this->x = this->x * ( 1 - c ) + ( transformation.x * c );
      this->y = this->y * ( 1 - c ) + ( transformation.y * c );

      return *this;
   }

   // from kat again
   /*static float hermite(float a, float a_tangent, float b, float b_tangent, float t) {
       float num = powf(t, 2);
       float num2 = t * num;
       float num3 = 2f * num2 - 3f * num + 1f;
       float num4 = -2f * num2 + 3f * num;
       float num5 = num2 - 2f * num + t;
       float num6 = num2 - num;

       return a * num3 + b * num4 + a_tangent * num5 + b_tangent * num6;
   }*/

   inline float length_squared() const {
      return this->x * this->x + this->y * this->y;
   }

   inline float length() const {
      return this->x + this->y;
   }

   inline vector2_t normalized() const {
      return *this / this->length();
   }

   inline vector2_t delta( const vector2_t &rhs ) const {
      return *this - rhs;
   }

   inline vector2_t &interpolate_to( const vector2_t &transformation, float transformation_time ) {
      this->x = std::lerp( this->x, transformation.x, transformation_time );
      this->y = std::lerp( this->y, transformation.y, transformation_time );

      return *this;
   }

   inline vector2_t &interpolate_from( const vector2_t &transformation, float transformation_time ) {
      this->x = std::lerp( transformation.x, this->x, transformation_time );
      this->y = std::lerp( transformation.y, this->y, transformation_time );

      return *this;
   }

   inline vector2_t mid( const vector2_t &b ) const {
      return { std::midpoint( this->x, b.x ), std::midpoint( this->y, b.y ) };
   }

   inline float relative_angle( const vector2_t &rhs ) const {
      return std::acos( std::fmax( -1.f, std::fmin( 1.f, normalized().dot( rhs.normalized() ) ) ) );
   }

   inline vector2_t rotate( float angle ) const {
      const auto cos_angle = std::cos( angle );
      const auto sin_angle = std::sin( angle );

      return { cos_angle * this->x + sin_angle * this->y, -sin_angle * this->x + cos_angle * this->y };
   }

   inline bool empty() const {
      return true ? !this->x && !this->y : false;
   }

   inline bool is_finite() const {
      return true ? std::isfinite( this->length() ) : false;
   }

   inline vector2_t finite() const {
      if ( this->is_finite() )
         return *this;

      return {};
   }

   inline ImVec2 imvec() const {
      return ImVec2( this->x, this->y );
   }

   inline vector2_t clamp( float range ) {
      return { std::clamp( this->x, -range, range ), std::clamp( this->y, -range, range ) };
   }

   inline vector2_t &direction_clamp( float range ) {
      *this - ( this->normalized() * range );

      return *this;
   }
};