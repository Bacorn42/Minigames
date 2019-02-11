#ifndef PIANOGAMESTATE_H_INCLUDED
#define PIANOGAMESTATE_H_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "state.h"
#include "button.h"
#include "fret.h"
#include "particle.h"
#include "utilities.h"

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <cmath>

class PianoGameState : public State
{
    public:
        PianoGameState(StateStack& stack, Context context);
        virtual bool handleEvent(sf::Event& event);
        virtual bool update(sf::Time dt);
        virtual void draw();
        void explodeParticles(sf::Time life, int maxSpeed, sf::Color color, sf::Vector2f pos, int amount);
        void handlePress(int column);
        Fret::Bonus fretBonus();

    private:
        sf::Sprite mBackground;
        std::vector<std::unique_ptr<Fret>> mFrets;
        std::vector<std::unique_ptr<Particle>> mParticles;
        std::vector<std::unique_ptr<Button>> mButtons;
        sf::Time mFretSpawnTime;
        sf::Text mTexts[10];
        sf::Time mSurviveTime;
        int mScore;
        int mCombo;
        int mLives;
        int mMaxCombo;
        int mFretCounter;
        bool mDead;
};

#endif // PIANOGAMESTATE_H_INCLUDED
