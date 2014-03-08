#include "camera.h"

namespace Scoundrel {
  Camera::Camera() {
    _camera_upper_left.x = 0;
    _camera_upper_left.y = 0;
    _camera_lower_right.x = 0;
    _camera_lower_right.y = 0;
  }

  Camera::Camera(U32 window_width, U32 window_height, float snap_x, float snap_y) {
    _window_width = window_width; 
    _window_height = window_height; 
    _snap_x = snap_x; 
    _snap_y = snap_y; 
    calculate_snap();
  }

  Rectangle Camera::get_view_rect() {
    return Rectangle(_camera_upper_left.x,
                     _camera_upper_left.y,
                     _camera_upper_left.x + _window_width,
                     _camera_upper_left.y + _window_height);
  }

  void Camera::set_window_size(U32 width, U32 height) {
    _window_width = width; 
    _window_height = height; 
  }

  void Camera::set_window_snap(float x, float y) {
    _snap_x = x; 
    _snap_y = y; 
  }

  void Camera::calculate_snap() {
    _snap_left = U32(float(_window_width) * _snap_x);
    _snap_right = U32(float(_window_width) * (1.0f - _snap_x));
    _snap_top = U32(float(_window_height) * _snap_y);
    _snap_bottom = U32(float(_window_height) * (1.0f - _snap_y));
  }

  void Camera::set_absolute(I32 x, I32 y) {
    _camera_upper_left.x = x;
    _camera_upper_left.y = y;
  }

  void Camera::move(I32 delta_x, I32 delta_y) {
    _camera_upper_left.x += delta_x;
    _camera_upper_left.y += delta_y;
    _camera_lower_right.x += delta_x;
    _camera_lower_right.y += delta_y;
  }

  Point Camera::position() {
    return _camera_upper_left;
  }

  Camera::CAMERA_SNAP Camera::point_snap_horizontal(Point point) {
    Point absolute_coords;
    absolute_coords.x = point.x - _camera_upper_left.x;
    absolute_coords.y = point.y - _camera_upper_left.y;

    if (absolute_coords.x <= _snap_left) {
      return SNAP_LEFT;
    } else if (absolute_coords.x >= _snap_right) {
      return SNAP_RIGHT;
    }
    return SNAP_NONE;
  }

  Camera::CAMERA_SNAP Camera::point_snap_vertical(Point point) {
    Point absolute_coords;
    absolute_coords.x = point.x - _camera_upper_left.x;
    absolute_coords.y = point.y - _camera_upper_left.y;

    if (absolute_coords.y <= _snap_top) {
      return SNAP_TOP;
    } else if (absolute_coords.y >= _snap_bottom) {
      return SNAP_BOTTOM;
    }
    return SNAP_NONE;
  }
}


