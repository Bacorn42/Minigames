#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include "resourceHolder.h"
#include "resourceIdentifiers.h"
#include "statestack.h"
#include "stateIdentifiers.h"
#include "highscore.h"
#include "menuState.h"
#include "gameMenuState.h"
#include "dodgeGameState.h"
#include "pauseState.h"
#include "pianoGameState.h"
#include "highscoreState.h"

#include <SFML/Graphics.hpp>

class Application
{
    public:
        Application();
        void run();
        void processEvents();
        void update(sf::Time dt);
        void render();
        void registerStates();

    private:
        sf::RenderWindow mWindow;
        TextureHolder mTextures;
        FontHolder mFonts;
        Highscore mHighscores;
        StateStack mStack;
};

#endif // APPLICATION_H_INCLUDED
