
#include "Player.h"

#include "FSM/FSM_Player.h"


// correção em posição global
bn::fixed Player::sprite_x(int cursor_x) {
    return (cursor_x * Scene::grid_cell_width) - ((Scene::grid_max_columns / 2) * Scene::grid_cell_width) ;
}

bn::fixed Player::sprite_y(int cursor_y) {
    return (cursor_y * Scene::grid_cell_height) - ((Scene::grid_max_rows / 2) * Scene::grid_cell_height) - (Scene::grid_cell_height / 2);
}

Player::Player(int pos_x, int pos_y, int collider_width, int collider_height, Scene* this_scene) :
    x(pos_x),
    y(pos_y),
    nextPos_x(x),
    nextPos_y(y),
    spritePos_x(sprite_x(x)),
    spritePos_y(sprite_y(y)),
    collider(spritePos_x.integer(), spritePos_y.integer(), collider_width, collider_height),
    onCollision(false),
    animFrameWait(4),
    current_direction(Player::Direction::down),
    last_direction(Player::Direction::down),
    player_sprite(player_sprite_ROM.create_sprite(sprite_x(x), sprite_y(y))),
    player_sprite_animation(bn::create_sprite_animate_action_forever(
        player_sprite, animFrameWait, bn::sprite_items::brandon_walk_run.tiles_item(),
        Graphics::Character_index::idle_down, Graphics::Character_index::idle_down,
        Graphics::Character_index::idle_down, Graphics::Character_index::idle_down)),
    fsm_player(new FSM::FSM_Player_Idle(*this, Direction::down)),
    current_scene(this_scene)
{
    MoveTo(pos_x, pos_y);
}
Player::~Player() {}


void Player::MoveTo(int target_x, int target_y){
    x = target_x;
    y = target_y;
    player_sprite.set_position(sprite_x(x), sprite_y(y));
}

int aceleration = 1;

//void Player::CheckCollision(bn::rect& collider) {
//    
//}

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

    if (spritePos_x < sprite_x(nextPos_x) ||
        spritePos_x > sprite_x(nextPos_x) ||
        spritePos_y < sprite_y(nextPos_y) ||
        spritePos_y > sprite_y(nextPos_y)) {
        //current_scene->willCollide();
        //BN_LOG("OnCollision is: ", onCollision);
        if (onCollision) {
            nextPos_x = x;
            nextPos_y = y;
            spritePos_x = sprite_x(x);
            spritePos_y = sprite_y(y);
            camera.set_position(spritePos_x, spritePos_y);
            collider.set_position(sprite_x(x).integer(), sprite_y(y).integer()+ (Scene::grid_cell_height / 2));
        }
        else {
        
            if(spritePos_x < sprite_x(nextPos_x)){ //direita
                camera.set_x(camera.x() + aceleration);
                spritePos_x += aceleration;
            }
            else if(spritePos_x > sprite_x(nextPos_x)){ //esquerda
                camera.set_x(camera.x() - aceleration);
                spritePos_x -= aceleration;
            }
            else if(spritePos_y < sprite_y(nextPos_y)){ //baixo
                camera.set_y(camera.y() + aceleration);
                spritePos_y += aceleration;
            }
            else if(spritePos_y > sprite_y(nextPos_y)){ //cima
                camera.set_y(camera.y() - aceleration);
                spritePos_y -= aceleration;
            }
            if(spritePos_x == sprite_x(nextPos_x)){ //se chegou no destino, quebra o loop de animação e movimento do sprite
                x = nextPos_x;
            }
            if(spritePos_y == sprite_y(nextPos_y)){ //aqui também.
                y = nextPos_y;
            }
            //////////////////
            switch (current_direction) {
            case Direction::up:
                BN_LOG("CurDir : up");

                break;
            case Direction::down:
                BN_LOG("CurDir : down" );

                break;
            case Direction::left:
                BN_LOG("CurDir : left" );

                break;
            default:
            case Direction::right:
                BN_LOG("CurDir : right" );

                break;
            }
            /////////////////////
            //////////////////
            switch (last_direction) {
            case Direction::up:
                BN_LOG("lastDir : up");

                break;
            case Direction::down:
                BN_LOG("lastDir : down");

                break;
            case Direction::left:
                BN_LOG("lastDir : left");

                break;
            default:
            case Direction::right:
                BN_LOG("lastDir : right");

                break;
            }
            /////////////////////
        }
    }
    collider.set_position(int_spritePos_x, int_spritePos_y + (Scene::grid_cell_height / 2));
    player_sprite.set_position(spritePos_x, spritePos_y);
    onCollision = false;

}

void Player::Update(bn::camera_ptr& camera) {
    player_sprite_animation.update();
    TranslateSprite(camera);
    fsm_player->Update(fsm_player);
}

