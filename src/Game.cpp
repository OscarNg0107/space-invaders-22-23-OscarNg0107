
#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  if(!font.loadFromFile("Data/Fonts/open-sans/OpenSans-ExtraBold.ttf"))
  {
    std::cout << "font loading error";
  }


  // Main menu setup
  title_text.setString("SPACE INVADERS");
  title_text.setFont(font);
  title_text.setCharacterSize(120);
  title_text.setFillColor(sf::Color(255,255,255,255));
  title_text.setPosition(window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
                         title_text.getGlobalBounds().height * 2);

  start_text.setString("[ Press space to start game ]");
  start_text.setFont(font);
  start_text.setCharacterSize(50);
  start_text.setPosition(window.getSize().x / 2 - start_text.getGlobalBounds().width / 2,
                         window.getSize().y - start_text.getGlobalBounds().height * 4);
  start_text.setFillColor(sf::Color(255,255,255,125));


  //InGame

  //Scoreboard
  score_number << score;
  scoreboard.setString("Score: " + score_number.str());
  scoreboard.setFont(font);
  scoreboard.setCharacterSize(40);
  scoreboard.setFillColor(sf::Color(255,255,255,255));
  scoreboard.setPosition(20, 20);


  //ship setup
  ship.initialiseSprite(ship_texture, "Data/Images/Alien UFO pack/PNG/playerShip2_red.png");
  ship.getSprite()->setScale(0.8, 0.8);
  ship.getSprite()->setPosition(window.getSize().x / 2 - ship.getSprite()->getGlobalBounds().width /2 ,
                                 window.getSize().y - ship.getSprite()->getGlobalBounds().height *1.5 );
  ship.setMovingDirection(2,0);
  ship.setVisility(true);


  //aliens setup
  for(int i = 0 ; i < aliens_row; i++)
  {
    for(int j = 0; j < aliens_column; j++)
    {
      aliens[i * aliens_column + j].initialiseSprite(alien_texture, "Data/Images/Alien UFO pack/PNG/shipBeige_manned.png");
      aliens[i * aliens_column + j].getSprite()->setScale(0.5f, 0.5f);
     // aliens[i * aliens_column + j].getSprite()->setPosition( window.getSize().x / 4 - aliens[i].getSprite()->getGlobalBounds().width + 65 * i,
                                                            //  aliens[i].getSprite()->getGlobalBounds().height /2 + 65 * j);
      //aliens[i * aliens_column + j].getSprite()->setPosition( 10+ 65 * i,
                                                              //10+ 65 * j);
      aliens[i * aliens_column + j].getSprite()->setPosition( window.getSize().x / 4 - aliens[i].getSprite()->getGlobalBounds().width + 65 * i,
                                                             aliens[i].getSprite()->getGlobalBounds().height /2 + 65 * j);
      aliens[i * aliens_column + j].setMovingDirection(2, 2);
      aliens[i * aliens_column + j].setVisility(true);
      aliens[i * aliens_column + j].moveRight(true);
    }
  }

   // shots setup
  for(int i = 0; i < 3; i++)
  {
    shots[i].initialiseSprite(shots_texture, "Data/Images/SpaceShooterRedux/PNG/Lasers/laserBlue03.png");
    shots[i].getSprite()->setScale(0.7f, 0.7f);
    shots[i].setMovingDirection(0, 5);
    shots[i].setVisility(false);
  }

  //Game Win Setting
  congrats_text.setString("Congratulation");
  congrats_text.setFont(font);
  congrats_text.setCharacterSize(130);
  congrats_text.setFillColor(sf::Color(255,255,255,255));
  congrats_text.setPosition(window.getSize().x / 2 - congrats_text.getGlobalBounds().width / 2,
                            congrats_text.getGlobalBounds().height );

  restart_text.setString("Restart");
  restart_text.setFont(font);
  restart_text.setCharacterSize(40);
  restart_text.setFillColor(sf::Color(255,255,255,125));
  restart_text.setPosition(window.getSize().x / 8 - restart_text.getGlobalBounds().width /2,
                           window.getSize().y - restart_text.getGlobalBounds().height * 3);

  return_menu_text.setString("Return to main menu");
  return_menu_text.setFont(font);
  return_menu_text.setCharacterSize(40);
  return_menu_text.setFillColor(sf::Color(255,255,255,125));
  return_menu_text.setPosition(window.getSize().x *5 /8 - restart_text.getGlobalBounds().width /2,
                               window.getSize().y - restart_text.getGlobalBounds().height * 3);

  final_result.setString("Your score is: "+ score_number.str());
  final_result.setFont(font);
  final_result.setCharacterSize(60);
  final_result.setFillColor(sf::Color(255,255,255,255));
  final_result.setPosition( window.getSize().x / 2 - final_result.getGlobalBounds().width /2 ,
                           window.getSize().y / 2 + final_result.getGlobalBounds().height);


  //Game Over Setting
  game_over_text.setString("GAME OVER");
  game_over_text.setFont(font);
  game_over_text.setCharacterSize(130);
  game_over_text.setFillColor(sf::Color(255,255,255,255));
  game_over_text.setPosition(window.getSize().x / 2 - game_over_text.getGlobalBounds().width / 2,
                             game_over_text.getGlobalBounds().height );

  //Option setup
  enemy_mode_title.setString("Select enemy moving type");
  enemy_mode_title.setFont(font);
  enemy_mode_title.setCharacterSize(60);
  enemy_mode_title.setFillColor(sf::Color(255,255,255,255));
  enemy_mode_title.setPosition(window.getSize().x / 2 - enemy_mode_title.getGlobalBounds().width / 2,
                               enemy_mode_title.getGlobalBounds().height * 2);

  normal_type_text.setString("Classic");
  normal_type_text.setFont(font);
  normal_type_text.setCharacterSize(40);
  normal_type_text.setFillColor(sf::Color(255,255,255,125));
  normal_type_text.setPosition(window.getSize().x / 2 - normal_type_text.getGlobalBounds().width /2,
                               300);

  gravity_type_text.setString("Gravity");
  gravity_type_text.setFont(font);
  gravity_type_text.setCharacterSize(40);
  gravity_type_text.setFillColor(sf::Color(255,255,255,125));
  gravity_type_text.setPosition(window.getSize().x / 2 - gravity_type_text.getGlobalBounds().width /2,
                                normal_type_text.getPosition().y+ normal_type_text.getGlobalBounds().height * 2);

  curve_type_text.setString("Curve");
  curve_type_text.setFont(font);
  curve_type_text.setCharacterSize(40);
  curve_type_text.setFillColor(sf::Color(255,255,255,125));
  curve_type_text.setPosition(window.getSize().x / 2 - curve_type_text.getGlobalBounds().width /2,
                              normal_type_text.getPosition().y+ normal_type_text.getGlobalBounds().height * 4);

  wave_type_text.setString("Wave");
  wave_type_text.setFont(font);
  wave_type_text.setCharacterSize(40);
  wave_type_text.setFillColor(sf::Color(255,255,255,125));
  wave_type_text.setPosition(window.getSize().x / 2 - wave_type_text.getGlobalBounds().width /2,
                             curve_type_text.getPosition().y+ curve_type_text.getGlobalBounds().height * 2);


  return true;
}

