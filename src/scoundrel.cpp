#include "scoundrel.h"

namespace Scoundrel {
  //I really hate all these globals. With more time I'd actually write some decent code
  GameMap* game_map;
  sf::Sprite* sprites;
  sf::Texture* textures;
  sf::Texture tile_sheet;

  Player* player;
  KeyState key_state;
  Camera camera;
  sf::Font game_font;
  sf::Clock fps_clock, game_clock;
  sf::SoundBuffer* sound_buffers;
  sf::Sound* sounds;
  std::map<int, Animation> animation_map;

  game_modes game_mode;
  int game_start_level, current_level, total_levels;
  std::list<Entity*> game_entities;

  float framerate = 0.f;
  bool show_fps = false;
  TileHelper tile_helper(TILE_WIDTH, TILE_HEIGHT);

  std::string full_path(std::string file_path)
  {
    std::stringstream final_path;
    final_path << proc_path << "/" << file_path;
    return final_path.str();
  }

  void load_config(int argc, char ** argv) {
    Json::Value root;
    Json::Reader reader;
    std::ifstream scoundrel_conf;
    scoundrel_conf.open(full_path("scoundrel.json").c_str());

    bool parsed = reader.parse(scoundrel_conf, root);
    scoundrel_conf.close();

    std::cout << full_path("scoundrel.json") << std::endl;
    if (parsed) {
      WINDOW_WIDTH = root.get("window_width", 1024).asInt();
      WINDOW_HEIGHT = root.get("window_height", 788).asInt();
      game_start_level = root.get("game_start_level", 0).asInt();
      current_level = root.get("current_level", 0).asInt();
      total_levels = root.get("total_levels", 1).asInt();
    } else {
      std::cout << "Unable to parse config" << std::endl;
      std::cout << reader.getFormatedErrorMessages() << std::endl;
      exit(1);
    }
  }

  sf::Texture load_image(std::string image_path) {
    sf::Texture tex;
    if (!tex.loadFromFile(image_path)) {
      std::cout << "Failed to load " << image_path << std::endl;
    }
    return tex;
  }

  sf::RenderWindow* init_sfml() {
    sf::RenderWindow* game_window = new sf::RenderWindow();
    game_window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Scoundrel");
    return game_window;
  }


