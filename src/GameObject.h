#include <SFML/Graphics.hpp>
#include "Vector2.h"
#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename );
  sf::Sprite* getSprite();

  void setMovingDirection(float x, float y);
  Vector2 getMovingDirection();
  void moveLeft(bool boolean);
  bool moveLeftBool();
  void moveRight(bool boolean);
  bool moveRightBool();
  void moveUp(bool boolean);
  bool moveUpBool();
  void moveDown(bool boolean);
  bool moveDownBool();
  void setVisility(bool  boolean);
  bool visibilityBool();


 private:
  sf::Sprite objectSprite;
  sf::Sprite* sprite_ptr = nullptr;
  bool moving_left = false;
  bool moving_right = false;
  bool moving_up = false;
  bool moving_down = false;
  bool visibility = true;
  Vector2 direction = Vector2(0,0);
};


#endif // SPACEINVADERS_GAMEOBJECT_H
