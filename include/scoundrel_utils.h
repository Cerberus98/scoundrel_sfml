#include <string>

#ifndef SCOUNDREL_UTILS
#define SCOUNDREL_UTILS

namespace Scoundrel {
  struct Point {
    float x, y;
    Point() {}
    Point(float x, float y): x(x), y(y) {}
  };

  typedef Point Size;

  struct KeyState {
    bool left_pressed;
    bool right_pressed;
    bool up_pressed;
    bool down_pressed;
    bool space_pressed;

    bool left_was_pressed;
    bool right_was_pressed;
    bool up_was_pressed;
    bool down_was_pressed;
    bool space_was_pressed;
  };

  std::string full_path(std::string file_path, std::string proc_path)
  {
    std::stringstream final_path;
    final_path << proc_path << "/" << file_path;
    return final_path.str();
  }
}

#endif

