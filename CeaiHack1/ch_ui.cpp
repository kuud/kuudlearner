#include "ch_ui.h"
#include "ch_auth.h"
#include "ch_config.h"
#include "ch_logger.h"
#include "ch_memory.h"
#include "ch_ui_design.h"

#include "ch_aim_assist.h"

#include "glad/glad.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

#include <iostream>

bool  is_init = false;
HHOOK original_get_message_proc;

extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam );

LRESULT CALLBACK message_proc_callback( int code, WPARAM wparam, LPARAM lparam ) {
   if ( code > 0 )
      return CallNextHookEx( original_get_message_proc, code, wparam, lparam );

   const auto message = (MSG *) lparam;

   if ( wparam == PM_REMOVE ) {
      if ( message->message == WM_KEYDOWN && LOWORD( message->wParam ) == VK_DELETE ) {
         ceaihack::logger::cheat->warn( "Open UI Menu" );
         ceaihack::config::is_menu_open = !ceaihack::config::is_menu_open;
         ImGui::GetIO().MouseDrawCursor = ceaihack::config::is_menu_open;
      }

      if ( ImGui_ImplWin32_WndProcHandler( message->hwnd, message->message, message->wParam, message->lParam ) ) {
         message->message = WM_NULL;
         return 1;
      }
   }

   if ( ceaihack::config::is_menu_open && ( ( message->message >= WM_MOUSEFIRST && message->message <= WM_MOUSELAST ) || message->message == WM_CHAR ) ) {
      message->message = WM_NULL;
      return 1;
   }

   return CallNextHookEx( original_get_message_proc, code, wparam, lparam );
}

void get_style() {
   ImGuiStyle &Style = ImGui::GetStyle();

   Style.ButtonTextAlign = ImVec2( 0, 0.5f ); // left align button text

   Style.Colors[ImGuiCol_WindowBg] = ceaihack::cheat::ui::color::background.Value;
   Style.Colors[ImGuiCol_Button]   = ceaihack::cheat::ui::color::button_color.Value;

   Style.WindowRounding = 5.2f;
   Style.FrameRounding  = 12;
}

void ceaihack::cheat::ui::init( HDC context ) {
   if ( is_init )
      return;

   gladLoadGL();

   auto ctx = ImGui::CreateContext();
   ImGui::SetCurrentContext( ctx );

   ImGui_ImplWin32_Init( WindowFromDC( context ) );

   ImGui_ImplOpenGL3_Init();

   get_style();

   ImGuiIO &IO = ImGui::GetIO();
   // text font
   IO.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Arial.ttf", 16.0F, NULL );

   font_logo  = IO.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Arial.ttf", 23.0F, NULL );
   font_title = IO.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Arial.ttf", 25.0F, NULL );

   IO.IniFilename                       = nullptr;
   IO.LogFilename                       = nullptr;
   IO.ConfigWindowsMoveFromTitleBarOnly = true;

   ceaihack::logger::cheat->info( "Hooking MessageProc..." );
   // original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(WindowFromDC(context), , reinterpret_cast<LONG_PTR>(&WndProc)));
   while ( original_get_message_proc == nullptr )
      original_get_message_proc = SetWindowsHookExA( WH_GETMESSAGE, &message_proc_callback, GetModuleHandleA( nullptr ), GetCurrentThreadId() );

   ceaihack::logger::cheat->info( "UI Init Complete" );
   is_init = true;
}

void ceaihack::cheat::ui::unload() {
   ceaihack::logger::cheat->warn( "Unloading requested!" );
   UnhookWindowsHookEx( original_get_message_proc );
   ImGui_ImplOpenGL3_DestroyDeviceObjects();
}

void ceaihack::cheat::ui::render_tab() {
   switch ( ceaihack::config::current_tab ) {
   case ui_tabs::timewarp:
      ceaihack::cheat::ui::design::timewarp();
      break;
   case ui_tabs::aim_assist:
      ceaihack::cheat::ui::design::aim_assist();
      break;
   case ui_tabs::visuals:
      ceaihack::cheat::ui::design::visuals();
      break;
#ifdef _DEBUG
   case ui_tabs::debug:
      ceaihack::cheat::ui::design::debug();
      break;
#endif
   default:
      break;
   }
}

