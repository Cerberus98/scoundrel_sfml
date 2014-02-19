#include <iostream>

#include <string>
#include <unistd.h>

#include "path.h"

#ifndef SCOUNDREL_OS
#define SCOUNDREL_OS

namespace Scoundrel {
  // NOTE(mdietz): The implementations of these are likely separated by a macro controlled by the Makefile for each
  // platform
  Path get_relative_path(std::string);
  Path get_absolute_path(std::string);
  Path get_cwd();

  // Caches the cwd for the duration of the process
  Path _procpath;
}

#endif
