#pragma once

#include "Player.h"
#include "Scene.h"

#include "bn_optional.h"
#include "bn_optional_fwd.h"

using MaybeDirection = bn::optional<Player::Direction>;


namespace FSM {

class FSM_Player;

class FSM_Player_State;
class FSM_Player_Idle;
class FSM_Player_Walk;
class FSM_Player_Run;

enum class FSM_PlayerType {
    Idle,
    Walk,
    Run,
    None
};


class FSM_Player_State {
public:
    using FSM_Player_State_ptr = FSM_Player_State*;
    Player &player;
    Player::Direction direction;
    bool is_valid;
    FSM_PlayerType state_type;

    FSM_Player_State(Player&, Player::Direction);               // Entry
    virtual ~FSM_Player_State() = default;                      // Exit
    virtual void Update(FSM_Player_State_ptr& estado) = 0;      // Update

    static void SwapToState(FSM_Player_State_ptr&, FSM_Player_State_ptr);

    static int ToGraphicsIndex(const int&, Player::Direction);
    static MaybeDirection direction_pressed();
};
using FSM_Player_State_ptr = FSM_Player_State*;

struct FSM_Player_Idle : public FSM_Player_State {
    FSM_Player_Idle(Player&, Player::Direction); // Entry
    ~FSM_Player_Idle() = default; // Exit
    void Update(FSM_Player_State_ptr& estado);
};

struct FSM_Player_Walk : public FSM_Player_State {
    FSM_Player_Walk(Player&, Player::Direction);
    void Update(FSM_Player_State_ptr& estado);
    ~FSM_Player_Walk() = default;
};

struct FSM_Player_Run : public FSM_Player_State {
    FSM_Player_Run(Player&, Player::Direction);
    void Update(FSM_Player_State_ptr& estado);
    ~FSM_Player_Run() = default;
};

}