#ifdef _DEBUG

void TextCentered( std::string text ) {
   auto _window = ImGui::GetWindowSize();
   auto _text   = ImGui::CalcTextSize( text.c_str() );

   ImGui::SetCursorPos( ImVec2( ( _window.x - _text.x ) * 0.5f, ( _window.y - _text.y ) * 0.5f ) );
   ImGui::Text( text.c_str() );
}

#endif

void draw_not_auth_prompt() {
   ImGui::Begin( "CeaiHack Auth", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
   {
      ImGui::SetWindowSize( ceaihack::cheat::ui::color::ui_size_auth );

      ceaihack::cheat::ui::design::header();
      ImGui::Spacing();

      ImGui::PushStyleColor( ImGuiCol_FrameBg, ceaihack::cheat::ui::color::background_content.Value );
      ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( 15.0f, 10.0f ) );
      ImGui::BeginChildFrame( 1, ImVec2( 0.0f, -27.0f ) );
      {
         ImGui::PopStyleColor();
         ImGui::PopStyleVar();
         ImGui::PushFont( ceaihack::cheat::ui::font_title );
         ImGui::Text( "Attention!" );
         ImGui::PopFont();
         ImGui::TextWrapped( "CeaiHack is running in an UNAUTHORIZED state!\n\nThis means that it was either injected with another injector than ours, you are "
                             "trying to reverse/tamper with our cheat or there is an unknown error.\n\nPlease try re-injecting CeaiHack again. If this issue "
                             "still occurs, please contact the CeaiHack development team.\n\nThank you!" );
      }
      ImGui::EndChildFrame();

      ImGui::Spacing();

      float total_w = ImGui::GetContentRegionAvail().x;
      ImGui::SameLine( total_w - 21.f );

      if ( ImGui::Button( "OK" ) ) {
         ceaihack::config::is_running = false;
      }
   }
   ImGui::End();
}

void draw() {
#ifdef _DEBUG
   if ( !ceaihack::config::is_running )
      return;
   if ( ceaihack::cheat::auth::auth_data.check != CH_AUTH_DEFAULT_CHECK_VALUE ) {
      draw_not_auth_prompt();
      return;
   }

   ImGui::SetNextWindowSize( ImVec2( 180, 35 ) );
   ImGui::Begin( "Debug Build", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
   {
      TextCentered( "CeaiHack Debug Build" );
      ImGui::SetWindowPos( ImVec2( ImGui::GetIO().DisplaySize.x - ImGui::GetWindowWidth(), 0 ) );
   }
   ImGui::End();
#endif

   ImGui::Begin( "CeaiHack Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
   {
      ImGui::SetWindowSize( ceaihack::cheat::ui::color::ui_size );

      ceaihack::cheat::ui::design::header();
      ImGui::Spacing();

      ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( 0, 0 ) );
      ImGui::BeginChildFrame( 1, ImVec2( 0.0f, -20.0f ), ImGuiWindowFlags_NoBackground );
      {
         ImGui::PopStyleVar(); // idk i'm a retart
         ceaihack::cheat::ui::design::tabs();

         ImGui::SameLine( 0, 0 );

         ImGui::PushStyleColor( ImGuiCol_FrameBg, ceaihack::cheat::ui::color::background_content.Value );
         ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( 15.0f, 10.0f ) );
         ImGui::PushStyleVar( ImGuiStyleVar_FrameRounding, 0 );

         ImGui::BeginChildFrame( 3, ImVec2( 0.0f, 0.0f ) );
         {
            ImGui::PopStyleColor();  // retard moment again ok
            ImGui::PopStyleVar( 2 ); // another retard moment again ok
            ceaihack::cheat::ui::render_tab();
         }
         ImGui::EndChildFrame();
      }
      ImGui::EndChildFrame();

      ImGui::Text( "Logged in as: " );
      ImGui::SameLine( 0, 0 );

      ImGui::PushStyleColor( ImGuiCol_Text, ceaihack::cheat::ui::design::user_role_to_color().Value );
      ImGui::Text( "%s", ceaihack::cheat::auth::auth_data.username );
      ImGui::PopStyleColor();

      ImGui::SameLine( 0, 0 );
      ImGui::Text( " - %s", ceaihack::cheat::ui::design::user_role_to_string().c_str() );
   }
   ImGui::End();
}

