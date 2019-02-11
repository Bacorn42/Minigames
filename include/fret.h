#ifndef FRET_H_INCLUDED
#define FRET_H_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "state.h"
#include "resourceHolder.h"
#include "resourceIdentifiers.h"
#include "utilities.h"

class Fret
{
    public:
        enum Bonus
        {
            None,
            Heart
        };

        Fret(State::Context context, sf::Color color, sf::Vector2f pos, int speed, int column, Bonus bonus);
        void update(sf::Time dt);
        void draw();
        bool isDead();
        sf::Color getColor();
        sf::Vector2f getPosition();
        int getColumn();
        int getBonus();

    private:
        State::Context mContext;
        Bonus mBonus;
        sf::Sprite mSprite;
        sf::Sprite mBonusSprite;
        int mSpeed;
        int mColumn;
};

#endif // FRET_H_INCLUDED
