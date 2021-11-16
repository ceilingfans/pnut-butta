#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "Util.hpp"
#include "Colours.hpp"

namespace Printer
{
  void think()
  {
    std::cout << "skippy: thinking..." << std::endl;
  }

  void error(ErrorCodes p_code)
  {
    std::cout << "pnut-butta: " << BOLD(FRED("error: "));
    switch (p_code)
    {
      case ErrorCodes::INTERNAL:
        std::cout << "internal error, please contact the maintainer" << std::endl;
        break;

      case ErrorCodes::ALREADY_ENTERED:
        std::cout << "character already entered" << std::endl;
        break;

      case ErrorCodes::INSUFFICIENT_OPTIONS:
        std::cout << "need at least two options before stopping" << std::endl;
        break;

      case ErrorCodes::INSUFFICIENT_PLAYERS:
        std::cout << "need at least 1 player" << std::endl;
        break;

      case ErrorCodes::INVALID_OPTION:
        std::cout << "invalid option" << std::endl;
        break;

      case ErrorCodes::NAN:
        std::cout << "not a number" << std::endl;
        break;

      case ErrorCodes::LENGTH_SHORT:
        std::cout << "substring length has to be at least 2" << std::endl;
        break;
    }
  }

  void loss(const std::string &p_loser, LossCodes p_code)
  {
    std::cout << "pnut-butta: " << BOLD(FRED("loser ")) << p_loser << std::endl;

    switch (p_code)
    {
      case LossCodes::INVALID:
        error(ErrorCodes::INTERNAL);
        break;

      case LossCodes::OPTION:
        std::cout << ", no valid moves left" << std::endl;
        break;

      case LossCodes::CHOICE:
        std::cout << ", there is already a match substring" << std::endl;
        break;
    }
  }

  void win(const std::string &p_winner)
  {
    std::cout << "pnut-butta: " << BOLD(FGRN("winner: ")) << p_winner << std::endl;
  }

  void prompt(const std::string &p_prompt)
  {
    std::cout << "pnut-butta: " << KMAG << p_prompt << RST << std::endl;
  }

  void options(const std::vector<std::string> &p_options)
  {
    std::cout << "pnut-butta: " << BOLD(FGRN("options: ")) << joinString(p_options, " ") << std::endl;
  }
} /* Printer */

void clearScreen()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif /* _WIN32 */
}

std::string joinString(const std::vector<std::string> &p_strings, const std::string& p_delimiter)
{
  std::string result;

  for (size_t i = 0; i < p_strings.size(); ++i)
  {
    if (i == p_strings.size() - 1)
    {
      result += p_strings[i];
      continue;
    }

    result += (p_strings[i] + p_delimiter);
  }

  return result;
}

bool contains(const std::string &p_string, const std::string &p_search)
{
  return p_string.find(p_search) != std::string::npos;
}

bool isNumber(const std::string &p_string)
{
  std::string::const_iterator it = p_string.begin();
  while(it != p_string.end() && std::isdigit(*it)) ++it;
  return !p_string.empty() && it == p_string.end();
}

std::vector<std::string> splitText(std::string p_string, const std::string &p_delimiter)
{
  std::vector<std::string> result;
  size_t pos = 0;
  while ((pos = p_string.find(p_delimiter)) != std::string::npos)
  {
    result.push_back(p_string.substr(0, pos));
    p_string.erase(0, pos + p_delimiter.length());
  }

  return result;
}