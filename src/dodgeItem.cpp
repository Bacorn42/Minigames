#include "dodgeItem.h"

DodgeItem::DodgeItem(State::Context context, Type type, sf::Vector2f pos)
: mContext(context)
, mType(type)
, mSprite(context.textures->get(Textures::DodgeGameSheet))
, mFrameTime(sf::Time::Zero)
, mLifeTime(sf::seconds(10.f))
, rising(false)
{
    if(mType == CoinBronze)
    {
        mSprite.setTextureRect(sf::IntRect(0,32,32,32));
        mSprite.setColor(sf::Color(210, 130, 50));
    }
    else if(mType == CoinSilver)
    {
        mSprite.setTextureRect(sf::IntRect(0,32,32,32));
        mSprite.setColor(sf::Color(128,128,128));
    }
    else if(mType == CoinGold)
    {
        mSprite.setTextureRect(sf::IntRect(0,32,32,32));
        mSprite.setColor(sf::Color(180,180,80));
    }
    else if(mType == Shield)
        mSprite.setTextureRect(sf::IntRect(0,64,32,32));
    else if(mType == Bomb)
        mSprite.setTextureRect(sf::IntRect(0,96,32,32));
    centerOrigin(mSprite);
    mSprite.setPosition(pos);
}

void DodgeItem::update(sf::Time dt)
{
    mLifeTime -= dt;
    int Frames = 0;
    if(mType == CoinBronze || mType == CoinSilver || mType == CoinGold)
        Frames = 6;
    else
        Frames = 4;
    const sf::Time AnimationTime = sf::seconds(0.25 / Frames);
    mFrameTime += dt;
    if(mFrameTime.asSeconds() > AnimationTime.asSeconds() * Frames)
        mFrameTime = sf::seconds(0);
    if(mType == CoinBronze || mType == CoinSilver || mType == CoinGold)
    {
        if(int(mFrameTime.asSeconds()/AnimationTime.asSeconds()) <= 3)
            mSprite.setTextureRect(sf::IntRect(32 * int(mFrameTime.asSeconds()/AnimationTime.asSeconds()), 32, 32, 32));
        else
            mSprite.setTextureRect(sf::IntRect(32 * (6 - int(mFrameTime.asSeconds()/AnimationTime.asSeconds())), 32, 32, 32));
    }
    else
        mSprite.setTextureRect(sf::IntRect(32 * int(mFrameTime.asSeconds()/AnimationTime.asSeconds()), 32 * mType - 32, 32, 32));
    if(mLifeTime <= sf::seconds(2.f))
    {
        sf::Color color = mSprite.getColor();
        if(rising)
        {
            color.a += 48;
            if(color.a >= 255)
                rising = false;
        }
        else
            {
            color.a -= 48;
            if(color.a <= 0)
                rising = true;
        }
        mSprite.setColor(color);
    }
    else if(mLifeTime <= sf::seconds(5.f))
    {
        sf::Color color = mSprite.getColor();
        if(rising)
        {
            color.a += 16;
            if(color.a >= 255)
                rising = false;
        }
        else
            {
            color.a -= 16;
            if(color.a <= 0)
                rising = true;
        }
        mSprite.setColor(color);
    }
}

void DodgeItem::draw()
{
    sf::RenderWindow& window = *mContext.window;

    window.draw(mSprite);
}

DodgeItem::Type DodgeItem::getType()
{
    return mType;
}

sf::Vector2f DodgeItem::getPosition()
{
    return mSprite.getPosition();
}

sf::FloatRect DodgeItem::getBoundingRect()
{
    return mSprite.getGlobalBounds();
}

bool DodgeItem::isDead()
{
    return mLifeTime < sf::Time::Zero;
}
