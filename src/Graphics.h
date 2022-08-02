#pragma once

#include "my_bn_headers.h"

namespace Graphics {
    //namespace SpriteSheet = bn::sprite_items;
    struct Character_index{
        //idle index
        static constexpr int idle_down = 1;
        static constexpr int idle_up = 4;
        static constexpr int idle_left = 7;
        //walk index
        static constexpr int walk_down = 0;
        static constexpr int walk_up = 3;
        static constexpr int walk_left = 6;
        //run index
        static constexpr int run_down = 9;
        static constexpr int run_up = 12;
        static constexpr int run_left = 15;
        //run offset index
        static constexpr int idle = 0;
        static constexpr int walk = 0;
        static constexpr int run = 9;
    };
}