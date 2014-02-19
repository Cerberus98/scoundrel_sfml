#include <iostream>

#include <string>

#ifndef SCOUNDREL_PATH
#define SCOUNDREL_PATH

namespace Scoundrel {
  struct Path {
    Path();
    Path(std::string path);
    Path(char* path);
    ~Path();
    friend std::ostream& operator<<(std::ostream& os, const Path& path);

    void set_path(char* path);
    bool is_path_set();
    char* _path;

  };
}

#endif
