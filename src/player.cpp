#include "player.h"

Player::Player(State::Context context)
: mContext(context)
, mSprite(context.textures->get(Textures::PlayerSheet), sf::IntRect(0,0,32,32))
, mDir(Down)
, mFrameTime()
, mDead(false)
, mShieldTime(sf::Time::Zero)
, mShield(32)
, rising(false)
, explode(false)
{
    mSprite.setPosition(sf::Vector2f(300,300));
    centerOrigin(mSprite);
    mShield.setFillColor(sf::Color(0,255,255,96));
    mShield.setOutlineThickness(4);
    mShield.setOutlineColor(sf::Color(0,128,128,96));
    centerOrigin(mShield);
}

void Player::handleEvent(sf::Event& event)
{

}

void Player::update(sf::Time dt)
{
    const int Speed = 300;
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
       mSprite.getPosition().x < 540)
    {
        mSprite.move(Speed * dt.asSeconds(), 0);
        mDir = Right;
    }
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) &&
            mSprite.getPosition().y < 540)
    {
        mSprite.move(0, Speed * dt.asSeconds());
        mDir = Down;
    }
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
            mSprite.getPosition().x > 60)
    {
        mSprite.move(-Speed * dt.asSeconds(), 0);
        mDir = Left;
    }
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) &&
            mSprite.getPosition().y > 60)
    {
        mSprite.move(0, -Speed * dt.asSeconds());
        mDir = Up;
    }
    const int Frames = 4;
    const sf::Time AnimationTime = sf::seconds(0.5 / Frames);
    mFrameTime += dt;
    if(mFrameTime.asSeconds() > AnimationTime.asSeconds() * Frames)
        mFrameTime = sf::seconds(0);
    mSprite.setTextureRect(sf::IntRect(32 * int(mFrameTime.asSeconds()/AnimationTime.asSeconds()), 32 * mDir, 32, 32));
    mShield.setPosition(mSprite.getPosition());
    if(isShield())
    {
        mShieldTime -= dt;
        if(mShieldTime <= sf::seconds(2.f))
        {
            sf::Color color = mShield.getFillColor();
            if(rising)
            {
                color.a += 48;
                if(color.a >= 96)
                    rising = false;
            }
            else
                {
                color.a -= 48;
                if(color.a <= 0)
                    rising = true;
            }
            mShield.setFillColor(color);
        }
        else if(mShieldTime <= sf::seconds(5.f))
        {
            sf::Color color = mShield.getFillColor();
            if(rising)
            {
                color.a += 16;
                if(color.a >= 96)
                    rising = false;
            }
            else
                {
                color.a -= 16;
                if(color.a <= 0)
                    rising = true;
            }
            mShield.setFillColor(color);
        }
    }
}

void Player::draw()
{
    if(!mDead)
    {
        sf::RenderWindow& window = *mContext.window;
        window.draw(mSprite);
        if(isShield())
            window.draw(mShield);
    }
}

sf::FloatRect Player::getBoundingRect()
{
    return mSprite.getGlobalBounds();
}

void Player::kill()
{
    mDead = true;
}

bool Player::isDead()
{
    return mDead;
}

sf::Vector2f Player::getPosition()
{
    return mSprite.getPosition();
}

void Player::shield()
{
    mShieldTime = sf::seconds(10.f);
    mShield.setFillColor(sf::Color(0,255,255,96));
    explode = true;
}

bool Player::isShield()
{
    return mShieldTime > sf::seconds(0.f);
}

bool Player::canExplode()
{
    if(explode)
    {
        explode = false;
        return true;
    }
    return false;
}
