#include "os.h"

namespace Scoundrel {
  #ifdef __APPLE__
  Path get_absolute_path(std::string file) {
    Path path;
    return path;
  }

  Path get_cwd() {
    if (!_procpath.is_path_set()) {
      _procpath.set_path(getwd(NULL));
    }
    return _procpath;
  }
  #endif
}
