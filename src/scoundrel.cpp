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

  void init_scoundrel(int window_width, int window_height) {
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

  void game_loop() {
    while (game_window->isOpen()) {
      game_window->clear(sf::Color::Black);
      handle_events(game_window);
      game_window->display();
    }
  }
}
