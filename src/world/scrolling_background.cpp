//
// Created by Gianni on 13/01/2024.
//

#include "scrolling_background.hpp"


const float ScrollingBackground::m_scroll_speed = 50;

ScrollingBackground::ScrollingBackground(sf::Texture& texture, const sf::Vector2i &size)
{
    texture.setRepeated(true);

    sf::Rect<int> sprite_rect {{0, 0}, size};

    m_scrollable_background.front().setTexture(texture);
    m_scrollable_background.front().setTextureRect(sprite_rect);

    m_scrollable_background.back() = m_scrollable_background.front();
    m_scrollable_background.back().setPosition(0, m_scrollable_background.front().getGlobalBounds().height);
}

//BackGround::BackGround(TextureManager &texture_manager)
//{
//    sf::Vector2u map_size = static_cast<sf::Vector2u>(texture_manager.get("test_map3").getSize());
//
//    sf::Texture& texture = texture_manager.get("yellow"); // todo: texture should come from parameter
//    texture.setRepeated(true);
//
//    uint32_t texture_height = texture.getSize().y;
//    uint32_t sprite_height = map_size.y + (texture_height - map_size.y % texture_height);
//
//    sf::IntRect sprite_rect {
//        0, 0,
//        static_cast<int>(map_size.x),
//        static_cast<int>(sprite_height)
//    };
//
//    m_scrollable_background[0].setTexture(texture);
//    m_scrollable_background[0].setTextureRect(sprite_rect);
//
//    m_scrollable_background[1] = m_scrollable_background[0];
//    m_scrollable_background[1].setPosition(0, m_scrollable_background[0].getGlobalBounds().height);
//}

void ScrollingBackground::update(double dt)
{
//    static bool current = false;
//
//    m_scrollable_background[0].move(0, m_scroll_speed * dt);
//    m_scrollable_background[1].move(0, m_scroll_speed * dt);
//
//    if (m_scrollable_background[current].getPosition().y > 0)
//    {
//        current = !current;
//        m_scrollable_background[current].setPosition(0, int(m_scrollable_background[!current].getPosition().y - m_scrollable_background[current].getGlobalBounds().height));
//    }

    float move_speed = m_scroll_speed * dt;

    m_scrollable_background.front().move(0, move_speed);
    m_scrollable_background.back().move(0, move_speed);

    if (m_scrollable_background.front().getPosition().y > 0)
    {
        sf::Vector2f new_pos(0, m_scrollable_background.front().getPosition().y - m_scrollable_background.front().getGlobalBounds().height);

        m_scrollable_background.back().setPosition(new_pos);

        std::swap(m_scrollable_background.front(), m_scrollable_background.back());
    }
}

void ScrollingBackground::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_scrollable_background.front());
    target.draw(m_scrollable_background.back());
}
