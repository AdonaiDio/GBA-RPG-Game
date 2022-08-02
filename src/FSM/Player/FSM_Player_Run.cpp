#include "Player.h"
#include "FSM/FSM_Player.h"
using namespace FSM;



FSM_Player_Run::FSM_Player_Run(Player& P, Player::Direction D)
    : FSM_Player_State(P, D){
    FSM_PlayerType old_state_type = state_type;    
    state_type = FSM_PlayerType::Run;
    // Actually finish entering this state
    switch (direction) {
    case Player::Direction::up:
        player.player_sprite.set_horizontal_flip(false);
        player.nextPos_y -= 1;
        // BN_LOG(__FILE__, " ", __func__, " ", __LINE__, " ", "up");

        break;
    case Player::Direction::down:
        player.player_sprite.set_horizontal_flip(true);
        player.nextPos_y += 1;
        // BN_LOG(__FILE__, " ", __func__, " ", __LINE__, " ", "down");

        break;
    case Player::Direction::left:
        player.player_sprite.set_horizontal_flip(false);
        player.nextPos_x -= 1;
        // BN_LOG(__FILE__, " ", __func__, " ", __LINE__, " ", "left");

        break;
    default:
    case Player::Direction::right:
        player.player_sprite.set_horizontal_flip(true);
        player.nextPos_x += 1;
        // BN_LOG(__FILE__, " ", __func__, " ", __LINE__, " ", "right");

        break;
    }
    
    if(player.last_direction != direction || old_state_type != state_type){
        int _direction = ToGraphicsIndex(Graphics::Character_index::run, direction);
        player.player_sprite_animation = bn::create_sprite_animate_action_forever(
                        player.player_sprite, (player.animFrameWait / 2), 
                        bn::sprite_items::brandon_walk_run.tiles_item(),
                        _direction, _direction+1,
                        _direction+2, _direction+1);
        player.last_direction = direction;
        BN_LOG("Nova direcao >> animacao <<");
    }

    BN_LOG("Anim RUN");
}

void FSM_Player_Run::Update(FSM_Player_State_ptr& current_state){
    if(player.x == player.nextPos_x
       && player.y == player.nextPos_y) {
        auto new_direction = direction_pressed();

        if(new_direction){
            if (bn::keypad::a_held())
                SwapToState(current_state, new FSM_Player_Run(player, new_direction.value()));
            else
                SwapToState(current_state, new FSM_Player_Walk(player, new_direction.value()));
            return;
        } else {
            SwapToState(current_state, new FSM_Player_Idle(player, direction));
            return;
        }
    }
}