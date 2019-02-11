#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED

#include "utilities.h"

#include <fstream>
#include <string>

class Highscore
{
    public:
        enum ScoreType
        {
            DodgeSeconds,
            DodgeScore,
            PianoSeconds,
            PianoCombo,
            PianoScore
        };

        Highscore();
        template<typename T>
        void updateScore(ScoreType type, T value);
        template<typename T>
        T getScore(ScoreType type);
        void encrypt(std::string& str);
        void decrypt(std::string& str);

    private:
        void load();
        void save();
        float mDodgeSeconds;
        int mDodgeScore;
        float mPianoSeconds;
        int mPianoCombo;
        int mPianoScore;
};

template<typename T>
void Highscore::updateScore(Highscore::ScoreType type, T value)
{
    if(type == Highscore::DodgeSeconds)
    {
        if(value > mDodgeSeconds)
            mDodgeSeconds = value;
    }
    else if(type == Highscore::DodgeScore)
    {
        if(value > mDodgeScore)
            mDodgeScore = value;
    }
    else if(type == Highscore::PianoSeconds)
    {
        if(value > mPianoSeconds)
            mPianoSeconds = value;
    }
    else if(type == Highscore::PianoCombo)
    {
        if(value > mPianoCombo)
            mPianoCombo = value;
    }
    else if(type == Highscore::PianoScore)
    {
        if(value > mPianoScore)
            mPianoScore = value;
    }
    save();
}

template<typename T>
T Highscore::getScore(Highscore::ScoreType type)
{
    if(type == Highscore::DodgeSeconds)
        return mDodgeSeconds;
    else if(type == Highscore::DodgeScore)
        return mDodgeScore;
    else if(type == Highscore::PianoSeconds)
        return mPianoSeconds;
    else if(type == Highscore::PianoCombo)
        return mPianoCombo;
    else if(type == Highscore::PianoScore)
        return mPianoScore;
    return -1;
}

#endif // HIGHSCORE_H_INCLUDED