  void init_tile_animations() {
    tile_sheet = load_image(full_path("tile_sheet.png"));

    //TODO: offload these into a config file later

    //Rock 1 Tile
    animation_map[1] = Animation();
    animation_map[1].set_sprite_sheet(&tile_sheet);
    animation_map[1].add_frame(sf::IntRect(32, 0, 32, 32));
    animation_map[1].set_frame(0);

    ////Rock 2 Tile
    //animation_map[2] = Animation();
    //animation_map[2].set_sprite_sheet(&tile_sheet);
    //animation_map[2].add_frame(sf::IntRect(64, 0, 32, 32));
    //animation_map[2].set_frame(0);

    ////Rock 1 Ground
    //animation_map[3] = Animation();
    //animation_map[3].set_sprite_sheet(&tile_sheet);
    //animation_map[3].add_frame(sf::IntRect(224, 0, 32, 32));
    //animation_map[3].set_frame(0);

    ////Dead Grass
    //animation_map[4] = Animation();
    //animation_map[4].set_sprite_sheet(&tile_sheet);
    //animation_map[4].add_frame(sf::IntRect(0, 0, 32, 32));
    //animation_map[4].set_frame(0);

    ////Gray Rock 1
    //animation_map[5] = Animation();
    //animation_map[5].set_sprite_sheet(&tile_sheet);
    //animation_map[5].add_frame(sf::IntRect(96, 0, 32, 32));
    //animation_map[5].set_frame(0);

    ////Gray Rock 2
    //animation_map[6] = Animation();
    //animation_map[6].set_sprite_sheet(&tile_sheet);
    //animation_map[6].add_frame(sf::IntRect(128, 0, 32, 32));
    //animation_map[6].set_frame(0);

    ////Gray Rock Ground 1
    //animation_map[7] = Animation();
    //animation_map[7].set_sprite_sheet(&tile_sheet);
    //animation_map[7].add_frame(sf::IntRect(288, 0, 32, 32));
    //animation_map[7].set_frame(0);

    ////Brown Spikes
    //animation_map[100] = Animation();
    //animation_map[100].set_sprite_sheet(&tile_sheet);
    //animation_map[100].add_frame(sf::IntRect(160, 0, 32, 32));
    //animation_map[100].set_frame(0);

    ////Ceiling Brown Spikes
    //animation_map[101] = Animation();
    //animation_map[101].set_sprite_sheet(&tile_sheet);
    //animation_map[101].add_frame(sf::IntRect(0, 96, 32, 32));
    //animation_map[101].set_frame(0);

    ////Right Facing Brown Spikes
    //animation_map[102] = Animation();
    //animation_map[102].set_sprite_sheet(&tile_sheet);
    //animation_map[102].add_frame(sf::IntRect(32, 96, 32, 32));
    //animation_map[102].set_frame(0);

    ////left Facing Brown Spikes
    //animation_map[103] = Animation();
    //animation_map[103].set_sprite_sheet(&tile_sheet);
    //animation_map[103].add_frame(sf::IntRect(64, 96, 32, 32));
    //animation_map[103].set_frame(0);

    ////Floor Gray Spikes
    //animation_map[104] = Animation();
    //animation_map[104].set_sprite_sheet(&tile_sheet);
    //animation_map[104].add_frame(sf::IntRect(192, 0, 32, 32));
    //animation_map[104].set_frame(0);

    //Player walk left
    animation_map[300] = Animation();
    animation_map[300].set_sprite_sheet(&tile_sheet);
    animation_map[300].add_frame(sf::IntRect(96, 32, 32, 32));
    animation_map[300].add_frame(sf::IntRect(128, 32, 32, 32));
    animation_map[300].add_frame(sf::IntRect(160, 32, 32, 32));
    animation_map[300].add_frame(sf::IntRect(128, 32, 32, 32));
    animation_map[300].set_frame_time(5);
    animation_map[300].set_frame(0);

    //Player walk right
    animation_map[301] = Animation();
    animation_map[301].set_sprite_sheet(&tile_sheet);
    animation_map[301].add_frame(sf::IntRect(0, 32, 32, 32));
    animation_map[301].add_frame(sf::IntRect(32, 32, 32, 32));
    animation_map[301].add_frame(sf::IntRect(64, 32, 32, 32));
    animation_map[301].add_frame(sf::IntRect(32, 32, 32, 32));
    animation_map[301].set_frame_time(5);
    animation_map[301].set_frame(0);

    //Player stand left
    animation_map[302] = Animation();
    animation_map[302].set_sprite_sheet(&tile_sheet);
    animation_map[302].add_frame(sf::IntRect(96, 32, 32, 32));
    animation_map[302].set_frame(0);

    //Player stand right
    animation_map[303] = Animation();
    animation_map[303].set_sprite_sheet(&tile_sheet);
    animation_map[303].add_frame(sf::IntRect(0, 32, 32, 32));
    animation_map[303].set_frame(0);

    ////Battery
    //animation_map[304] = Animation();
    //animation_map[304].set_sprite_sheet(&tile_sheet);
    //animation_map[304].add_frame(sf::IntRect(352, 0, 32, 32));
    //animation_map[304].add_frame(sf::IntRect(384, 0, 32, 32));
    //animation_map[304].add_frame(sf::IntRect(416, 0, 32, 32));
    //animation_map[304].add_frame(sf::IntRect(384, 0, 32, 32));
    //animation_map[304].set_frame_time(5);
    //animation_map[304].set_frame(0);

    ////Exit Arrow
    //animation_map[305] = Animation();
    //animation_map[305].set_sprite_sheet(&tile_sheet);
    //animation_map[305].add_frame(sf::IntRect(0, 64, 32, 32));
    //animation_map[305].add_frame(sf::IntRect(32, 64, 32, 32));
    //animation_map[305].add_frame(sf::IntRect(64, 64, 32, 32));
    //animation_map[305].add_frame(sf::IntRect(96, 64, 32, 32));
    //animation_map[305].set_frame_time(5);
    //animation_map[305].set_frame(0);

    ////Radio
    //animation_map[306] = Animation();
    //animation_map[306].set_sprite_sheet(&tile_sheet);
    //animation_map[306].add_frame(sf::IntRect(0, 128, 32, 32));
    //animation_map[306].add_frame(sf::IntRect(32, 128, 32, 32));
    //animation_map[306].add_frame(sf::IntRect(64, 128, 32, 32));
    //animation_map[306].add_frame(sf::IntRect(32, 128, 32, 32));
    //animation_map[306].set_frame_time(5);
    //animation_map[306].set_frame(0);
    
    ////Grass
    animation_map[0] = Animation();
    animation_map[0].set_sprite_sheet(&tile_sheet);
    animation_map[0].add_frame(sf::IntRect(0, 192, 32, 32));
    animation_map[0].set_frame(0);

  }

