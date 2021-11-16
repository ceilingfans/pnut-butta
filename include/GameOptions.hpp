#ifndef PNUTBUTTA_GAMEOPTIONS_H
#define PNUTBUTTA_GAMEOPTIONS_H

#include <vector>
#include <string>

struct GameOptions
{
    int playerCount = 0;
    int substringLength = 0;
    bool isAssist = false;
    std::vector<std::string> options {};
};

bool isValidOption(const GameOptions &opt);

#endif /* PNUTBUTTA_GAMEOPTIONS_H */