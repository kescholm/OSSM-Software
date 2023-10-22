#ifndef OSSM_SOFTWARE_MENU_H
#define OSSM_SOFTWARE_MENU_H

#include <WString.h>

#include "constants/UserConfig.h"

enum MenuOption { Play, StrokeEngine, DTTSync, Help, Restart, NUM_OPTIONS };

static String menuStrings[MenuOption::NUM_OPTIONS] = {
    UserConfig::language.SimplePenetration, UserConfig::language.StrokeEngine,
    UserConfig::language.DeepThroatTrainerSync, UserConfig::language.GetHelp,
    UserConfig::language.Restart};

#endif  // OSSM_SOFTWARE_MENU_H
