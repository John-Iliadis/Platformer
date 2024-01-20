//
// Created by Gianni on 18/01/2024.
//

#include "running_state.hpp"
#include "player.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"
#include "idle_state.hpp"


RunningState::RunningState(Player &player)
{
    auto& data = player.get_platformer_data();

    running_animation = LoopingAnimation(32, 32, 12, sf::milliseconds(50));
    player.set_texture("running");
    player.set_texture_rect(static_cast<sf::IntRect>(running_animation.get_current_frame(player.facing_right())));

    data.previously_jumped = false;
    data.previously_double_jumped = false;
}

PlayerState* RunningState::handle_event(Player &player, const sf::Event &event)
{
    return nullptr;
}

PlayerState* RunningState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.time_since_last_jump_button_pressed.getElapsedTime().asSeconds() <= data.jump_pressed_remember_time)
        return new JumpingState(player);

    if (data.velocity.y > 0)
        return new FallingState(player);

    if (data.velocity.x == 0)
        return new IdleState(player);

    running_animation.update();
    player.set_texture_rect(static_cast<sf::IntRect>(running_animation.get_current_frame(data.facing_right)));

    return nullptr;
}
