#ifndef DODGEGAMESTATE_H_INCLUDED
#define DODGEGAMESTATE_H_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "state.h"
#include "player.h"
#include "dodgeEnemy.h"
#include "particle.h"
#include "button.h"
#include "dodgeItem.h"

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <cmath>

class DodgeGameState : public State
{
    public:
        DodgeGameState(StateStack& stack, Context context);
        virtual bool handleEvent(sf::Event& event);
        virtual bool update(sf::Time dt);
        virtual void draw();
        void handleCollisions();
        void spawnEnemy(int difficulty);
        void spawnItem();
        void explodeParticles(sf::Time life, int maxSpeed, sf::Color color, sf::Vector2f pos, int amount);

    private:
        Player mPlayer;
        std::vector<std::unique_ptr<DodgeEnemy>> mEnemies;
        sf::RectangleShape mPlayerBorder;
        sf::Time mEnemySpawnTime;
        sf::Time mSurviveTime;
        std::vector<std::unique_ptr<Particle>> mParticles;
        sf::Text mTexts[6];
        std::vector<std::unique_ptr<Button>> mButtons;
        std::vector<std::unique_ptr<DodgeItem>> mItems;
        sf::Time mItemSpawner;
        int mScore;
};

#endif // DODGEGAMESTATE_H_INCLUDED
