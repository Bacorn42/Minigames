#include "pianoGameState.h"

PianoGameState::PianoGameState(StateStack& stack, Context context)
: State(stack, context)
, mBackground(context.textures->get(Textures::PianoBackground))
, mFretSpawnTime(sf::Time::Zero)
, mScore(0)
, mCombo(0)
, mLives(10)
, mMaxCombo(0)
, mFretCounter(0)
, mDead(false)
{
    for(int i=0; i<10; i++)
    {
        mTexts[i].setFont(context.fonts->get(Fonts::Main));
        mTexts[i].setCharacterSize(20);
        mTexts[i].setColor(sf::Color::White);
        centerOrigin(mTexts[i]);
        mTexts[i].setPosition(430,40*i+(i/2) * 40);
    }
    mTexts[0].setString("Seconds survived:");
    mTexts[1].setString("0");
    mTexts[2].setString("Score:");
    mTexts[3].setString("0");
    mTexts[4].setString("Combo:");
    mTexts[5].setString("0 (0)");
    mTexts[6].setString("Total score:");
    mTexts[7].setString("0");
    mTexts[8].setString("Lives:");
    mTexts[9].setString("0");

    const std::string strs[] = {"Restart", "Exit"};
    std::function<void()> funcs[] = {
        [this](){ requestStackPop(); requestStackPush(States::PianoGame); },
        [this](){ requestStackPop(); requestStackPush(States::GameMenu); }
    };
    for(int i=0; i<2; i++)
    {
        std::unique_ptr<Button> button(new Button(context, strs[i], funcs[i], sf::Vector2f(680, 500 + 60*i)));
        mButtons.push_back(std::move(button));
    }
}

bool PianoGameState::handleEvent(sf::Event& event)
{
    const sf::Keyboard::Key keys[] = {sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D,
                                sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L};
    if(event.type == sf::Event::KeyPressed)
        if(mLives > 0)
        {
            if(event.key.code == sf::Keyboard::P)
                requestStackPush(States::Pause);
            for(int i=0; i<6; i++)
                if(event.key.code == keys[i])
                    handlePress(i);
        }
    if(mLives <= 0)
        for(auto it = mButtons.begin(); it != mButtons.end(); it++)
            (*it)->handleEvent(event);
    return true;
}

bool PianoGameState::update(sf::Time dt)
{
    mTexts[1].setString(toString(mSurviveTime.asSeconds()));
    mTexts[3].setString(toString(mScore));
    mTexts[5].setString(toString(mCombo) + " (" + toString(mMaxCombo) + ")");
    mTexts[7].setString(toString(int(mScore * floor(mSurviveTime.asSeconds()))));
    mTexts[9].setString(toString(mLives));
    if(mLives > 0)
    {
        mFretSpawnTime += dt;
        mSurviveTime += dt;
        const sf::Color colors[] = { sf::Color::Red, sf::Color(255,128,0), sf::Color::Yellow,
                               sf::Color::Green, sf::Color::Blue, sf::Color(192,0,192) };
        int difficulty = floor(mSurviveTime.asSeconds());
        if(mFretSpawnTime.asSeconds() >= std::max(1.f - float(sqrt(difficulty * 0.003f)), 0.05f))
        {
            mFretSpawnTime -= sf::seconds(std::max(1.f - float(sqrt(difficulty * 0.003f)), 0.05f));
            int column = rand()%6;
            std::unique_ptr<Fret> fret(new Fret(getContext(), colors[column], sf::Vector2f(16 + 64 * column, -32), 200 + std::min(difficulty * 2, 300), column, fretBonus()));
            mFrets.push_back(std::move(fret));
            if(difficulty > 30)
                if(rand()%(12 - std::min((difficulty/15), 11))==0)
                {
                    int column2 = column;
                    while(column2 == column)
                        column2 = rand()%6;
                    std::unique_ptr<Fret> fret2(new Fret(getContext(), colors[column2], sf::Vector2f(16 + 64 * column2, -32), 200 + std::min(difficulty * 2, 300), column2, fretBonus()));
                    mFrets.push_back(std::move(fret2));
                    if(difficulty > 90)
                        if(rand()%(10 - std::min((difficulty/15), 8))==0)
                        {
                            int column3 = column2;
                            while(column3 == column2 || column3 == column)
                                column3 = rand()%6;
                            std::unique_ptr<Fret> fret3(new Fret(getContext(), colors[column3], sf::Vector2f(16 + 64 * column3, -32), 200 + std::min(difficulty * 2, 300), column3, fretBonus()));
                            mFrets.push_back(std::move(fret3));
                        }
                }
        }
        for(auto it = mFrets.begin(); it != mFrets.end(); it++)
        {
            (*it)->update(dt);
            if((*it)->isDead())
            {
                explodeParticles(sf::seconds(0.5), 400, sf::Color(96,96,96), (*it)->getPosition(), 60);
                mFrets.erase(it);
                it--;
                mLives--;
                mCombo = 0;
            }
        }
    }
    else
    {
        if(!mDead)
        {
            mDead = true;
            getContext().highscores->updateScore(Highscore::PianoSeconds, mSurviveTime.asSeconds());
            getContext().highscores->updateScore(Highscore::PianoCombo, mMaxCombo);
            getContext().highscores->updateScore(Highscore::PianoScore, mScore * floor(mSurviveTime.asSeconds()));
        }
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

void PianoGameState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackground);
    for(auto it = mFrets.begin(); it != mFrets.end(); it++)
        (*it)->draw();
    for(auto it = mParticles.begin(); it != mParticles.end(); it++)
        (*it)->draw();
    for(int i=0; i<10; i++)
        window.draw(mTexts[i]);
    if(mLives <= 0)
        for(auto it = mButtons.begin(); it != mButtons.end(); it++)
            (*it)->draw();
}

void PianoGameState::explodeParticles(sf::Time life, int maxSpeed, sf::Color color, sf::Vector2f pos, int amount)
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

void PianoGameState::handlePress(int column)
{
    bool hit = false;
    for(auto it = mFrets.begin(); it != mFrets.end(); it++)
        if((*it)->getColumn() == column)
            if((*it)->getPosition().y >= 468 && (*it)->getPosition().y <= 580)
            {
                hit = true;
                explodeParticles(sf::seconds(0.5), 400, (*it)->getColor(), (*it)->getPosition(), 60);
                if((*it)->getBonus() == Fret::Bonus::Heart)
                {
                    mLives++;
                    explodeParticles(sf::seconds(0.6), 600, (*it)->getColor(), (*it)->getPosition(), 100);
                }
                mFrets.erase(it);
                it--;
            }
    if(hit)
    {
        mCombo++;
        mScore+=mCombo;
        if(mCombo > mMaxCombo)
            mMaxCombo = mCombo;
    }
    else
    {
        mLives--;
        mCombo = 0;
    }
}

Fret::Bonus PianoGameState::fretBonus()
{
    Fret::Bonus bonus = Fret::Bonus::None;
    mFretCounter++;
    if(mFretCounter % 50 == 0)
        bonus = Fret::Bonus::Heart;
    return bonus;
}
