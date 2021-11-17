#include <cstdio>
#include <string>
#include <vector>

#include "Game.hpp"
#include "Util.hpp"

#define FLAG_IMPLEMENTATION
#include "flag.h"

#define PNUTBUTTA_VERSION "pnut-butta1.2 17 Nov 2021"

void usage(FILE *stream)
{
  fprintf(stream, "Usage: pnut-butta [-help] [-version] [options]\n");
  fprintf(stream, "Options: \n");
  flag_print_options(stream);
}

int main(int argc, char** argv)
{
  bool *help = flag_bool("help", false, "Prints the help message");
  bool *version = flag_bool("version", false, "Prints the version");
  bool *isAssist = flag_bool("assist", false, "Sets whether assistance from the game is provided\n"
                                              "\tE.g. '-assist'");
  char* *playerCount = flag_str("players", "0", "Sets the amount of players\n"
                                                "\tE.g. '-players 1' (play against the computer)\n"
                                                "\t     '-players 2' (more than 1 for multiplayer)");
  char* *substringLength = flag_str("substring", "0", "Sets the length of substring\n"
                                                      "\tE.g. '-substring 4'");
  char* *options = flag_str("options", "", "Sets the options of the game (seperated by commas)\n"
                                           "\tE.g. '-options 0,1,2'");

  bool b_parsed = flag_parse(argc, argv);
  if (!b_parsed)
  {
    flag_print_error(stdout);
    usage(stdout);
    return EXIT_FAILURE;
  }

  if (*help)
  {
    usage(stdout);
    return EXIT_SUCCESS;
  }
  if (*version)
  {
    fprintf(stdout, PNUTBUTTA_VERSION);
    fprintf(stdout, "\n");
    return EXIT_SUCCESS;
  }

  GameOptions opt;

  if (argc != 1)
  {
    std::string pc(*playerCount);
    std::string sl(*substringLength);
    std::string op(*options);

    if (!isNumber(pc))
    {
      Printer::error(Printer::ErrorCodes::NOT_A_NUMBER);
      usage(stdout);
      return EXIT_FAILURE;
    }
    else
    {
      opt.playerCount = std::stoi(pc);
    }

    if (!isNumber(sl))
    {
      Printer::error(Printer::ErrorCodes::NOT_A_NUMBER);
      usage(stdout);
      return EXIT_FAILURE;
    }
    else
    {
      opt.substringLength = std::stoi(sl);
    }

    if (op.empty())
    {
      Printer::error(Printer::ErrorCodes::INSUFFICIENT_OPTIONS);
      usage(stdout);
      return EXIT_FAILURE;
    }
    else
    {
      bool isValid = true;
      for (char i : op)
      {
        isValid = isdigit(i) || i == ',';
      }

      if (!isValid)
      {
        Printer::error(Printer::ErrorCodes::INVALID_OPTION);
        usage(stdout);
        return EXIT_FAILURE;
      }
      else
      {
        opt.options = splitText(op, ",");
      }
    }
  }

  opt.isAssist = *isAssist;

  Game game(&opt);
  game.main();

  return EXIT_SUCCESS;
}