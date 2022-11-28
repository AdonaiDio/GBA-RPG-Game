#pragma once

#include "my_bn_headers.h"

#include "Player.h"
#include "Object.h"

#include "bn_sprite_items_grid_cell.h"
//#include "bn_regular_bg_items_pokemon_map_static.h"
#include "bn_regular_bg_tiles_items_pkm_tileset.h"

class Player;

class Scene
{
public:
    static constexpr int grid_max_columns = 32;
    static constexpr int grid_max_rows = 32;

    static constexpr int grid_cell_width = 16;
    static constexpr int grid_cell_height = 16;

    Player* player;
    Object object;

    //bn::regular_bg_ptr pkm_bg;
    bn::regular_bg_tiles_ptr pkm_bg_tiles;
    bn::camera_ptr camera;

    Scene();
    ~Scene();

    void willCollide();
    void Reset();

private:
    
};

