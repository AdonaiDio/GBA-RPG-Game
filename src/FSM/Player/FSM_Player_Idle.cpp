#include "Player.h"
#include "FSM/FSM_Player.h"
using namespace FSM;

FSM_Player_Idle::FSM_Player_Idle(Player& P, Player::Direction D)
    : FSM_Player_State(P, D) {

    state_type = FSM_PlayerType::Idle;

    // BN_LOG(__FILE__, " ", __func__, " ", __LINE__, " ", "entered idle");


    int _direction = ToGraphicsIndex(Graphics::Character_index::idle, direction);
    player.player_sprite_animation = bn::create_sprite_animate_action_forever(
                    player.player_sprite, player.animFrameWait, 
                    bn::sprite_items::brandon_walk_run.tiles_item(),
                    _direction+1, _direction+1,
                    _direction+1, _direction+1);
    BN_LOG("Nova direcao >> animacao <<");
    
    BN_LOG("Anim IDLE");
}



void FSM_Player_Idle::Update(FSM_Player_State_ptr& current_state){
    auto new_direction = direction_pressed();
    
    if (new_direction) {
        //player.last_direction = player.current_direction;
        SwapToState(current_state, new FSM_Player_Walk(player, new_direction.value()));
        return;
    }
}
