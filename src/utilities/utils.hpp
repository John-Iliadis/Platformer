//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_UTILS_HPP
#define PLATFORMER_UTILS_HPP

#include <windows.h>
#include <cstdint>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../world/enums.hpp"


namespace utils
{
    float get_distance(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

    void set_origin(sf::Sprite& sprite, Origin origin);

    float to_radians(float degrees);
    float to_degrees(float radians);
}


#endif //PLATFORMER_UTILS_HPP
