#include "header_file.h"

Game::Game()
{
    // Initialize member variables here
    score = 0;
    speedMultiplier = 1.0f;
}

void Game::initialize()
{
    // Load resources and set up game objects here
    backgroundTexture.loadFromFile("C:/Users/Lenovo/Desktop/game_p/images/background.png");
    ballTexture.loadFromFile("C:/Users/Lenovo/Desktop/game_p/images/ball.png");
    paddleTexture.loadFromFile("C:/Users/Lenovo/Desktop/game_p/images/paddle.png");
    blockTexture.loadFromFile("C:/Users/Lenovo/Desktop/game_p/images/block03.png");

    backgroundSprite.setTexture(backgroundTexture);

    ballSprite.setTexture(ballTexture);
    ballSprite.setPosition(300, 300);

    paddleSprite.setTexture(paddleTexture);
    paddleSprite.setPosition(300, 440);

    // Initialize blocks
    int n = 0;
       for (int i = 1; i <= 10; i++)
       {
           for (int j = 1; j <= 10; j++)
           {
               blocks[n].setTexture(blockTexture);
               blocks[n].setPosition(i * 43, j * 20);
               n++;
           }
       }
}

void Game::update(sf::RenderWindow& window)
{
    // Update game logic here
    sf::Vector2f ballPosition = ballSprite.getPosition();
    sf::Vector2f paddlePosition = paddleSprite.getPosition();

    // Ball movement logic
    ballPosition.x += dx * speedMultiplier;
    ballPosition.y += dy * speedMultiplier;

    if (ballPosition.x < 0 || ballPosition.x > window.getSize().x)
        dx = -dx;

    if (ballPosition.y < 0)
        dy = -dy;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            paddle.move(paddleSpeed, 0);
            if (paddle.getPosition().x +
                    paddle_Width > windowWidth)
                paddle.setPosition(windowWidth - paddle_Width, paddle.getPosition().y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            paddle.move(-paddleSpeed, 0);
            if (paddle.getPosition().x < 0)
                paddle.setPosition(0, paddle.getPosition().y);
        }
    if (ballPosition.y > window.getSize().y)
    {
        // Ball hit the bottom, game over logic
        gameOver();
        return;
    }

    if (ballPosition.y + BALL_RADIUS >= paddlePosition.y && ballPosition.y + BALL_RADIUS <= paddlePosition.y + PADDLE_HEIGHT
        && ballPosition.x + BALL_RADIUS >= paddlePosition.x && ballPosition.x + BALL_RADIUS <= paddlePosition.x + paddle_Width)
    {
        // Ball hit the paddle logic
        dy = -dy;
    }

    // Check collision with blocks
    for (int i = 0; i < MAX_BLOCKS; i++)
    {
        if (blocks[i].getGlobalBounds().intersects(ballSprite.getGlobalBounds()))
        {
            // Ball hit a block logic
            blocks[i].setPosition(-100, 0); // Hide the block

            // Increase score
            score += SCORE_INCREMENT;

            // Increase ball speed
            speedMultiplier += SPEED_INCREASE;
        }
    }

    ballSprite.setPosition(ballPosition);
}

void Game::draw(sf::RenderWindow& window)
{
    // Draw game objects here
    window.clear();
    window.draw(backgroundSprite);
    window.draw(ballSprite);
    window.draw(paddleSprite);

    for (int i = 0; i < MAX_BLOCKS; i++)
        {
            if (blocks[i].getPosition().x != -100 && blocks[i].getPosition().y != 0)
            {
                window.draw(blocks[i]);
            }
        }

    window.display();
}

void Game::gameOver()
{
    // Game over logic here
    // Display score and time survived
}
