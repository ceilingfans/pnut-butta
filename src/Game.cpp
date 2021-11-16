#include <iostream>
#include <string>

#include "Game.hpp"
#include "Util.hpp"

Game::Game(GameOptions *p_opt)
{
  clearScreen();
  if (isValidOption(*p_opt))
  {
    std::cout << "!true" << std::endl;
    gameOptions = *p_opt;
    return;
  }

  p_opt->options.clear(); /* CLEAR OPTIONS IN CASE THERE ARE MULTIPLE */

  while (true)
  {
    if (!p_opt->options.empty())
    {
      Printer::options(p_opt->options);
    }

    std::string opt;
    Printer::prompt("Enter a character or 'stop'");
    std::cin >> opt;

    /* VALIDATION */
    if (std::find(p_opt->options.begin(), p_opt->options.end(), opt) != p_opt->options.end())
    { /* CHARACTER ALREADY ENTERED */
      Printer::error(Printer::ErrorCodes::ALREADY_ENTERED);
      continue;
    }
    if (p_opt->options.size() < 2 && opt == "stop")
    { /* 'STOP'ING BEFORE 2 OPTIONS */
      Printer::error(Printer::ErrorCodes::INSUFFICIENT_OPTIONS);
      continue;
    }
    if (opt.length() != 1 && !(opt.length() == 4 && opt == "stop"))
    { /* INVALID OPTION */
      Printer::error(Printer::ErrorCodes::INVALID_OPTION);
      continue;
    }

    /* PROCESSING */
    if (opt.length() == 4 && opt == "stop")
    {
      clearScreen();
      break;
    }

    clearScreen();
    p_opt->options.push_back(opt);
  }

  while (true)
  {
    std::string opt;
    Printer::prompt("Enter the substring length");
    std::cin >> opt;

    /* VALIDATION */
    if (!isNumber(opt))
    { /* NAN */
      Printer::error(Printer::ErrorCodes::NAN);
      continue;
    }
    int substringLength = std::stoi(opt);
    if (substringLength < 2)
    {
      Printer::error(Printer::ErrorCodes::LENGTH_SHORT);
      continue;
    }

    /* PROCESSING */
    clearScreen();
    p_opt->substringLength = substringLength;
    break;
  }

  while (true)
  {
    std::string opt;
    Printer::prompt("Enter the player count");
    std::cin >> opt;

    /* VALIDATION */
    if (!isNumber(opt))
    {
      Printer::error(Printer::ErrorCodes::NAN);
      continue;
    }
    int playerCount = std::stoi(opt);
    if (playerCount < 1)
    {
      Printer::error(Printer::ErrorCodes::INSUFFICIENT_PLAYERS);
      continue;
    }

    /* PROCESSING */
    clearScreen();
    p_opt->playerCount = playerCount;
    break;
  }

  while (true)
  {
    std::string opt;
    Printer::prompt("DO you want assistance? ('y'/'n')");
    std::cin >> opt;

    /* VALIDATION */
    if (opt == "y")
    {
      clearScreen();
      p_opt->isAssist = true;
      break;
    }
    else if (opt == "n")
    {
      clearScreen();
      p_opt->isAssist = false;
      break;
    }
    else
    {
      Printer::error(Printer::ErrorCodes::INVALID_OPTION);
      continue;
    }
  }

  gameOptions = *p_opt;
}
