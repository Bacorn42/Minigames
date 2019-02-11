#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class Particle
{
    public:
        Particle(sf::RenderWindow& window, sf::Time life, sf::Vector2f velocity, sf::Color color, sf::Vector2f pos);
        void update(sf::Time dt);
        void draw();
        bool isDead();

    private:
        sf::RenderWindow& mWindow;
        sf::RectangleShape mParticle;
        sf::Time mLifeConst;
        sf::Time mLife;
        sf::Vector2f mVelocity;
};

#endif // PARTICLE_H_INCLUDED