  void init_graphics() {
    sprites = new sf::Sprite[10];
    textures = new sf::Texture[10];

    init_tile_animations();

    game_font.loadFromFile(full_path("digital_tech.otf"));
  }

  void init_audio() {
    sound_buffers = new sf::SoundBuffer[5];
    sounds = new sf::Sound[5];
    //sound_buffers[0].loadFromFile(full_path("jump.wav"));
    //sounds[0].setBuffer(sound_buffers[0]);

    //sound_buffers[1].loadFromFile(full_path("battery.wav"));
    //sounds[1].setBuffer(sound_buffers[1]);

    //sound_buffers[2].loadFromFile(full_path("death.wav"));
    //sounds[2].setBuffer(sound_buffers[2]);
  }

  void clear_game_entities() {
    for (std::list<Entity *>::iterator it=game_entities.begin(); it != game_entities.end(); ++it) {
      delete *it;
    }
    game_entities.clear();
  }

  void reset_game(bool hard=false) {
    if (hard)
      current_level = game_start_level;

    player->set_alive();
    player->reset();
    clear_game_entities();
    game_mode = GAME_PLAY;
    game_map->load_level(proc_path, current_level, player, &camera, &animation_map, sounds, game_entities);
    player->walk_right();
    framerate = fps_clock.restart().asSeconds();
  }

  void init_game()
  {
    init_graphics();
    init_audio();

    player = new Player(&sprites[3], Point(300, 300), Rectangle(6, 4, 26, 30));
    player->set_walk_speed(WALK, MAX_WALK, WALK_STOP);
    player->set_movement(0, 0);
    player->set_fall_speed(GRAVITY, TERMINAL_VELOCITY);
    player->set_jump_speed(JUMP_SPEED);
    player->set_walk_frames(&animation_map[300], &animation_map[301]);
    player->set_stand_frames(&animation_map[302], &animation_map[303]);

    camera.set_absolute(0, 0);
    camera.set_window_size(WINDOW_WIDTH, WINDOW_HEIGHT);
    camera.set_window_snap(CAMERA_SNAP_X, CAMERA_SNAP_Y);
    camera.calculate_snap();

    game_map = new GameMap(&tile_helper);
    reset_game();
  }

  void deinitialize_game(sf::RenderWindow* window) {
    delete window;
    delete player;
    game_map->clear();
    clear_game_entities();
    delete game_map;
    delete[] textures;
    delete[] sprites;
    delete[] sound_buffers;
    delete[] sounds;
    for (std::list<Entity *>::iterator it=game_entities.begin(); it != game_entities.end(); ++it) {
      delete *it;
    }
  }

  void check_and_move_camera() {
    Point player_coords = player->position();
    Camera::CAMERA_SNAP cam_snap_horz;
    Camera::CAMERA_SNAP cam_snap_vert;

    cam_snap_horz = camera.point_snap_horizontal(player_coords);
    cam_snap_vert = camera.point_snap_vertical(player_coords);

    sf::Vector2f player_move = player->get_movement();
    if (player_move.x < 0 && cam_snap_horz == Camera::SNAP_LEFT) {
      camera.move(player->get_movement().x, 0);
    } else if (player_move.x > 0 && cam_snap_horz == Camera::SNAP_RIGHT) {
      camera.move(player->get_movement().x, 0);
    }

    if (player_move.y < 0 && cam_snap_vert == Camera::SNAP_TOP) {
      camera.move(0, player->get_movement().y);
    } else if (player_move.y > 0 && cam_snap_vert == Camera::SNAP_BOTTOM) {
      camera.move(0, player->get_movement().y);
    }
  }