void Game::update(float dt)
{
  if(gamestate == InGame)
  {
    //scoreboard update
    score_number.str("");
    score_number<< score;
    scoreboard.setString("Score: " + score_number.str());


    //ship movement
    if(ship.moveRightBool() && (ship.getSprite()->getPosition().x + ship.getSprite()->getGlobalBounds().width < window.getSize().x))
    {
      ship.getSprite()->move( ship.getMovingDirection().operator*(400).x * dt,0);
    }

    if(ship.moveLeftBool() && ship.getSprite()->getPosition().x > 0 )
    {
      ship.getSprite()->move(ship.getMovingDirection().operator*(-400).x * dt, 0);
    }

    //alien movement
    if(selected_mode == 0)
    {
      for (int i = 0; i < aliens_row * aliens_column; i++)
      {
        if (aliens[i].moveRightBool())
        {
          aliens[i].getSprite()->move(
            aliens[i].getMovingDirection().operator*(200).x * dt, 0);
        }
        if (aliens[i].moveLeftBool())
        {
          aliens[i].getSprite()->move(
            aliens[i].getMovingDirection().operator*(-200).x * dt, 0);
        }
        if (aliens[i].moveDownBool())
        {
          aliens[i].getSprite()->move(
            0, aliens[i].getMovingDirection().operator*(100).y * dt);
        }
        AlienWallCollision();
      }
    }
    else if(selected_mode ==1)
    {
      gravity_multipler += 0.1f;
      for (int i = 0; i < aliens_row * aliens_column; i++)
      {
        if (aliens[i].moveRightBool())
        {
          aliens[i].getSprite()->move(
            aliens[i].getMovingDirection().operator*(100).x * dt, aliens[i].getMovingDirection().operator*(1).y * gravity_multipler* dt);
        }
        if (aliens[i].moveLeftBool())
        {
          aliens[i].getSprite()->move(
            aliens[i].getMovingDirection().operator*(-100).x * dt, aliens[i].getMovingDirection().operator*(1).y * gravity_multipler* dt);
        }
        if (aliens[i].moveDownBool())
        {
          aliens[i].getSprite()->move(
            0, aliens[i].getMovingDirection().operator*(100).y * dt);
        }
        AlienWallCollision();
      }
    }

    else if(selected_mode ==2)
    {
      for(int i = 0 ; i < aliens_row; i++)
      {
        for (int j = 0; j < aliens_column; j++)
        {
          if (aliens[29].getSprite()->getPosition().x + aliens[29].getSprite()->getGlobalBounds().width >= window.getSize().x)
          {
            wall_hit_counter +=1;
            aliens[i *aliens_column +j].moveRight(false);
            aliens[i *aliens_column +j].moveLeft(true);
          }

          if (aliens[0].getSprite()->getPosition().x <= 0)
          {
            wall_hit_counter += 1;
            aliens[i *aliens_column +j].moveRight(true);
            aliens[i *aliens_column +j].moveLeft(false);
          }

          if (aliens[i *aliens_column +j].moveRightBool())
          {
            aliens[i *aliens_column +j].getSprite()->setPosition(
              aliens[i *aliens_column +j].getSprite()->getPosition().x + 1,
              -(pow(
                  aliens[i *aliens_column +j].getSprite()->getPosition().x -
                    (window.getSize().x -
                     aliens[i *aliens_column +j].getSprite()->getGlobalBounds().width) /
                      2,2) /800) +320 +  0.5 *wall_hit_counter +65*j );
          };
          if (aliens[i *aliens_column +j].moveLeftBool())
          {
            aliens[i *aliens_column +j].getSprite()->setPosition(
              aliens[i *aliens_column +j].getSprite()->getPosition().x - 1,
              -(pow(
                  aliens[i *aliens_column +j].getSprite()->getPosition().x -
                    (window.getSize().x -
                     aliens[i *aliens_column +j].getSprite()->getGlobalBounds().width) /
                      2,2) /800) + 320+ 0.5  *wall_hit_counter  +65*j );
          };
        }
      }
    }

    else if(selected_mode == 3)
    {
      for(int i = 0 ; i < aliens_row; i++)
      {
        for (int j = 0; j < aliens_column; j++)
        {
          if (aliens[49].getSprite()->getPosition().x + aliens[49].getSprite()->getGlobalBounds().width >= window.getSize().x)
          {
            wall_hit_counter +=1;
            aliens[i *aliens_column +j].moveRight(false);
            aliens[i *aliens_column +j].moveLeft(true);
          }

          if (aliens[0].getSprite()->getPosition().x <= 0)
          {
            wall_hit_counter += 1;
            aliens[i *aliens_column +j].moveRight(true);
            aliens[i *aliens_column +j].moveLeft(false);
          }

          if (aliens[i *aliens_column +j].moveRightBool())
          {
            aliens[i *aliens_column +j].getSprite()->setPosition((aliens[i *aliens_column +j].getSprite()->getPosition().x + 2),
                                                                   20000* (sin(((aliens[i *aliens_column +j].getSprite()->getPosition().x +2)/20))/1000) +65*j +40 +0.5* wall_hit_counter);
          }
          if (aliens[i *aliens_column +j].moveLeftBool())
          {
            aliens[i *aliens_column +j].getSprite()->setPosition((aliens[i *aliens_column +j].getSprite()->getPosition().x - 2),
                                                                   20000* (sin(((aliens[i *aliens_column +j].getSprite()->getPosition().x -2)/20))/1000) +65*j + 40 +0.5* wall_hit_counter);
          }
        }
      }
    }



    //shot movement
    for(int i =0 ; i<3; i++)
    {
      if(shots[i].visibilityBool())
      {
        if(shots[i].moveUpBool())
        {
          shots[i].getSprite()->move(0, shots->getMovingDirection().operator*(-300).y * dt);
          if(shots[i].getSprite()->getPosition().y + shots[i].getSprite()->getGlobalBounds().height < 0)
          {
            shots[i].setVisility(false);
            launched_shots_counter -= 1;
          }
        }
      }
    }


    // Shot-Alien collision check
    for(int j = 0; j < 3 ; j++)
    {
      for (int i = 0; i < aliens_column *aliens_row; i++)
      {
       if(CollisionCheck(*aliens[i].getSprite(), *shots[j].getSprite()))
        {
          if(aliens[i].visibilityBool() && shots[j].visibilityBool())
          {
            score += 2;
            aliens[i].setVisility(false);
            dead_alien_counter += 1;
            shots[j].setVisility(false);
            launched_shots_counter -= 1;
          }
        }
      }
    }

    //aliens-ship collision check
    for(int i =0 ; i<aliens_column *aliens_row ; i++)
    {
      if(aliens[i].visibilityBool())
      {
        if (CollisionCheck(*aliens[i].getSprite(), *ship.getSprite()))
        {
          final_result.setString("Your score is: "+ score_number.str());
          gamestate = GameOver;
        }
      }

    }

    if(selected_mode ==0 || selected_mode ==1|| selected_mode ==3)
    {
      if(dead_alien_counter >= 50)
      {
        final_result.setString("Your score is: "+ score_number.str());
        gamestate = GameWin;
      }
    }
    else if(selected_mode==2)
    {
      if(dead_alien_counter >= 30)
      {
        final_result.setString("Your score is: "+ score_number.str());
        gamestate = GameWin;
      }
    }


  }

  if(gamestate == GameWin)
  {
    if(restart_selected)
    {
      restart_text.setFillColor(sf::Color(255,255,255,255));
      return_menu_text.setFillColor(sf::Color(255,255,255,125));
    }
    else
    {
      restart_text.setFillColor(sf::Color(255,255,255,125));
      return_menu_text.setFillColor(sf::Color(255,255,255,255));
    }
  }

  if(gamestate == GameOver)
  {
    if(restart_selected)
    {
      restart_text.setFillColor(sf::Color(255,255,255,255));
      return_menu_text.setFillColor(sf::Color(255,255,255,125));
    }
    else
    {
      restart_text.setFillColor(sf::Color(255,255,255,125));
      return_menu_text.setFillColor(sf::Color(255,255,255,255));
    }
  }

  if(gamestate == Option)
  {
    if(selected_mode == 0)
    {
      normal_type_text.setFillColor(sf::Color(255,255,255,255));
      gravity_type_text.setFillColor(sf::Color(255,255,255,125));
      curve_type_text.setFillColor(sf::Color(255,255,255,125));
      wave_type_text.setFillColor(sf::Color(255,255,255,125));
    }
    else if(selected_mode == 1)
    {
      normal_type_text.setFillColor(sf::Color(255,255,255,125));
      gravity_type_text.setFillColor(sf::Color(255,255,255,255));
      curve_type_text.setFillColor(sf::Color(255,255,255,125));
      wave_type_text.setFillColor(sf::Color(255,255,255,125));
    }
    else if(selected_mode == 2)
    {
      normal_type_text.setFillColor(sf::Color(255,255,255,125));
      gravity_type_text.setFillColor(sf::Color(255,255,255,125));
      curve_type_text.setFillColor(sf::Color(255,255,255,255));
      wave_type_text.setFillColor(sf::Color(255,255,255,125));
    }
    else if(selected_mode == 3)
    {
      normal_type_text.setFillColor(sf::Color(255,255,255,125));
      gravity_type_text.setFillColor(sf::Color(255,255,255,125));
      curve_type_text.setFillColor(sf::Color(255,255,255,125));
      wave_type_text.setFillColor(sf::Color(255,255,255,255));
    }
  }
}

