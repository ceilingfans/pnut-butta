#ifndef PNUTBUTTA_UTIL_H
#define PNUTBUTTA_UTIL_H

#include <string>
#include <vector>

namespace Printer
{
    enum ErrorCodes
    {
      INTERNAL = 0,
      ALREADY_ENTERED,
      INSUFFICIENT_OPTIONS,
      INSUFFICIENT_PLAYERS,
      INVALID_OPTION,
      NAN,
      LENGTH_SHORT,
    };

    enum LossCodes
    {
      INVALID = 0,
      OPTION,
      CHOICE,
    };

    void think();
    void error(ErrorCodes p_code);
    void loss(const std::string &p_loser, LossCodes p_code);
    void win(const std::string &p_winner);
    void prompt(const std::string &p_prompt);
    void options(const std::vector<std::string> &p_options);
} /* Printer */

void clearScreen();
std::string joinString(const std::vector<std::string> &p_strings, const std::string& p_delimiter);
bool contains(const std::string &p_string, const std::string &p_search);
bool isNumber(const std::string &p_string);
std::vector<std::string> splitText(std::string p_string, const std::string &p_delimiter);

#endif /* PNUTBUTTA_UTIL_H */