  void player_collide_top(Point left, Point right, Point left_delta, Point right_delta) {
    Point player_tile_left = tile_helper.toTileCoords(left_delta);
    if (player_tile_left.y < 0) {
      sf::Vector2f player_movement = player->get_movement();
      player->set_movement(player_movement.x, 0);
      return;
    }

    Point player_tile_right = tile_helper.toTileCoords(right_delta);

    for (int i = (int)player_tile_left.x; i <= (int)player_tile_right.x; ++i) {
      int ptl = (int)player_tile_left.y;
      if (!game_map->get_tile(i, ptl)->passable()) {
        sf::Vector2f player_movement = player->get_movement();
        Point tile_world = tile_helper.fromTileCoords(i, ptl); 
        float delta_y = float(left.y - tile_world.y - TILE_HEIGHT);
        if (delta_y == -1.f) {
          player->set_movement(player_movement.x, 0);
        } else if ((-delta_y) >= player_movement.y) {
          player->set_movement(player_movement.x, -delta_y);
        }
      }
      if (game_map->get_tile(i, ptl)->is_deadly()) {
        player->kill();
        return;
      }
    }
  }

  void player_collide_bottom(Point left, Point right, Point left_delta, Point right_delta) {
    Point player_tile_left = tile_helper.toTileCoords(left_delta);
    if (player_tile_left.y >= game_map->get_height()) {
      sf::Vector2f player_movement = player->get_movement();
      player->set_movement(player_movement.x, 0);
      return;
    }

    Point player_tile_right = tile_helper.toTileCoords(right_delta);
    for (int i = (int)player_tile_left.x; i <= (int)player_tile_right.x; ++i) {
      int ptl = (int) player_tile_left.y;
      if (!game_map->get_tile(i, ptl)->passable()) {
        sf::Vector2f player_movement = player->get_movement();
        Point tile_world = tile_helper.fromTileCoords(i, ptl);
        float delta_y = float(tile_world.y - left.y);
        /*
         * Three states:
         *
         * Falling, but we'll land on this frame
         * Still Falling
         * Landed
         *
         * Falling, but land -> set_movement(player.move.x, diff(player, tile));
         * Still falling -> do nothing
         * landed -> unset(ENTITY_JUMPING) - landed counts as 1 px above the tile
         */
        if (delta_y == 1.f) {
          player->unset_state(ENTITY_JUMPING);
          player->set_movement(player_movement.x, 0);
        } else if (delta_y > 1.f && delta_y <= player_movement.y) {
          player->unset_state(ENTITY_JUMPING);
          player->set_movement(player_movement.x, (delta_y - 1));
        } else {
          player->set_state(ENTITY_JUMPING);
        }
      }
      if (game_map->get_tile(i, ptl)->is_deadly()) {
        player->kill();
        return;
      }
    }
  }

  void player_collide_left(Point top, Point bottom, Point top_delta, Point bottom_delta) {
    Point player_tile_top = tile_helper.toTileCoords(top_delta);
    if (player_tile_top.x < 0) {
      sf::Vector2f player_movement = player->get_movement();
      player->set_movement(0, player_movement.y);
      return;
    }

    Point player_tile_bottom = tile_helper.toTileCoords(bottom_delta);
    for (int i = (int)player_tile_top.y; i <= (int)player_tile_bottom.y; ++i) {
      int ptt = (int)player_tile_top.x;
      if (game_map->get_tile(ptt, i)->is_deadly()) {
        player->kill();
        return;
      }
      if (!game_map->get_tile(ptt, i)->passable()) {
        sf::Vector2f player_movement = player->get_movement();
        Point tile_world = tile_helper.fromTileCoords(ptt, i);
        float delta_x = float(top.x - (tile_world.x + TILE_WIDTH));
        if (delta_x <= 0.f) {
          player->set_movement(0, player_movement.y);
        } else if (delta_x > 0.f) {
          if (-delta_x >= player_movement.x)
            player->set_movement(-delta_x, player_movement.y);
          else
            player->set_movement(0, player_movement.y);
        }
      }
    }
  }

  void player_collide_right(Point top, Point bottom, Point top_delta, Point bottom_delta) {
    Point player_tile_top = tile_helper.toTileCoords(top_delta);
    if (player_tile_top.x >= game_map->get_width()) {
      sf::Vector2f player_movement = player->get_movement();
      player->set_movement(0, player_movement.y);
      return;
    }

    Point player_tile_bottom = tile_helper.toTileCoords(bottom_delta);
    for (int i = (int)player_tile_top.y; i <= (int)player_tile_bottom.y; ++i) {
      Point pos = player->position();
      Rectangle rect = player->get_bounding_rect();
      int ptt = (int)player_tile_top.x;
      if (game_map->get_tile(ptt, i)->is_deadly()) {
        player->kill();
        return;
      }
      if (!game_map->get_tile(ptt, i)->passable()) {
        sf::Vector2f player_movement = player->get_movement();
        Point tile_world = tile_helper.fromTileCoords(ptt, i);
        float delta_x = float(tile_world.x - top.x);
        if (delta_x <= 0.f) {
          player->set_movement(0, player_movement.y);
        } else if (delta_x > 0.f) {
          if (delta_x > player_movement.x)
            player->set_movement(delta_x, player_movement.y);
          else
            player->set_movement(0.f, player_movement.y);
        }
        return;
      }
    }
  }

