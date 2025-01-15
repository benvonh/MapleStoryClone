#include "game.hpp"
#include "resources.h"

int main() {
  SearchAndSetResourceDir("resources");

  Game<1366, 768> game("MapleStory Clone");

  game.Loop();

  return EXIT_SUCCESS;
}