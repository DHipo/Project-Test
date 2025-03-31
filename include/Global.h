#ifndef GLOBAL_H
#define GLOBAL_H

class Block;
class Map;
class Player;

#include "Utils.h"
#include ".\Player\Player.h"

#define WINDOW_SIZE_W 1280
#define WINDOW_SIZE_H 720
#define LEFT_CLICK_MOUSE 1
#define RIGT_CLICK_MOUSE 1

#define URL_FONT "./assets/fonts/HackRegularNerdFontCompleteMono.ttf"
#define URL_ASSETS "./assets/"

#define FONT_SIZE 16

static Player*  g_player= nullptr;

#endif