  void player_move_up(float delta) {
    Rectangle player_rect = player->get_bounding_rect();

    Point player_left_coords(player_rect.left(), player_rect.top());
    Point player_right_coords(player_rect.right(), player_rect.top());
    Point player_delta_left(player_left_coords.x, player_left_coords.y + delta);
    Point player_delta_right(player_right_coords.x, player_right_coords.y + delta);
    player_collide_top(player_left_coords, player_right_coords, player_delta_left, player_delta_right);
  }

  void player_move_down(float delta) {
    Rectangle player_rect = player->get_bounding_rect();

    Point player_left_coords(player_rect.left(), player_rect.bottom());
    Point player_right_coords(player_rect.right(), player_rect.bottom());
    Point player_delta_left(player_left_coords.x, player_left_coords.y + delta);
    Point player_delta_right(player_right_coords.x, player_right_coords.y + delta);

    player_collide_bottom(player_left_coords, player_right_coords, player_delta_left, player_delta_right);
  }

  void player_move_left(float delta) {
    Rectangle player_rect = player->get_bounding_rect();

    Point player_top_coords(player_rect.left(), player_rect.top());
    Point player_bottom_coords(player_rect.left(), player_rect.bottom());
    Point player_delta_top(player_top_coords.x + delta, player_top_coords.y);
    Point player_delta_bottom(player_bottom_coords.x + delta, player_bottom_coords.y);

    player_collide_left(player_top_coords, player_bottom_coords, player_delta_top, player_delta_bottom);
  }

  void player_move_right(float delta) {
    Rectangle player_rect = player->get_bounding_rect();

    Point player_top_coords(player_rect.right(), player_rect.top());
    Point player_bottom_coords(player_rect.right(), player_rect.bottom());
    Point player_delta_top(player_top_coords.x + delta, player_top_coords.y);
    Point player_delta_bottom(player_bottom_coords.x + delta, player_bottom_coords.y);
    player_collide_right(player_top_coords, player_bottom_coords, player_delta_top, player_delta_bottom);
  }

  void player_move_map_left(float delta) {
    player->move(Point(delta, 0));
  }

  void player_move_map_right(float delta) {
    player->move(Point(delta, 0));
  }

  void player_move_map_up(float delta) {
    player->move(Point(0, delta));
  }

  void player_move_map_down(float delta) {
    player->move(Point(0, delta));
  }

  void player_move() {
    sf::Vector2f player_move = player->get_movement();
    if (key_state.right_pressed)
      player_move_map_right(player_move.x);
    else if (key_state.left_pressed)
      player_move_map_left(player_move.x);

    if (key_state.up_pressed)
      player_move_map_up(player_move.y);
    else if (key_state.down_pressed)
      player_move_map_down(player_move.y);
    //}
  }

