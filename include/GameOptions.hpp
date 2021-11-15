#ifndef PNUTBUTTA_GAMEOPTIONS_H
#define PNUTBUTTA_GAMEOPTIONS_H

#include <vector>
#include <string>

struct GameOptions
{
    int playerCount;
    int substringLength;
    bool isAssist;
    std::vector<std::string> options;
};

#endif /* PNUTBUTTA_GAMEOPTIONS_H */