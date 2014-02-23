#include "scoundrel.h"

namespace Scoundrel {
  sf::RenderWindow* game_window;
  std::list<Entity*> game_entities;

  void load_config(std::string path) {
    Json::Value root;
    Json::Reader reader;
    std::ifstream scoundrel_conf;

    //TODO: This need to be a configurable filename
    //scoundrel_conf.open(full_path("scoundrel.json").c_str());
    scoundrel_conf.open(path.c_str());

    bool parsed = reader.parse(scoundrel_conf, root);
    scoundrel_conf.close();

    if (parsed) {
      WINDOW_WIDTH = root.get("window_width", 1024).asInt();
      WINDOW_HEIGHT = root.get("window_height", 788).asInt();
    } else {
      std::cout << "Unable to parse config" << std::endl;
      std::cout << reader.getFormatedErrorMessages() << std::endl;
      exit(1);
    }
  }

  sf::RenderWindow* init_window() {
    sf::RenderWindow* game_window = new sf::RenderWindow();
    game_window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Scoundrel");
    return game_window;
  }

  sf::RenderWindow* init_sfml(std::string path) {
    load_config(path);
    return init_window();
  }

  sf::RenderWindow* init_sfml(int window_width, int window_height) {
    WINDOW_WIDTH = window_width;
    WINDOW_HEIGHT = window_height;
    return init_window();
  }

  void init_tile_animations() {
  }

  void init_graphics() {
  }

  void init_audio() {
  }

  void clear_game_entities() {
    for (std::list<Entity *>::iterator it=game_entities.begin(); it != game_entities.end(); ++it) {
      delete *it;
    }
    game_entities.clear();
  }

  void init_scoundrel(std::string path)
  {
    //TODO: place this better.
    game_window = init_sfml(path);
    init_graphics();
    init_audio();
  }

  void init_scoundrel(int window_width, int window_height, int framerate) {
    max_framerate = framerate;
    U64 frame_time = (1.0f / float(max_framerate)) * 100000;

    game_window = init_sfml(window_width, window_height);
    init_graphics();
    init_audio();
  }

  void deinitialize_game() {
    delete game_window;
    clear_game_entities();
    for (std::list<Entity *>::iterator it=game_entities.begin(); it != game_entities.end(); ++it) {
      delete *it;
    }
  }

  void handle_events(sf::RenderWindow* window) {
    sf::Event event;
    while (window->pollEvent(event)) {
        switch(event.key.code) {
          case sf::Keyboard::Escape:
            window->close();
            break;
          default:
            break;
        }
      if (event.type == sf::Event::Closed)
        window->close();
    }
  }

  void collide_objects() {
  }

  void set_frame_handler(FrameHandler* game) {
    _game = game;
  }

  void insert_layer(Layer* layer, U32 index) {
    //TODO: actually insert at the index into the eventual linked list
    _layer = layer;
  }

  Layer* get_layer(U32 index) {
    return NULL;
  }

  void game_loop() {

    //TODO: This needs to be configurable, colorwise, or even drawing fullscreen graphics.
    //      Best answer seems to suggest abstraction like TileLayers, ColorLayers, ImageLayers
    //      and Composite Layers(former 3 in any order)
    U64 sleep_time, elapsed;
    while (game_window->isOpen()) {
      _game->frame_start();

      game_window->clear(sf::Color::Black);

      //TODO: Pull this out into a draw_loop()
      _layer->draw();

      handle_events(game_window);
      elapsed = game_clock.get_elapsed_time();
      sleep_time = frame_time - elapsed;

      // TODO: Decide on run time resolution. Book has suggestions
      // runtime += (sleep_time + elapsed);

      if (sleep_time >= 0.f)
        game_clock.wait(sleep_time);
      game_window->display();
      _game->frame_end(elapsed);
      game_clock.restart();
    }
  }
}
