#pragma once
#include "my_bn_headers.h"
#include "Graphics.h"


#include "bn_sprite_items_brandon_walk_run.h"

// Forward declaration, see: https://stackoverflow.com/questions/553682/when-can-i-use-a-forward-declaration
namespace FSM {
    class FSM_Player_State;
}


class Player
{
public:

    int x; // posição x Global em grid
    int y; // posição y Global em grid
    int nextPos_x; //controle para movimentação entre grids
    int nextPos_y;
    bn::fixed spritePos_x; //valor em pixels de x
    bn::fixed spritePos_y;
    bn::rect collider;
    //teste
    bool onCollision;

    int animFrameWait;

    enum class Direction {
        down,
        up,
        left,
        right
    };

    Direction current_direction;
    Direction last_direction;

    bn::sprite_ptr player_sprite;
    static constexpr auto& player_sprite_ROM = bn::sprite_items::brandon_walk_run;
    
    bn::sprite_animate_action<4> player_sprite_animation;
    
    bn::fixed sprite_x(int cursor_x);
    bn::fixed sprite_y(int cursor_y);
    FSM::FSM_Player_State* fsm_player;
    

    Player(int pos_x, int pos_y, int collider_width, int collider_height);
    ~Player();

    void MoveTo(int target_x, int target_y);
    void TranslateSprite(bn::camera_ptr& camera);
    void MoveControler();
    void Update(bn::camera_ptr& camera);
    
private:
 
};