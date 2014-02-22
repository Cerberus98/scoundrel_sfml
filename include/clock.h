#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "types.h"


#ifndef SCOUNDREL_CLOCK
#define SCOUNDREL_CLOCK

namespace Scoundrel {
  class Clock {
    //Exists to provide an abstraction layer between us and SFML,
    //theoretically making it easier to move away later if need be
  public:
    U64 get_elapsed_time();
    void restart();
    void wait(U64 milliseconds);

  private:
    sf::Clock _clock;
  };
}

#endif
