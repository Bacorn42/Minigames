#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>
#include <string>
#include <sstream>

template<typename T>
void centerOrigin(T& img)
{
    sf::FloatRect bounds = img.getLocalBounds();
    img.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

template<typename T>
std::string toString(T input)
{
    std::stringstream ss;
    ss << input;
    return ss.str();
}

template<typename T>
T fromString(std::string& input)
{
    std::stringstream ss(input);
    T value;
    ss >> value;
    return value;
}

#endif // UTILITIES_H_INCLUDED
