#ifndef SCOUNDREL_CAMERA
#define SCOUNDREL_CAMERA

#include "rect.h"
#include "scoundrel_utils.h"
#include "types.h"

namespace Scoundrel {
  class Camera {
  public:
    Camera();
    Camera(U32 window_width, U32 window_height, float snap_x, float snap_y);
    void move(I32 delta_x, I32 delta_y);
    void calculate_snap();
    Point position();
    enum CAMERA_SNAP {
      SNAP_LEFT, SNAP_RIGHT, SNAP_TOP, SNAP_BOTTOM, SNAP_NONE
    };
    CAMERA_SNAP point_snap_horizontal(Point point);
    CAMERA_SNAP point_snap_vertical(Point point);
    void set_absolute(I32 x, I32 y);
    void set_window_size(U32 width, U32 height);
    void set_window_snap(float x, float y);
    Rectangle get_view_rect();

  private:
    Point _camera_upper_left;
    Point _camera_lower_right;
    U32 _snap_left, _snap_right, _snap_top, _snap_bottom;
    U32 _window_width, _window_height;
    float _snap_x, _snap_y;
  };
}

#endif