void Game::render()
{
  if(gamestate == MainMenu)
  {
    window.draw(title_text);
    window.draw(start_text);
  }

  if(gamestate == InGame)
  {

    for (int i = 0; i < aliens_row * aliens_column; i++)
    {
      if(aliens[i].visibilityBool())
      {
        window.draw(*aliens[i].getSprite());
      }
    }
    for(int i =0 ; i < 3; i++)
    {
      if(shots[i].visibilityBool())
      {
        window.draw(*shots[i].getSprite());
      }
    }
    window.draw(*ship.getSprite());
    window.draw(scoreboard);
  }

  if(gamestate == GameWin)
  {
    window.draw(congrats_text);
    window.draw(final_result);
    window.draw(restart_text);
    window.draw(return_menu_text);
  }

  if(gamestate == GameOver)
  {
    window.draw(game_over_text);
    window.draw(final_result);
    window.draw(restart_text);
    window.draw(return_menu_text);
  }

  if(gamestate == Option)
  {
    window.draw(enemy_mode_title);
    window.draw(normal_type_text);
    window.draw(gravity_type_text);
    window.draw(curve_type_text);
    window.draw(wave_type_text);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  if(gamestate == MainMenu)
  {
    if(event.key.code == sf::Keyboard::Space)
    {
      gamestate = Option;
    }
  }

  if(gamestate == InGame)
  {
    if(event.key.code == sf::Keyboard::A)
    {
      ship.moveLeft(true);
    }

    if(event.key.code == sf::Keyboard::D)
    {
      ship.moveRight(true);
    }

    if(event.key.code == sf::Keyboard::Space)
    {
      if (launched_shots_counter < 3 && !shots[current_shot_number].visibilityBool())
      {
        shots[current_shot_number].setVisility(true);
        shots[current_shot_number].getSprite()->setPosition(ship.getSprite()->getPosition().x + ship.getSprite()->getGlobalBounds().width / 2,
                                                            ship.getSprite()->getPosition().y + ship.getSprite()->getGlobalBounds().height / 2);
        shots[current_shot_number].moveUp(true);
        current_shot_number +=1;
        if (current_shot_number == 3)
        {
          current_shot_number = 0;
        }
        launched_shots_counter += 1;
        std::cout << launched_shots_counter;
        score -=1;
      }
    }
  }

  if (gamestate == GameWin)
  {
    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
    {
      restart_selected = !restart_selected;
    }

    if (event.key.code == sf::Keyboard::Enter)
    {
      if(restart_selected)
      {
        Reset();
        gamestate = InGame;
      }
      else
      {
        Reset();
        gamestate = MainMenu;
      }
    }
  }

  if(gamestate == GameOver)
  {
    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
    {
      restart_selected = !restart_selected;
    }

    if (event.key.code == sf::Keyboard::Enter)
    {
      if(restart_selected)
      {
        Reset();
        gamestate = InGame;
      }
      else
      {
        Reset();
        gamestate = MainMenu;
      }
    }
  }

  if(gamestate == Option)
  {
    if(event.key.code == sf::Keyboard::Down)
    {
      selected_mode += 1;
      if(selected_mode > 3)
      {
        selected_mode = 0;
      }
      std::cout << selected_mode;
    }

    else if(event.key.code == sf::Keyboard::Up)
    {
      selected_mode -= 1;
      if(selected_mode <0)
      {
        selected_mode = 3;
      }
      std::cout << selected_mode;
    }

    else if(event.key.code == sf::Keyboard::Enter)
    {
      gamestate = InGame;
      if(selected_mode == 2)
      {
        aliens_column = 3;
      }
      else if(selected_mode!= 2)
      {
        aliens_column = 5;
      }
      Reset();
    }
  }

}

void Game::keyReleased(sf::Event event)
{
  if(gamestate == InGame)
  {
    if(event.key.code == sf::Keyboard::A)
    {
      ship.moveLeft(false);
    }

    if(event.key.code == sf::Keyboard::D)
    {
      ship.moveRight(false);
    }
  }

}

bool Game::CollisionCheck(sf::Sprite sprite1, sf::Sprite sprite2)
{
  if(sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Game::Reset()
{
  //scoreboard and score reset
  score = 0;
  score_number.str();
  score_number << score;
  scoreboard.setString("Score: " + score_number.str());

  //alien reset
  dead_alien_counter = 0;
  wall_hit_counter =0;

  for(int i = 0 ; i < aliens_row; i++)
  {
    for(int j = 0; j < aliens_column; j++)
    {
      aliens[i * aliens_column + j].getSprite()->setPosition( window.getSize().x / 4 - aliens[i].getSprite()->getGlobalBounds().width + 65 * i,
                                                             aliens[i].getSprite()->getGlobalBounds().height /2 + 65 * j);
      aliens[i * aliens_column + j].setVisility(true);
      aliens[i * aliens_column + j].moveRight(true);
      aliens[i * aliens_column + j].moveLeft(false);
    }
  }

  //shots reset
  launched_shots_counter = 0;
  current_shot_number = 0;
  for(int i =0 ; i< 3 ; i++)
  {
    shots[i].setVisility(false);
  }

  //ship reset
  ship.getSprite()->setPosition(window.getSize().x / 2 - ship.getSprite()->getGlobalBounds().width /2 ,
                                window.getSize().y - ship.getSprite()->getGlobalBounds().height *1.5 );
}

void Game::RestartClock()
{
  clock1.restart();
}

void Game::AlienWallCollision()
{
  for (int i = 0; i < aliens_column * aliens_row; i++)
  {
    if (
      aliens[49].getSprite()->getPosition().x +
        aliens[49].getSprite()->getGlobalBounds().width >=
      float(window.getSize().x))
    {
      aliens[i].moveRight(false);
      aliens[i].moveDown(true);

      RestartClock();

      aliens[i].getSprite()->setPosition(
        aliens[i].getSprite()->getPosition().x - 1,
        aliens[i].getSprite()->getPosition().y);
    }

    if (
      float(clock1.getElapsedTime().asSeconds() >= 0.5f) &&
      aliens[i].moveDownBool() &&
      aliens[49].getSprite()->getPosition().x >= window.getSize().x *3/4)
    {
      aliens[i].moveDown(false);
      aliens[i].moveLeft(true);
    }

    if (aliens[0].getSprite()->getPosition().x <= 0)
    {
      for (int i = 0; i < aliens_column * aliens_row; i++)
      {
        aliens[i].moveLeft(false);
        aliens[i].moveDown(true);
      }
      RestartClock();

      for (int i = 0; i < aliens_column * aliens_row; i++)
      {
        aliens[i].getSprite()->setPosition(
          aliens[i].getSprite()->getPosition().x + 1,
          aliens[i].getSprite()->getPosition().y);
      }
    }

    if (
      float(clock1.getElapsedTime().asSeconds() >= 0.5f) &&
      aliens[i].moveDownBool() &&
      aliens[0].getSprite()->getPosition().x <= window.getSize().x / 4)
    {
      for (int i = 0; i < aliens_column * aliens_row; i++)
      {
        aliens[i].moveDown(false);
        aliens[i].moveRight(true);
      }
    }
  }
}




