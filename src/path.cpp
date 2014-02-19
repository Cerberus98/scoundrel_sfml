#include "path.h"

namespace Scoundrel {
  Path::Path() {

  }
  
  Path::Path(char* path) {
    set_path(path);
  }

  void Path::set_path(char* path) {
    _path = path;
  }

  bool Path::is_path_set() {
    return _path != NULL;
  }

  std::ostream& operator<<(std::ostream& os, const Path& path) {
    os << path._path;
    return os;
  }

  Path::~Path() {
    if (_path) {
      // The man page say memory is allocated for this but that appears to be horseshit
      //free(_path);
    }
  }
}
