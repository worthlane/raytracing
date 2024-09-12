#include "graphics/convertion.hpp"

// ----------------------------------------------------------------------

Graphics::Sprite::Sprite()
{
    sf::Sprite sprite_;
}

// ----------------------------------------------------------------------

Graphics::Sprite::~Sprite()
{
}

// ----------------------------------------------------------------------

void Graphics::Sprite::set_texture(const sf::Texture &texture, bool reset_rect)
{
    sprite_.setTexture(texture, reset_rect);
}

// ----------------------------------------------------------------------

void Graphics::Sprite::set_position(float x, float y)
{
    sprite_.setPosition(x, y);
}

// ----------------------------------------------------------------------

sf::Sprite Graphics::Sprite::get_sprite() const
{
    return sprite_;
}
