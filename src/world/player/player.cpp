//
// Created by Gianni on 13/01/2024.
//

#include "player.hpp"


Player::Player()
{
    m_textures.load_directory_list("../data/player/player_textures.json");
    m_animations.load_from_file("../data/player/animations.json");
    m_player_data.load_from_file("../data/player/platformer_data.json");

    m_current_state = new IdleState(*this);

    m_sprite_collider.set_hitbox_size(m_player_data.hitbox_size.x, m_player_data.hitbox_size.y);
    m_sprite_collider.set_origin_mid_bottom();
}

Player::~Player()
{
    delete m_current_state;
}

void Player::handle_events(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        m_player_data.jump_pressed_ellapsed_time = m_player_data.jump_pressed_remember_time;
}

void Player::update(double dt)
{
    handle_input();
    update_physics(dt);
    handle_state();
    update_animation(dt);

    m_player_data.jump_pressed_ellapsed_time -= dt;
}

void Player::handle_input()
{
    using namespace sf;
    bool (*key_pressed)(Keyboard::Key) = Keyboard::isKeyPressed;

    if (key_pressed(Keyboard::Left) && key_pressed(Keyboard::Right)
        || (!key_pressed(Keyboard::Left) && !key_pressed(Keyboard::Right)))
    {
        m_player_data.velocity.x = 0;
    }
    else if (key_pressed(Keyboard::Right))
    {
        m_player_data.velocity.x = m_player_data.move_speed;
        m_sprite_collider.set_orientation(SpriteOrientation::FACES_RIGHT);
    }
    else if (key_pressed(Keyboard::Left))
    {
        m_player_data.velocity.x = -m_player_data.move_speed;
        m_sprite_collider.set_orientation(SpriteOrientation::FACES_LEFT);
    }
}

void Player::update_physics(double dt)
{
    apply_gravity();
    m_resolve_collision_callback(dt);
}

void Player::handle_state()
{
    PlayerState* new_state = m_current_state->update(*this);
    change_state(new_state);
}

void Player::update_animation(double dt)
{
    m_animations.update(dt);
    set_animation_frame();
}

void Player::set_collision_callback(std::function<void(double)> callback)
{
    m_resolve_collision_callback = std::move(callback);
}

void Player::set_animation(const std::string &id)
{
    m_animations.set_animation(id);
    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
    m_sprite_collider.set_texture(m_textures.get(id));
}

void Player::set_position(float x, float y)
{
    m_sprite_collider.setPosition(x, y);
}

void Player::move(float x, float y)
{
    m_sprite_collider.move(x, y);
}

void Player::set_gravity(bool on)
{
    m_player_data.gravity = on ? m_player_data.gravity_speed : 0;
}

sf::FloatRect Player::get_hitbox() const
{
    return m_sprite_collider.get_hitbox();
}

sf::Vector2f Player::get_center() const
{
    return m_sprite_collider.get_sprite_center();
}

sf::Vector2f Player::get_position() const
{
    return m_sprite_collider.getPosition();
}

SpriteOrientation Player::get_orientation() const
{
    return m_sprite_collider.get_orientation();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite_collider);
}

void Player::apply_gravity()
{
    m_player_data.velocity.y += m_player_data.gravity;
}

void Player::change_state(PlayerState *new_state)
{
    if (new_state)
    {
        delete m_current_state;
        m_current_state = new_state;
    }
}

void Player::set_animation_frame()
{
    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
}

sf::Vector2f Player::get_velocity() const
{
    return m_player_data.velocity;
}

float Player::get_wall_sliding_speed() const
{
    return m_player_data.wall_sliding_speed;
}

bool Player::previously_jumped() const
{
    return m_player_data.previously_jumped;
}

bool Player::previously_double_jumped() const
{
    return m_player_data.previously_double_jumped;
}

bool Player::touching_wall() const
{
    return m_player_data.touching_wall;
}

void Player::set_previously_jumped(bool prev_jumped)
{
    m_player_data.previously_jumped = prev_jumped;
}

void Player::set_previously_double_jumped(bool prev_double_jumped)
{
    m_player_data.previously_double_jumped = prev_double_jumped;
}

void Player::jump()
{
    m_player_data.jump_pressed_ellapsed_time = 0;
    m_player_data.velocity.y = m_player_data.jump_speed;
}

void Player::set_velocity(float x, float y)
{
    m_player_data.velocity = {x, y};
}

void Player::set_touching_wall(bool touching_wall)
{
    m_player_data.touching_wall = touching_wall;
}

float Player::get_jump_pressed_ellapsed_time() const
{
    return m_player_data.jump_pressed_ellapsed_time;
}

void Player::set_position(const sf::Vector2f &pos)
{
    set_position(pos.x, pos.y);
}
