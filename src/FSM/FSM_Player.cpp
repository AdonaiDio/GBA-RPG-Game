#include "Player.h"
#include "FSM/FSM_Player.h"
using namespace FSM;

FSM_Player_State::FSM_Player_State(Player& _player, Player::Direction _direction)
    : player(_player), direction(_direction), is_valid(true){
    // BN_LOG(__FILE__, " ", __func__, " ", __LINE__, " ", "entered state NONE");
}

void FSM_Player_State::SwapToState(FSM_Player_State_ptr& current_state, FSM_Player_State_ptr target_state){
    if(target_state->is_valid){
        auto old_state = current_state;
        current_state = target_state;
        delete old_state;
    } else {
        delete target_state;
    }
}

MaybeDirection FSM_Player_State::direction_pressed(){
    if (bn::keypad::left_held() || bn::keypad::left_pressed())
        return bn::make_optional<Player::Direction>(Player::Direction::left);

    if(bn::keypad::right_held() || bn::keypad::right_pressed())
        return bn::make_optional<Player::Direction>(Player::Direction::right);

    if(bn::keypad::up_held() || bn::keypad::up_pressed())
        return bn::make_optional<Player::Direction>(Player::Direction::up);

    if(bn::keypad::down_held() || bn::keypad::down_pressed())
        return bn::make_optional<Player::Direction>(Player::Direction::down);

    return MaybeDirection(bn::nullopt_t(-1));
}

int FSM_Player_State::ToGraphicsIndex(const int& offset, Player::Direction direction){
    switch(direction){
    case Player::Direction::down:
        return offset + Graphics::Character_index::walk_down;

    case Player::Direction::up:
        return offset + Graphics::Character_index::walk_up;

    case Player::Direction::left:
        return offset + Graphics::Character_index::walk_left;

    default:
    case Player::Direction::right:
        return offset + Graphics::Character_index::walk_left;
    }
}