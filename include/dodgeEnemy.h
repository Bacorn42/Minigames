#ifndef DODGEENEMY_H_INCLUDED
#define DODGEENEMY_H_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "state.h"
#include "resourceHolder.h"
#include "resourceIdentifiers.h"
#include "utilities.h"

class DodgeEnemy
{
    public:
        DodgeEnemy(State::Context context, int x, int y, char dir, sf::Time delay);
        void handleEvent(sf::Event& event);
        void update(sf::Time dt);
        void draw();
        bool destroy();
        void setColor();
        sf::Vector2f getPosition();
        sf::FloatRect getBoundingRect();

    private:
        State::Context mContext;
        sf::Sprite mSprite;
        sf::Time mFrameTime;
        sf::Time mDelayConst;
        sf::Time mDelay;
        char dir;
};

#endif // DODGEENEMY_H_INCLUDED
