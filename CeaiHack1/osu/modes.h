#pragma once
namespace ceaihack::osu {
    enum class mode_e : int
    {
        menu,
        edit,
        play,
        exit,
        select_edit,
        select_play,
        select_drawings,
        rank,
        update,
        busy,
        unknown,
        lobby,
        match_setup,
        select_multi,
        ranking_vs,
        online_selection,
        options_offset_wizard,
        ranking_tag_coop,
        ranking_team,
        beatmap_import,
        package_updater,
        benchmark,
        tourney,
        charts
    };
}