#include "dodgeGameState.h"

DodgeGameState::DodgeGameState(StateStack& stack, Context context)
: State(stack, context)
, mPlayer(context)
, mEnemies()
, mPlayerBorder(sf::Vector2f(512, 512))
, mEnemySpawnTime(sf::Time::Zero)
, mSurviveTime(sf::Time::Zero)
, mParticles()
, mButtons()
, mItems()
, mItemSpawner(sf::Time::Zero)
, mScore(0)
{
    mPlayerBorder.setPosition(44, 44);
    mPlayerBorder.setOutlineThickness(8);
    mPlayerBorder.setOutlineColor(sf::Color(64,64,64));
    mPlayerBorder.setFillColor(sf::Color(128,128,128));

    for(int i=0; i<6; i++)
    {
        mTexts[i].setFont(context.fonts->get(Fonts::Main));
        mTexts[i].setCharacterSize(20);
        mTexts[i].setColor(sf::Color::White);
        centerOrigin(mTexts[i]);
        mTexts[i].setPosition(600,32+40*i+(i/2) * 60);
    }
    mTexts[0].setString("Seconds survived:");
    mTexts[1].setString("0");
    mTexts[2].setString("Score:");
    mTexts[3].setString("0");
    mTexts[4].setString("Final score:");
    mTexts[5].setString("0");

    const std::string strs[] = {"Restart", "Exit"};
    std::function<void()> funcs[] = {
        [this](){ requestStackPop(); requestStackPush(States::DodgeGame); },
        [this](){ requestStackPop(); requestStackPush(States::GameMenu); }
    };
    for(int i=0; i<2; i++)
    {
        std::unique_ptr<Button> button(new Button(context, strs[i], funcs[i], sf::Vector2f(680, 450 + 60*i)));
        mButtons.push_back(std::move(button));
    }
}

bool DodgeGameState::handleEvent(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
        if(event.key.code == sf::Keyboard::P)
            if(!mPlayer.isDead())
                requestStackPush(States::Pause);
    mPlayer.handleEvent(event);
    for(auto it = mEnemies.begin(); it != mEnemies.end(); it++)
        (*it)->handleEvent(event);
    if(mPlayer.isDead())
        for(auto it = mButtons.begin(); it != mButtons.end(); it++)
            (*it)->handleEvent(event);
    return true;
}

bool DodgeGameState::update(sf::Time dt)
{
    mTexts[1].setString(toString(mSurviveTime.asSeconds()));
    mTexts[3].setString(toString(mScore));
    mTexts[5].setString(toString(mScore * floor(mSurviveTime.asSeconds())));
    if(!mPlayer.isDead())
    {
        mPlayer.update(dt);
        if(!mPlayer.isDead())
            mSurviveTime += dt;
        for(auto it = mEnemies.begin(); it != mEnemies.end(); it++)
        {
            (*it)->update(dt);
            if((*it)->destroy())
            {
                explodeParticles(sf::seconds(0.3), 300, sf::Color::Cyan, (*it)->getPosition(), 30);
                mEnemies.erase(it);
                it--;
            }
        }
        for(auto it = mItems.begin(); it != mItems.end(); it++)
        {
            (*it)->update(dt);
            if((*it)->isDead())
            {
                explodeParticles(sf::seconds(0.2), 300, sf::Color(80,80,80), (*it)->getPosition(), 30);
                mItems.erase(it);
                it--;
            }
        }
        int difficulty = floor(mSurviveTime.asSeconds());
        sf::Time EnemySpawnDelay = sf::seconds(std::max(0.7f - float(sqrt(difficulty * 0.0025f)), 0.05f));
        mEnemySpawnTime += dt;
        if(mEnemySpawnTime >= EnemySpawnDelay)
        {
            mEnemySpawnTime -= EnemySpawnDelay;
            spawnEnemy(difficulty);
        }
        const sf::Time ItemSpawnDelay = sf::seconds(3.f + sqrt(difficulty * 0.05f));
        mItemSpawner += dt;
        if(mItemSpawner >= ItemSpawnDelay)
        {
            mItemSpawner -= ItemSpawnDelay;
            spawnItem();
        }
        handleCollisions();
    }
    else
    {
        for(auto it = mButtons.begin(); it != mButtons.end(); it++)
            (*it)->update();
    }
    for(auto it = mParticles.begin(); it != mParticles.end(); it++)
    {
        (*it)->update(dt);
        if((*it)->isDead())
        {
            mParticles.erase(it);
            it--;
        }
    }
    return true;
}

