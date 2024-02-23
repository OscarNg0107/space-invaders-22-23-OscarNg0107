
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"
#include "sstream"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  bool CollisionCheck(sf::Sprite sprite1, sf::Sprite sprite2);
  void Reset();
  void RestartClock();
  void AlienWallCollision();
  void AlienPointReachCheck();

  enum Gamestate {MainMenu,  InGame, GameOver, GameWin, Option};
 private:
  //Settings
  sf::RenderWindow& window;
  Gamestate gamestate = MainMenu;
  sf::Font font;

  //main menu texts
  sf::Text title_text;
  sf::Text start_text;

  // InGame

  //score

  sf::Text scoreboard;
  std::ostringstream score_number;
  int score = 0;

  // ship
  GameObject ship;
  sf::Texture ship_texture;

  //alien
  GameObject aliens[50];
  sf::Texture alien_texture;
  int aliens_row = 10;
  int aliens_column = 5;
  int dead_alien_counter = 0;
  sf::Clock clock1;
  sf::Time elapsed;
  float gravity_multipler = 9.81f;
  float  curve_value = 0;
  int screen_centre_x = 0;
  //shots
  GameObject shots[3];
  sf::Texture shots_texture;
  int current_shot_number = 0;
  int launched_shots_counter = 0;
  int wall_hit_counter = 0;

  //GameWin text

  sf::Text final_result;
  sf::Text congrats_text;
  sf::Text restart_text;
  sf::Text return_menu_text;

  bool restart_selected = true;

  //GameOver text

  sf::Text game_over_text;


  //Option
  sf::Text enemy_mode_title;
  sf::Text normal_type_text;
  sf::Text gravity_type_text;
  sf::Text curve_type_text;
  sf::Text wave_type_text;

  int selected_mode = 0;
};

#endif // SPACEINVADERS_GAME_H
