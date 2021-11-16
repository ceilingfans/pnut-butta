#include "GameOptions.hpp"

bool isValidOption(const GameOptions& opt)
{
  return opt.playerCount != 0 && opt.substringLength != 0 && !opt.options.empty();
}