#include "GameObject.h"
#include <iostream>
GameObject::GameObject()
{
  sprite_ptr = new sf::Sprite;
}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if(!texture.loadFromFile(filename))
  {
    std::cout << "texture loading fail";
    return false;
  }
  objectSprite.setTexture(texture);
}

sf::Sprite* GameObject::getSprite()
{
  sprite_ptr = &objectSprite;
  *sprite_ptr = objectSprite;
  return sprite_ptr;
}
void GameObject::setVisility(bool boolean)
{
  visibility = boolean;
}

bool GameObject::visibilityBool()
{
  return visibility;
}

void GameObject::moveLeft(bool boolean)
{
  moving_left = boolean;
}

bool GameObject::moveLeftBool()
{
  return moving_left;
}

void GameObject::moveRight(bool boolean)
{
  moving_right = boolean;
}

bool GameObject::moveRightBool()
{
  return moving_right;
}

void GameObject::moveUp(bool boolean)
{
  moving_up = boolean;
}

bool GameObject::moveUpBool()
{
  return moving_up;
}

void GameObject::moveDown(bool boolean)
{
  moving_down = boolean;
}

bool GameObject::moveDownBool()
{
  return moving_down;
}


void GameObject::setMovingDirection(float x, float y)
{
  direction = Vector2(x ,y);
  direction.normalise();
}
Vector2 GameObject::getMovingDirection()
{
  return direction;
}

GameObject::~GameObject()
{
  if(sprite_ptr != nullptr)
  {
    delete sprite_ptr;
    sprite_ptr = nullptr;
  }
}