  void handle_events(sf::RenderWindow* window) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          key_state.left_pressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          key_state.right_pressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          key_state.down_pressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          key_state.up_pressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
          if (game_mode == GAME_PLAY)
            game_mode = GAME_MAP_EDIT;
          else
            game_mode = GAME_PLAY;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          if (game_mode == GAME_END) {
            reset_game();
            return;
          } else if (game_mode == GAME_WIN) {
            reset_game(true);
            return;
          } else if (game_mode == GAME_NEXT_LEVEL) {
            game_mode = GAME_PLAY;
            return;
          }
          key_state.space_pressed = true;
        }

        switch(event.key.code) {
          case sf::Keyboard::Escape:
            window->close();
            break;
          case sf::Keyboard::F:
            show_fps = !show_fps;
            break;
          default:
            break;
        }
      } else if (event.type == sf::Event::KeyReleased) {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          key_state.left_pressed = false;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          key_state.right_pressed = false;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          key_state.up_pressed = false;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          key_state.down_pressed = false;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          key_state.space_pressed = false;
          key_state.space_was_pressed = false;
        }
      }

      if (event.type == sf::Event::Closed)
        window->close();
    }

    if (key_state.left_pressed)
      player->walk_left();
    if (key_state.right_pressed)
      player->walk_right();
    if (key_state.up_pressed)
      player->float_up();
    if (key_state.down_pressed)
      player->float_down();
    if (!key_state.up_pressed && !key_state.down_pressed) {
      player->stop_floating();
    }

    if (!key_state.left_pressed && !key_state.right_pressed) {
      player->stop_walking();
    }
    
  }

  void display_framerate(sf::RenderWindow* window) {
    //Super basic framerate calculator.
    //
    //TODO: Make a better one - http://gafferongames.com/game-physics/fix-your-timestep/
    char frame_string[5];
    int rate = (int)(1.0f / framerate);
    sprintf(frame_string, "%d", rate);
    sf::Text test_text(frame_string, game_font);
    test_text.setPosition(100, 20);
    window->draw(test_text);
  }

  void collide_objects() {
    Collidable temp;
    Rectangle player_rect = player->get_bounding_rect();
    for (std::list<Entity *>::iterator it=game_entities.begin(); it != game_entities.end(); ++it) {
      Rectangle other_rect = (*it)->get_bounding_rect();
      if (player_rect.intersects(&other_rect)) {
        Entity* game_entity = (*it);

        // In a better world, I'd pass in a complete game context object that can be updated
        int cur_lev = current_level;
        dynamic_cast<Collidable *>(game_entity)->perform_collision_action(player, current_level);
        if (!game_entity->is_alive()) {
          delete *it;
          game_entities.erase(it);
        }
        if (cur_lev != current_level) {
          //next map!
          if (current_level > total_levels) {
            //You win!
            game_mode = GAME_WIN;
          } else {
            game_mode = GAME_NEXT_LEVEL;
            reset_game();
            return;
          }
        }
      }
    }
  }

  void game_loop(sf::RenderWindow* window) {
    int decay = 30;
    while (window->isOpen()) {
      window->clear(sf::Color::Black);
      handle_events(window);

      if (game_mode == GAME_PLAY || game_mode == GAME_MAP_EDIT) {
        Rectangle view = camera.get_view_rect();
        Point camera_pos = view.upper_left();

        player_move();
        collide_objects();

        check_and_move_camera();

        Point tile_start = tile_helper.toTileCoords(camera_pos);

        Point draw_start = tile_helper.toTileCoords(view.left(), view.top());
        Point draw_end = tile_helper.toTileCoords(view.right(), view.bottom());

        int map_width = game_map->get_width();
        int map_height = game_map->get_height();

        draw_start.x = draw_start.x < 0 ? 0 : draw_start.x;
        draw_start.y = draw_start.y < 0 ? 0 : draw_start.y;
        draw_start.x = draw_start.x > map_width ? map_width : draw_start.x;
        draw_start.y = draw_start.y > map_height ? map_height : draw_start.y;
        draw_end.x = draw_end.x > map_width ? map_width : draw_end.x;
        draw_end.y = draw_end.y > map_height ? map_height : draw_end.y;
        draw_end.x = draw_end.x < 0 ? 0 : draw_end.x;
        draw_end.y = draw_end.y < 0 ? 0 : draw_end.y;

        game_map->draw(window, camera_pos, draw_start, draw_end, player, game_entities);

        for (std::list<Entity *>::iterator it=game_entities.begin(); it != game_entities.end(); ++it) {
          (*it)->draw(window, camera_pos);
        }

        player->draw(window, camera_pos);

        if (show_fps)
          display_framerate(window);

        if (game_mode == GAME_PLAY) {
          framerate = fps_clock.restart().asSeconds();
        }
      }
      window->display();
    }
  }
}

int main(int argc, char ** argv)
{
  char full_path[1024];
  realpath(argv[0], full_path);

  Scoundrel::proc_path = full_path;
  unsigned found = Scoundrel::proc_path.find_last_of("/");
  Scoundrel::proc_path = Scoundrel::proc_path.substr(0, found);

  Scoundrel::load_config(argc, argv);
  sf::RenderWindow* window = Scoundrel::init_sfml();
  window->setFramerateLimit(Scoundrel::FRAMERATE_LIMIT);
  window->setVerticalSyncEnabled(true);
  Scoundrel::init_game();
  Scoundrel::game_loop(window);
  Scoundrel::deinitialize_game(window);
  return 0;
}
