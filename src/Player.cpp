
#include "Player.h"
#include "Scene.h"

#include "FSM/FSM_Player.h"

// #include "bn_sprite_items_grid_cell.h"

//teste
// bn::sprite_ptr teste_sprite = bn::sprite_items::grid_cell.create_sprite(sprite_x(x), sprite_y(y));
//



// correção em posição global
bn::fixed Player::sprite_x(int cursor_x) {
    return (cursor_x * Scene::grid_cell_width) - ((Scene::grid_max_columns / 2) * Scene::grid_cell_width) ;
}

bn::fixed Player::sprite_y(int cursor_y) {
    return (cursor_y * Scene::grid_cell_height) - ((Scene::grid_max_rows / 2) * Scene::grid_cell_height) - (Scene::grid_cell_height / 2);
}


Player::Player(int pos_x, int pos_y) : 
    x(pos_x), 
    y(pos_y), 
    nextPos_x(x),
    nextPos_y(y),
    spritePos_x(sprite_x(x)),
    spritePos_y(sprite_y(y)),
    animFrameWait(4),
    current_direction(Player::Direction::down),
    last_direction(Player::Direction::down),
    player_sprite(player_sprite_ROM.create_sprite(sprite_x(x), sprite_y(y))),
    player_sprite_animation(bn::create_sprite_animate_action_forever(
        player_sprite, animFrameWait, bn::sprite_items::brandon_walk_run.tiles_item(), 
        Graphics::Character_index::idle_down, Graphics::Character_index::idle_down, 
        Graphics::Character_index::idle_down, Graphics::Character_index::idle_down)),
    fsm_player(new FSM::FSM_Player_Idle(*this, Direction::up))
{
    MoveTo(pos_x, pos_y);
}

Player::~Player(){}


void Player::MoveTo(int target_x, int target_y){
    x = target_x;
    y = target_y;
    player_sprite.set_position(sprite_x(x), sprite_y(y));
}

int aceleration = 1;


void Player::TranslateSprite(bn::camera_ptr& camera){
    //grid 16x16
    if (fsm_player->state_type == FSM::FSM_PlayerType::Run){
        aceleration = 4;
    } 
    else if (fsm_player->state_type == FSM::FSM_PlayerType::Walk){
        aceleration = 2; //aceleração em pixels
    }

    int int_spritePos_x = spritePos_x.round_integer();
    int int_spritePos_y = spritePos_y.round_integer();

    int new_aceleration = aceleration;

    if((int_spritePos_x % aceleration) != 0)
        new_aceleration += aceleration - (int_spritePos_x % aceleration);

    if((int_spritePos_y % aceleration) != 0)
        new_aceleration += aceleration - (int_spritePos_y % aceleration);

    if(new_aceleration != aceleration)
        aceleration = new_aceleration % aceleration;

    // BN_LOG(__FILE__, " ", __func__, " ", __LINE__, " ", "aceleration: ", aceleration);

    if(spritePos_x < sprite_x(nextPos_x)){
        camera.set_x(camera.x() + aceleration);
        spritePos_x += aceleration;
    }
    else if(spritePos_x > sprite_x(nextPos_x)){
        camera.set_x(camera.x() - aceleration);
        spritePos_x -= aceleration;
    }
    else if(spritePos_y < sprite_y(nextPos_y)){
        camera.set_y(camera.y() + aceleration);
        spritePos_y += aceleration;
    }
    else if(spritePos_y > sprite_y(nextPos_y)){
        camera.set_y(camera.y() - aceleration);
        spritePos_y -= aceleration;
    }
    if(spritePos_x == sprite_x(nextPos_x)){
        x = nextPos_x;
    }
    if(spritePos_y == sprite_y(nextPos_y)){
        y = nextPos_y;
    }
    player_sprite.set_position(spritePos_x, spritePos_y);

}

void Player::Update(bn::camera_ptr& camera) {
    player_sprite_animation.update();
    TranslateSprite(camera);
    fsm_player->Update(fsm_player);
    // teste_sprite.set_position(sprite_x(nextPos_x), sprite_y(nextPos_y) + 8);
}

