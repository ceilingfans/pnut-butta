#include "GameOptions.hpp"

bool isValidOption(const GameOptions& opt)
{
  return opt.playerCount > 0 && opt.substringLength >= 2 && !opt.options.empty() && opt.options.size() >= 2;
}