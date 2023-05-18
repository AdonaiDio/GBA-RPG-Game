#pragma once

#include "my_bn_headers.h"

#include "Player.h"
#include "Object.h"

#include "bn_sprite_items_grid_cell.h"
//#include "bn_regular_bg_items_pokemon_map_static.h"
//#include "bn_regular_bg_tiles_items_pkm_tileset.h"
#include "bn_regular_bg_items_pkm_village.h"
#include "bn_regular_bg_items_pkm_village1.h"
#include "bn_regular_bg_items_pkm_village2.h"


class Player;

class Scene
{
public:
    static constexpr int grid_max_columns = 32;
    static constexpr int grid_max_rows = 32;

    static constexpr int grid_cell_width = 16;
    static constexpr int grid_cell_height = 16;
    static constexpr int cells_count = grid_max_columns * grid_max_rows;

    Player* player;
    Object object;

    bn::camera_ptr camera;
    //bn::regular_bg_ptr pkm_bg;
    //bn::regular_bg_tiles_ptr pkm_bg_tiles;
    //bn::regular_bg_ptr pkm_village;
    bn::regular_bg_ptr pkm_village1;
    bn::regular_bg_ptr pkm_village2;
    int coliderMap[123][2] = { {14, 7} ,{15, 7},{16, 7},{17, 7},{18, 7},{19, 7},{20, 7},{21, 7},
        {14, 8},{21, 8},{12, 9},{13, 9},{14, 9},{21, 9},{22, 9},{23, 9},{12, 10},{23, 10},{12, 11},{23, 11},
        {24, 11},{25, 11},{12, 12},{13, 12},{14, 12},{15, 12},{16, 12},{25, 12},{16, 13},{25, 13},{16, 14},
        {17, 14},{18, 14},{19, 14},{20, 14},{25, 14},{20, 15},{25, 15},{20, 16},{25, 16},{2, 17},{3, 17},
        {4, 17},{5, 17},{6, 17},{7, 17},{8, 17},{9, 17},{10, 17},{11, 17},{12, 17},{13, 17},{14, 17},{15, 17},
        {18, 17},{19, 17},{20, 17},{25, 17},{26, 17},{27, 17},{2, 18},{15, 18},{18, 18},{27, 18},{2, 19},
        {15, 19},{16, 19},{17, 19},{18, 19},{27, 19},{2, 20},{27, 20},{2, 21},{4, 21},{5, 21},{6, 21},{7, 21},
        {27, 21},{2, 22},{4, 22},{6, 22},{7, 22},{12, 22},{15, 22},{16, 22},{17, 22},{18, 22},{27, 22},{2, 23},
        {4, 23},{12, 23},{13, 23},{14, 23},{15, 23},{18, 23},{27, 23},{2, 24},{12, 24},{18, 24},{19, 24},
        {20, 24},{25, 24},{26, 24},{27, 24},{2, 25},{12, 25},{20, 25},{21, 25},{22, 25},{23, 25},{24, 25},
        {25, 25}, { 2, 26 }, { 3, 26 }, { 4, 26 }, { 5, 26 }, { 6, 26 }, { 7, 26 }, { 8, 26 }, { 9, 26 }, { 10, 26 }, { 11, 26 }, { 12, 26 } };


    Scene();
    ~Scene();

    void willCollide();
    void Reset();

private:
    
};

