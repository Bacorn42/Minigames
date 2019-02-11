#ifndef DODGEITEM_H_INCLUDED
#define DODGEITEM_H_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "state.h"
#include "utilities.h"
#include "resourceHolder.h"
#include "resourceIdentifiers.h"

class DodgeItem
{
    public:
        enum Type
        {
            CoinBronze,
            CoinSilver,
            CoinGold,
            Shield,
            Bomb
        };

        DodgeItem(State::Context context, Type type, sf::Vector2f pos);
        void update(sf::Time dt);
        void draw();
        Type getType();
        sf::Vector2f getPosition();
        sf::FloatRect getBoundingRect();
        bool isDead();

    private:
        State::Context mContext;
        Type mType;
        sf::Sprite mSprite;
        sf::Time mFrameTime;
        sf::Time mLifeTime;
        bool rising;
};

#endif // DODGEITEM_H_INCLUDED
