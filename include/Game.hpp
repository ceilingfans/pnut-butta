#ifndef PNUTBUTTA_GAME_H
#define PNUTBUTTA_GAME_H

#include <string>

#include "GameOptions.hpp"

class Game
{
public:
    explicit Game(GameOptions *p_opt);

    std::vector<std::string> getValidOptions();
    int getOptions(const std::string &p_opt);
    void addToGameString(const std::string &p_string);
    void run();
    void runComputer();
    void main();

private:
    std::string gameString;
    GameOptions gameOptions;
};

#endif /* PNUTBUTTA_GAME_H */