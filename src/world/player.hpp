//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_PLAYER_HPP
#define PLATFORMER_PLAYER_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include "../asset_managers/texture_manager.hpp"


class Player : public sf::Drawable
{
public:
    Player(const TextureManager& texture_manager);

    void update(double dt);
    void handle_event(const sf::Event& event);
    void move(float x, float y);

    const sf::FloatRect& get_hit_box() const;
    sf::Vector2f get_center() const;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite m_sprite;
    sf::FloatRect m_hit_box;
    sf::Vector2f m_velocity;
};


#endif //PLATFORMER_PLAYER_HPP
