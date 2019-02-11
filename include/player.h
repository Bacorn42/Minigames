#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "state.h"
#include "resourceHolder.h"
#include "resourceIdentifiers.h"
#include "utilities.h"

class Player
{
    public:
        Player(State::Context context);
        void handleEvent(sf::Event& event);
        void update(sf::Time dt);
        void draw();
        sf::FloatRect getBoundingRect();
        void kill();
        bool isDead();
        sf::Vector2f getPosition();
        void shield();
        bool isShield();
        bool canExplode();

    private:
        enum Direction
        {
            Down,
            Left,
            Right,
            Up
        };

        State::Context mContext;
        sf::Sprite mSprite;
        Direction mDir;
        sf::Time mFrameTime;
        bool mDead;
        sf::Time mShieldTime;
        sf::CircleShape mShield;
        bool rising;
        bool explode;
};

#endif // PLAYER_H_INCLUDED
