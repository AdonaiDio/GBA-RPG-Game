#include "Player.h"
#include "FSM/FSM_Player.h"
using namespace FSM;


FSM_Player_Walk::FSM_Player_Walk(Player& P, Player::Direction D)
    : FSM_Player_State(P, D){
    state_type = FSM_PlayerType::Walk;
    player.current_direction = D;
    // Checks if we can really enter this state
    //Scene::willCollide();
    player.current_scene->willCollide();

    ////////////



    ////////////
    
    if(player.onCollision){  // use a condition here //////////////////////////////////////////////////////
        // Oh no, we can't actually use this state right now!
        is_valid = false;
        return;
    }
    if (is_valid) {
        // Actually finish entering this state
        switch (direction) {
        case Player::Direction::up:
            player.player_sprite.set_horizontal_flip(false);
            player.nextPos_y -= 1;
            // BN_LOG(__FILE__, " ", __func__, " ", __LINE__, " ", "up");

            break;
        case Player::Direction::down:
            player.player_sprite.set_horizontal_flip(false);
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
    }
    
    int _direction = ToGraphicsIndex(Graphics::Character_index::walk, direction);
    player.player_sprite_animation = bn::create_sprite_animate_action_forever(
                    player.player_sprite, player.animFrameWait, 
                    bn::sprite_items::brandon_walk_run.tiles_item(),
                    _direction, _direction+1,
                    _direction+2, _direction+1);
    player.last_direction = direction;
    BN_LOG("Nova direcao >> animacao <<");
    
        
    BN_LOG("Anim WALK");
}

void FSM_Player_Walk::Update(FSM_Player_State_ptr& current_state){
    auto new_direction = direction_pressed();

    if(player.x == player.nextPos_x
       && player.y == player.nextPos_y){
        if(new_direction)
            SwapToState(current_state, new FSM_Player_Walk(player, new_direction.value()));
        else            
            SwapToState(current_state, new FSM_Player_Idle(player, direction));
        return;
    } 
    else if(bn::keypad::a_held() || bn::keypad::a_pressed()){
        SwapToState(current_state, new FSM_Player_Run(player, direction));
        return;
    }
}
