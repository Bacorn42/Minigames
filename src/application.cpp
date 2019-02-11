#include "application.h"

Application::Application()
: mWindow(sf::VideoMode(800,600,32), "Game")
, mTextures()
, mFonts()
, mHighscores()
, mStack(State::Context(mWindow, mTextures, mFonts, mHighscores))
{
    srand(time(NULL));
    mTextures.load(Textures::MenuButtons, "gfx/menuButtons.png");
    mTextures.load(Textures::PlayerSheet, "gfx/player.png");
    mTextures.load(Textures::DodgeGameSheet, "gfx/dodgeGame.png");
    mTextures.load(Textures::PianoBackground, "gfx/pianoBackground.png");
    mTextures.load(Textures::PianoGameSheet, "gfx/pianoGame.png");
    mFonts.load(Fonts::Main, "luckiest-guy.ttf");
    registerStates();
    mStack.pushState(States::Menu);
    mWindow.setFramerateLimit(60);
}

void Application::run()
{
    sf::Clock clock;
    const sf::Time FrameTime = sf::seconds(1.f/60);
    sf::Time elapsedTime = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        processEvents();
        elapsedTime += clock.restart();
        while(elapsedTime >= FrameTime)
        {
            elapsedTime -= FrameTime;
            update(FrameTime);

            if(mStack.isEmpty())
                mWindow.close();
        }

        render();
    }
}

void Application::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();

        mStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    mStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    mStack.draw();
    mWindow.display();
}

void Application::registerStates()
{
    mStack.registerState<MenuState>(States::Menu);
    mStack.registerState<GameMenuState>(States::GameMenu);
    mStack.registerState<DodgeGameState>(States::DodgeGame);
    mStack.registerState<PauseState>(States::Pause);
    mStack.registerState<PianoGameState>(States::PianoGame);
    mStack.registerState<HighscoreState>(States::Highscores);
}
