#include "highscore.h"

Highscore::Highscore()
: mDodgeSeconds(0.f)
, mDodgeScore(0)
, mPianoSeconds(0.f)
, mPianoCombo(0)
, mPianoScore(0)
{
    load();
}

void Highscore::load()
{
    std::ifstream inFile("highscores.dat");
    std::string str;
    std::getline(inFile, str);
    if(str == "")
    {
        save();
        return;
    }
    decrypt(str);
    std::string buffer;
    const int Values = 5;
    std::string strValues[Values];
    for(unsigned int i=0, cnt=0; i<str.size(); i++)
    {
        if(str[i]!='$') buffer += str[i];
        else
        {
            strValues[cnt] = buffer;
            cnt++;
            buffer = "";
        }
    }
    mDodgeSeconds = fromString<float>(strValues[0]);
    mDodgeScore = fromString<int>(strValues[1]);
    mPianoSeconds = fromString<float>(strValues[2]);
    mPianoCombo = fromString<int>(strValues[3]);
    mPianoScore = fromString<int>(strValues[4]);
}

void Highscore::save()
{
    std::ofstream outFile("highscores.dat");
    std::string str = toString(mDodgeSeconds) + "$" +
                      toString(mDodgeScore) + "$" +
                      toString(mPianoSeconds) + "$" +
                      toString(mPianoCombo) + "$" +
                      toString(mPianoScore) + "$";
    encrypt(str);
    outFile << str;
    outFile.close();
}

void Highscore::encrypt(std::string& str)
{
    for(unsigned int i=0; i<str.size(); i++)
        str[i] = (str[i]^(77+i))+2*i+32;
}

void Highscore::decrypt(std::string& str)
{
    for(unsigned int i=0; i<str.size(); i++)
        str[i] = (str[i]-2*i-32)^(77+i);
}
