#include "fret.h"

Fret::Fret(State::Context context, sf::Color color, sf::Vector2f pos, int speed, int column, Bonus bonus)
: mContext(context)
, mBonus(bonus)
, mSprite(context.textures->get(Textures::PianoGameSheet))
, mBonusSprite(context.textures->get(Textures::PianoGameSheet))
, mSpeed(speed)
, mColumn(column)
{
    mSprite.setTextureRect(sf::IntRect(0,0,64,32));
    mSprite.setColor(color);
    mSprite.setPosition(pos);
    mBonusSprite.setTextureRect(sf::IntRect(32 * (bonus - 1), 32, 32, 32));
    centerOrigin(mBonusSprite);
    mBonusSprite.setPosition(mSprite.getPosition() + sf::Vector2f(31, 16));
}

void Fret::update(sf::Time dt)
{
    mSprite.move(0, mSpeed * dt.asSeconds());
    mBonusSprite.setPosition(mSprite.getPosition() + sf::Vector2f(31, 16));
}

void Fret::draw()
{
    sf::RenderWindow& window = *mContext.window;

    window.draw(mSprite);
    if(mBonus >= 0)
        window.draw(mBonusSprite);
}

bool Fret::isDead()
{
    return mSprite.getPosition().y > 548;
}

sf::Color Fret::getColor()
{
    return mSprite.getColor();
}

sf::Vector2f Fret::getPosition()
{
    return mSprite.getPosition() + sf::Vector2f(32, 16);
}

int Fret::getColumn()
{
    return mColumn;
}

int Fret::getBonus()
{
    return mBonus;
}
