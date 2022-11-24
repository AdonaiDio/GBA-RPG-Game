#pragma once
#include "my_bn_headers.h"

#include "bn_sprite_items_grid_cell.h"

class Object{
public:
    int x; // posição x Global em grid
    int y; // posição y Global em grid
    bn::fixed spritePos_x; //valor em pixels de x
    bn::fixed spritePos_y;
    //int collider_width;
    //int collider_height;
    bn::rect collider;


    bn::fixed GridToSpritePos_x(int gridPos_x);
    bn::fixed GridToSpritePos_y(int gridPos_y);

    bn::sprite_ptr object_sprite;
    static constexpr auto& object_sprite_ROM = bn::sprite_items::grid_cell;

    Object(int pos_x, int pos_y, int width, int height);
    ~Object();
private:

};