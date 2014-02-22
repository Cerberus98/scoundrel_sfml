#include "clock.h"

namespace Scoundrel {
  U64 Clock::get_elapsed_time() {
    return _clock.getElapsedTime().asMicroseconds();
  }

  void Clock::restart() {
    _clock.restart();
  }

  void Clock::wait(U64 time) {
    sf::Time t = sf::microseconds(time);
    sf::sleep(t);
  }
}






