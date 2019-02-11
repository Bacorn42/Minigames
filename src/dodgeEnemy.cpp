#include "dodgeEnemy.h"

DodgeEnemy::DodgeEnemy(State::Context context, int x, int y, char dir, sf::Time delay)
: mContext(context)
, mSprite(context.textures->get(Textures::DodgeGameSheet), sf::IntRect(0,0,32,32))
, mFrameTime()
, mDelayConst(delay)
, mDelay(delay)
, dir(dir)
{
    mSprite.setPosition(sf::Vector2f(x,y));
    setColor();
    centerOrigin(mSprite);
}

void DodgeEnemy::handleEvent(sf::Event& event)
{

}

void DodgeEnemy::update(sf::Time dt)
{
    if(mDelay.asSeconds() <= 0)
    {
        const int Speed = 200;
        if(dir == 'r')
            mSprite.move(Speed * dt.asSeconds(), 0);
        else if(dir == 'd')
            mSprite.move(0, Speed * dt.asSeconds());
        else if(dir == 'l')
            mSprite.move(-Speed * dt.asSeconds(), 0);
        else if(dir == 'u')
            mSprite.move(0, -Speed * dt.asSeconds());
        const int Frames = 4;
        const sf::Time AnimationTime = sf::seconds(0.25 / Frames);
        mFrameTime += dt;
        if(mFrameTime.asSeconds() > AnimationTime.asSeconds() * Frames)
            mFrameTime = sf::seconds(0);
        mSprite.setTextureRect(sf::IntRect(32 * int(mFrameTime.asSeconds()/AnimationTime.asSeconds()), 0, 32, 32));
        mSprite.rotate(720 * dt.asSeconds());
    }
    else
    {
        mDelay -= dt;
        setColor();
    }
}

void DodgeEnemy::draw()
{
    sf::RenderWindow& window = *mContext.window;
    window.draw(mSprite);
}

bool DodgeEnemy::destroy()
{
    if((dir == 'r' && mSprite.getPosition().x > 556) ||
       (dir == 'l' && mSprite.getPosition().x < 44) ||
       (dir == 'u' && mSprite.getPosition().y < 44) ||
       (dir == 'd' && mSprite.getPosition().y > 556))
        return true;
    return false;
}

void DodgeEnemy::setColor()
{
    sf::Color sprColor = mSprite.getColor();
    sprColor.a = std::min(255 * (1-(mDelay.asSeconds()/mDelayConst.asSeconds())), 255.f);
    mSprite.setColor(sprColor);
}

sf::Vector2f DodgeEnemy::getPosition()
{
    return mSprite.getPosition();
}

sf::FloatRect DodgeEnemy::getBoundingRect()
{
    return mSprite.getGlobalBounds();
}
