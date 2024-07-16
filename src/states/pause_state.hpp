//
// Created by Gianni on 10/02/2024.
//

#ifndef PLATFORMER_PAUSE_STATE_HPP
#define PLATFORMER_PAUSE_STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "state.hpp"
#include "../structs/colors.hpp"
#include "../audio/sound_player.hpp"
#include "../audio/music_player.hpp"
#include "../world/parallel_task.hpp"


class PauseState : public State
{
public:
    PauseState(StateStack& state_stack, GameContext& context, void* user_ptr = nullptr);

    void on_exit() override;
    void on_return() override;

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    void play_callback();
    void restart_callback();
    void settings_callback();
    void menu_callback();
    void desktop_callback();

private:
    sf::RectangleShape m_dark_overlay;
};


#endif //PLATFORMER_PAUSE_STATE_HPP