void DodgeGameState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(mPlayerBorder);
    mPlayer.draw();
    for(auto it = mEnemies.begin(); it != mEnemies.end(); it++)
        (*it)->draw();
    for(auto it = mParticles.begin(); it != mParticles.end(); it++)
        (*it)->draw();
    for(auto it = mItems.begin(); it != mItems.end(); it++)
        (*it)->draw();
    if(mPlayer.isDead())
        for(auto it = mButtons.begin(); it != mButtons.end(); it++)
            (*it)->draw();
    for(int i=0; i<6; i++)
        window.draw(mTexts[i]);
}

void DodgeGameState::handleCollisions()
{
    if(!mPlayer.isDead())
    {
        if(!mPlayer.isShield())
        {
            for(auto it = mEnemies.begin(); it != mEnemies.end(); it++)
                if(mPlayer.getBoundingRect().intersects((*it)->getBoundingRect()))
                {
                    mPlayer.kill();
                    explodeParticles(sf::seconds(1), 500, sf::Color::Red, mPlayer.getPosition(), 200);
                    getContext().highscores->updateScore(Highscore::DodgeSeconds, mSurviveTime.asSeconds());
                    getContext().highscores->updateScore(Highscore::DodgeScore, mScore * floor(mSurviveTime.asSeconds()));
                }
            if(mPlayer.canExplode())
                explodeParticles(sf::seconds(0.3f), 800, sf::Color::Cyan, mPlayer.getPosition(), 100);
        }
        for(auto it = mItems.begin(); it != mItems.end(); it++)
            if(mPlayer.getBoundingRect().intersects((*it)->getBoundingRect()))
            {
                if((*it)->getType() == DodgeItem::CoinBronze)
                    mScore+=1;
                else if((*it)->getType() == DodgeItem::CoinSilver)
                    mScore+=2;
                else if((*it)->getType() == DodgeItem::CoinGold)
                    mScore+=4;
                else if((*it)->getType() == DodgeItem::Shield)
                    mPlayer.shield();
                else if((*it)->getType() == DodgeItem::Bomb)
                {
                    for(auto it = mEnemies.begin(); it != mEnemies.end(); it++)
                    {
                        explodeParticles(sf::seconds(0.3), 300, sf::Color::Cyan, (*it)->getPosition(), 30);
                        mEnemies.erase(it);
                        it--;
                    }
                }
                explodeParticles(sf::seconds(0.2), 300, sf::Color::Yellow, ((mPlayer.getPosition() + (*it)->getPosition())*0.5f), 30);
                mItems.erase(it);
                it--;
            }
    }
}

void DodgeGameState::spawnEnemy(int difficulty)
{
    char dirs[] = {'r', 'd', 'u', 'l'};
    int dir = rand()%4;
    int x = 0, y = 0;
    if(dir == 0)
    {
        x = 20;
        y = rand()%16 * 32 + 60;
    }
    else if(dir == 1)
    {
        x = rand()%16 * 32 + 60;
        y = 20;
    }
    else if(dir == 2)
    {
        x = rand()%16 * 32 + 60;
        y = 580;
    }
    else if(dir == 3)
    {
        x = 580;
        y = rand()%16 * 32 + 60;
    }
    std::unique_ptr<DodgeEnemy> enemy(new DodgeEnemy(getContext(), x, y, dirs[dir], sf::seconds(std::max(1.5f - float(sqrt(difficulty * 0.01)), 0.1f))));
    mEnemies.push_back(std::move(enemy));
}

void DodgeGameState::spawnItem()
{
    float x = rand()%488 + 60;
    float y = rand()%488 + 60;
    int itemRoll = rand()%100;
    DodgeItem::Type itemType = DodgeItem::CoinBronze;
    if(itemRoll <= 4) itemType = DodgeItem::Shield;
    else if(itemRoll <= 14) itemType = DodgeItem::Bomb;
    else if(itemRoll <= 24) itemType = DodgeItem::CoinGold;
    else if(itemRoll <= 54) itemType = DodgeItem::CoinSilver;
    std::unique_ptr<DodgeItem> item(new DodgeItem(getContext(), itemType, sf::Vector2f(x,y)));
    mItems.push_back(std::move(item));
}

void DodgeGameState::explodeParticles(sf::Time life, int maxSpeed, sf::Color color, sf::Vector2f pos, int amount)
{
    for(int i=0; i<amount; i++)
    {
        float dir = 2 * 3.14159265358979323846 * (rand()%10000 / 10000.f);
        float speed = maxSpeed * (rand()%5000 + 5000) / 10000.f;
        sf::Vector2f velocity = sf::Vector2f(speed * cos(dir), speed * sin(dir));
        std::unique_ptr<Particle> particle(new Particle(*getContext().window, life, velocity, color, pos));
        mParticles.push_back(std::move(particle));
    }
}
