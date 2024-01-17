//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_WORLD_HPP
#define PLATFORMER_WORLD_HPP

#include <memory>
#include <SFML/Window/Event.hpp>
#include "tile_map.hpp"
#include "back_ground.hpp"
#include "player.hpp"
#include "collision.hpp"

#include <SFML/Graphics/RectangleShape.hpp> // todo: remove


class World
{
public:
    World(GameContext& context);

    void handle_events(const sf::Event& event);
    void update(double dt);
    void draw();

private:
    void handle_player_collision();

private:
    GameContext& m_context;
    TileMap m_tile_map;
    BackGround m_background;
    Player m_player;
};


#endif //PLATFORMER_WORLD_HPP