void ceaihack::cheat::ui::on_frame( HDC context ) {
   if ( !is_init )
      init( context );

   ImGui_ImplWin32_NewFrame();
   ImGui_ImplOpenGL3_NewFrame();
   ImGui::NewFrame();

   if ( ceaihack::config::is_menu_open )
      draw();

#ifdef _DEBUG
   if ( ceaihack::config::show_beatmap_objects ) {
      ImGui::SetNextWindowSize( ImVec2( 500, 200 ) );
      ImGui::Begin( "Debug: Beatmap Objects", &ceaihack::config::show_beatmap_objects );
      ceaihack::cheat::ui::design::beatmap_debug();
      ImGui::End();
   }

#ifdef _DEBUG
   if ( ceaihack::config::features::aimassist::enabled && ceaihack::config::features::aimassist::show_prediction ) {
      ImColor normal     = ImColor( 255, 0, 255, 100 );
      ImColor in_radius  = ImColor( 0, 255, 0 );
      ImColor correction = ImColor( 255, 0, 0 );

      auto cursor_pos = ceaihack::cheat::features::aimassist::cursor_position.imvec();
      auto object_pos = ceaihack::cheat::features::aimassist::object_position.imvec();
      auto text_pos   = cursor_pos;
      text_pos.y -= 60;

      auto x_sqrd = ( cursor_pos.x - object_pos.x ) * ( cursor_pos.x - object_pos.x );
      auto y_sqrd = ( cursor_pos.y - object_pos.y ) * ( cursor_pos.y - object_pos.y );

      auto current_radius = sqrt( x_sqrd + y_sqrd );

      bool in_object_radius = current_radius <= ceaihack::cheat::features::aimassist::object_radius;
      bool in_corr_radius =
          current_radius <= ceaihack::cheat::features::aimassist::object_radius * ceaihack::config::features::aimassist::radius_start_correction &&
          current_radius > ceaihack::cheat::features::aimassist::object_radius;

      char tmp[512] = { 0 };
      sprintf(
          tmp,
          "R:%.2f\nC:%.2f\nO%.2f",
          current_radius,
          ceaihack::cheat::features::aimassist::object_radius * ceaihack::config::features::aimassist::radius_start_correction,
          ceaihack::cheat::features::aimassist::object_radius );

      ImGui::GetBackgroundDrawList()->AddCircleFilled(
          object_pos,
          ceaihack::cheat::features::aimassist::object_radius * ceaihack::config::features::aimassist::radius_start_correction,
          ImColor( 0, 255, 255, 100 ) ); // aim correction point - CYAN
      ImGui::GetBackgroundDrawList()->AddCircleFilled(
          object_pos, ceaihack::cheat::features::aimassist::object_radius, ImColor( 0, 255, 0, 100 ) ); // object radius - GREEN

      ImGui::GetBackgroundDrawList()->AddCircleFilled(
          ceaihack::cheat::features::aimassist::predicted_position.imvec(), 15, ImColor( 100, 100, 100 ) ); // cursor position - RED

      ImGui::GetBackgroundDrawList()->AddText( text_pos, ImColor( 255, 255, 255 ), tmp );
      ImGui::GetBackgroundDrawList()->AddLine( cursor_pos, object_pos, in_object_radius ? in_radius : ( in_corr_radius ? correction : normal ), 5 );
      ImGui::GetBackgroundDrawList()->AddCircleFilled(
          ceaihack::cheat::features::aimassist::s_cursor_position.imvec(), 15, ImColor( 255, 255, 0 ) ); // og cursor position - YELLOW
      ImGui::GetBackgroundDrawList()->AddCircleFilled(
          cursor_pos, 15, in_object_radius ? in_radius : ( in_corr_radius ? correction : normal ) ); // cursor position - RED
   }
#endif

#endif

   ImGui::EndFrame();
   ImGui::Render();
   ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
}