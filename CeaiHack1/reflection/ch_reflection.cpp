#include "ch_reflection.h"
#include "../ch_logger.h"

void ceaihack::reflection::init() {
	osu_assembly = domain.get_assembly(L"osu!, Version");
	ceaihack::logger::cheat->info("Got osu! assembly reference!");

	osu_player_t = osu_assembly.find_type(L"#=zdLJxrX5Y0pd7KawJUxF7qjUOhFbS");
	ceaihack::logger::cheat->info("Got ref to type osu.GameModes.Play.Player!");
}