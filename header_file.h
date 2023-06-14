#pragma once

#include <SFML/Graphics.hpp>

#define MAX_BLOCKS 1000
#define BALL_RADIUS 6
#define paddle_Width 64
#define PADDLE_HEIGHT 16
#define SCORE_INCREMENT 10
#define SPEED_INCREASE 0.1f

class Game
{
public:
    Game();

    void initialize();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void gameOver();

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture ballTexture;
    sf::Sprite ballSprite;

    sf::Texture paddleTexture;
    sf::Sprite paddleSprite;

    sf::Texture blockTexture;
    sf::Sprite blocks[MAX_BLOCKS];

    sf::RenderWindow window;

       sf::Sprite paddle;
       sf::Sprite ball;
       const int windowWidth = 520;
           const int windowHeight = 450;
           const int paddleSpeed = 6;


    float dx = 6, dy = 5;
    float speedMultiplier;

    int score;
};

