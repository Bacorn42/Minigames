#include "particle.h"

Particle::Particle(sf::RenderWindow& window, sf::Time life, sf::Vector2f velocity, sf::Color color, sf::Vector2f pos)
: mWindow(window)
, mParticle(sf::Vector2f(4,4))
, mLifeConst(life)
, mLife(life)
, mVelocity(velocity)
{
    mParticle.setPosition(pos);
    mParticle.setFillColor(color);
}

void Particle::update(sf::Time dt)
{
    mLife -= dt;
    mParticle.move(mVelocity * dt.asSeconds());
    sf::Color parColor = mParticle.getFillColor();
    parColor.a = std::max(255 * (mLife.asSeconds()/mLifeConst.asSeconds()), 0.f);
    mParticle.setFillColor(parColor);
}

void Particle::draw()
{
    mWindow.draw(mParticle);
}

bool Particle::isDead()
{
    return mLife.asSeconds() <= 0 ? true : false;
}
