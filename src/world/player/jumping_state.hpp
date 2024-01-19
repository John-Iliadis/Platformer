//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_JUMPING_STATE_HPP
#define PLATFORMER_JUMPING_STATE_HPP

#include "player_state.hpp"
#include "../../utilities/utils.hpp"


class JumpingState : public PlayerState
{
public:
    void on_enter(Player &player) override;
    void on_exit(Player &player) override;

    PlayerState *handle_event(Player &player, const sf::Event &event) override;
    PlayerState *update(Player &player, double dt) override;
};


#endif //PLATFORMER_JUMPING_STATE_HPP
