#ifndef RESOURCEIDENTIFIERS_H_INCLUDED
#define RESOURCEIDENTIFIERS_H_INCLUDED

namespace sf
{
    class Texture;
    class Font;
}

namespace Textures
{
    enum ID
    {
        MenuButtons,
        PlayerSheet,
        DodgeGameSheet,
        PianoBackground,
        PianoGameSheet
    };
}

namespace Fonts
{
    enum ID
    {
        Main
    };
}

template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIERS_H_INCLUDED
