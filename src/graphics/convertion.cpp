#include "graphics/convertion.hpp"

// ----------------------------------------------------------------------

Sprite::Sprite()
{
    sf::Sprite sprite_;
}

// ----------------------------------------------------------------------

Sprite::~Sprite()
{
}

// ----------------------------------------------------------------------

void Sprite::set_texture(const sf::Texture &texture, bool reset_rect)
{
    sprite_.setTexture(texture, reset_rect);
}

// ----------------------------------------------------------------------

void Sprite::set_position(float x, float y)
{
    sprite_.setPosition(x, y);
}

// ----------------------------------------------------------------------

sf::Sprite Sprite::get_sprite() const
{
    return sprite_;
}
