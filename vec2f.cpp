#include "vec2f.h"

using namespace zen;

Vec2f::Vec2f()
    : sf::Vector2f(0,0)
{
}
Vec2f::Vec2f(float x, float y)
    : sf::Vector2f(x, y)
{
}
Vec2f::Vec2f(const sf::Vector2f& other)
    : sf::Vector2f(other)
{
}
Vec2f::Vec2f(const sf::Vector2u& other)
    : sf::Vector2f(other)
{
}
float Vec2f::length()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2f::operator sf::Vector2i()
{
    return sf::Vector2i(x, y);
}

Vec2f& Vec2f::operator=(const Vec2f& other)
{
    //Vec2f newVec;

    //x = other.x;
    //y = other.y;
    Vec2f tmp(other);

    std::swap(x, tmp.x);
    std::swap(y, tmp.y);
    return *this;

}
Vec2f& Vec2f::operator=(const sf::Vector2f& other)
{
    Vec2f tmp(other);

    std::swap(x, tmp.x);
    std::swap(y, tmp.y);
    return *this;
}
Vec2f& Vec2f::operator=(const sf::Vector2u& other)
{
    Vec2f tmp(other);

    std::swap(x, tmp.x);
    std::swap(y, tmp.y);
    return *this;
}

Vec2f& Vec2f::operator*=(const Vec2f& other)
{
    this->x *= other.x;
    this->y *= other.y;

    return *this;
}
Vec2f operator*(Vec2f lhs, const Vec2f& rhs)
{
    lhs *= rhs;
    return lhs;
}
