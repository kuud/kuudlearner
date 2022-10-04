#pragma once
namespace ceaihack::osu {
    enum class object_type_e : int {
        circle = 1 << 0,
        slider = 1 << 1,
        new_combo = 1 << 2,
        spinner = 1 << 3,
        combo_offset = 1 << 4 | 1 << 5 | 1 << 6,
        hold = 1 << 7
    };
}