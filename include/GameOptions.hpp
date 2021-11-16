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

bool isValidOption(const GameOptions &opt)
{
  return opt.playerCount != 0 && opt.substringLength != 0 && opt.options.empty();
}

#endif /* PNUTBUTTA_GAMEOPTIONS_H */