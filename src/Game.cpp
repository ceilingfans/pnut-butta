#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

#include "Game.hpp"
#include "Util.hpp"
#include "Colours.hpp"

Game::Game(GameOptions *p_opt)
{
  clearScreen();
  if (isValidOption(*p_opt))
  {
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
    std::getline(std::cin, opt);

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
    std::getline(std::cin, opt);

    /* VALIDATION */
    if (!isNumber(opt))
    { /* NOT_A_NUMBER */
      Printer::error(Printer::ErrorCodes::NOT_A_NUMBER);
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
    std::getline(std::cin, opt);

    /* VALIDATION */
    if (!isNumber(opt))
    {
      Printer::error(Printer::ErrorCodes::NOT_A_NUMBER);
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
    std::getline(std::cin, opt);

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

std::vector<std::string> Game::getValidOptions()
{
  if (static_cast<int>(gameString.length()) < gameOptions.substringLength)
  {
    return gameOptions.options;
  }

  std::vector<std::string> validOptions;
  std::string prefix = gameString.substr(gameString.length() - (gameOptions.substringLength-1));

  for (const std::string &s : gameOptions.options)
  {
    if (!contains(gameString, prefix+s))
    {
      validOptions.push_back(s);
    }
  }

  return validOptions;
}

int Game::getOptions(const std::string &p_opt)
{
  int result = 0;
  std::string s = gameString + p_opt;

  for (const std::string &str : gameOptions.options)
  {
    if (!contains(gameString, s+str))
    {
      ++result;
    }
  }

  return result;
}

void Game::addToGameString(const std::string &p_string)
{
  gameString += p_string;
}
void Game::run()
{
  while (true)
  {
    for (int i = 1; i < gameOptions.playerCount + 1; ++i)
    {
      clearScreen();
      std::vector<std::string> validOptions = getValidOptions();

      if (validOptions.empty() && gameOptions.playerCount == 2)
      {
        Printer::loss(std::to_string(i), Printer::LossCodes::OPTION);
        return;
      }
      else if (validOptions.empty() && gameOptions.playerCount > 2)
      {
        Printer::win(std::to_string(i-1 || gameOptions.playerCount));
        return;
      }

      std::string opt;
      std::cout <<
              (
                gameString.empty() ?
                BOLD(FGRN("Nothing Yet")) :
                "\x1B[1m\x1B[32m" + gameString + "\x1B[0m"
              ) << " | Player \x1B[4m" << i << RST << "'s turn" << std::endl;


      if (gameOptions.isAssist)
      {
        Printer::options(validOptions);
      }
      do
      {
        std::getline(std::cin, opt);

        if (std::find(validOptions.begin(), validOptions.end(), opt) == validOptions.end())
        {
          if (gameOptions.isAssist)
          {
            Printer::error(Printer::ErrorCodes::INVALID_OPTION);
            opt.clear();
          }
          else
          {
            if (std::find(gameOptions.options.begin(), gameOptions.options.end(), opt) == gameOptions.options.end())
            {

              Printer::error(Printer::ErrorCodes::INVALID_OPTION);
              continue;
            }

            clearScreen();
            Printer::loss(std::to_string(i), Printer::LossCodes::CHOICE);
            std::string prefix = gameString.substr(gameString.length() - (gameOptions.substringLength - 1)) + opt;
            size_t pos = gameString.find(prefix);

            std::cout << gameString << std::endl;
            Printer::arrow(pos, gameOptions.substringLength, prefix);
            return;
          }
        }
      } while (opt.empty() || std::find(validOptions.begin(), validOptions.end(), opt) == validOptions.end());

      addToGameString(opt);
    }
  }
}

void Game::runComputer()
{
  bool isFirst;

  while (true)
  {
    std::string opt;
    Printer::prompt("Do you want to go first? ('y'/'n')");
    std::getline(std::cin, opt);

    if (opt == "y")
    {
      isFirst = true;
    }
    else if (opt == "n")
    {
      isFirst = false;
    }
    else 
    {
      Printer::error(Printer::ErrorCodes::INVALID_OPTION);
      continue;
    }
    break;
  }
  
  while (true)
  {
    for (int i = 1; i < 3; ++i)
    {
      if ((i == 1 && isFirst) || (i == 2 && !isFirst)) 
      {
        clearScreen();

        std::vector<std::string> validOptions = getValidOptions();
        if (validOptions.empty()) 
        {
          Printer::loss(std::to_string(i), Printer::LossCodes::OPTION);
          return;
        }

        std::string opt;
        std::cout <<
                (
                  gameString.empty() ?
                  BOLD(FGRN("Nothing Yet")) :
                  "\x1B[1m\x1B[32m" + gameString.substr(0, gameString.length()-1) + RST + "\x1B[1m" + KRED + gameString.substr(gameString.length()-1) + RST
                ) << " | Player \x1B[4m" << i << RST << "'s turn" << std::endl;
        
        if (gameOptions.isAssist)
        {
          Printer::options(gameOptions.options);
        }
        do
        {
          std::getline(std::cin, opt);
          
          if (std::find(validOptions.begin(), validOptions.end(), opt) == validOptions.end())
          {
            if (gameOptions.isAssist)
            {
              Printer::error(Printer::ErrorCodes::INVALID_OPTION);
              opt.clear();
            }
            else
            {
              if (std::find(gameOptions.options.begin(), gameOptions.options.end(), opt) == gameOptions.options.end())
              {
                Printer::error(Printer::ErrorCodes::INVALID_OPTION);
                continue;
              }
              
              clearScreen();
              Printer::loss(std::to_string(i), Printer::LossCodes::CHOICE);
              std::string prefix = gameString.substr(gameString.length() - (gameOptions.substringLength - 1)) + opt;
              size_t pos = gameString.find(prefix);
              
              std::cout << gameString << std::endl;
              Printer::arrow(pos, gameOptions.substringLength, prefix);
              return;
            }
          }
        } while (opt.empty() || !(std::find(validOptions.begin(), validOptions.end(), opt) != validOptions.end()));
        
        addToGameString(opt);
      }
      else
      {
        clearScreen();
                std::cout <<
                (
                  gameString.empty() ?
                 BOLD(FGRN("Nothing Yet")) :
                 "\x1B[1m\x1B[32m" + gameString + "\x1B[0m"
                ) << " | Player \x1B[4m" << i << RST << "'s turn" << std::endl;

        std::vector<std::string> validOptions = getValidOptions();
        if (validOptions.empty())
        {
          Printer::win(std::to_string(isFirst ? 1 : 2));
          return;
        }

        size_t bestOptionIndex = 0;
        int lowestOptionCount;

        for (size_t j = 0; j < validOptions.size(); ++j)
        {
          int options = getOptions(validOptions[j]);
          
          if (j == 0)
          {
            lowestOptionCount = options;
            continue;
          }
          
          if (options < lowestOptionCount)
          {
            bestOptionIndex = j;
            lowestOptionCount = options;
          }
        }

        Printer::think();

        std::mt19937_64 eng { std::random_device{}() };
        std::uniform_int_distribution<> dist { 750, 1250 };
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(eng)));

        addToGameString(validOptions[bestOptionIndex]);
      }
    }
  }
}

void Game::main()
{
  if (gameOptions.playerCount < 2)
  {
    runComputer();
  }
  else
  {
    run();
  }
}

// 101012002020