#include "Game.h"
#include <iostream>
#include <sstream>
Game::Game()
{
    // Initialize member variables here
    score = 0;
    speedMultiplier = 1.0f;
}

void Game::initialize()
{
    // Load resources and set up game objects here
    backgroundTexture.loadFromFile("images/background.png");
    ballTexture.loadFromFile("images/ball.png");
    paddleTexture.loadFromFile("images/paddle.png");
    blockTexture.loadFromFile("images/block03.png");

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

// void Game::gameOver()
// {
//     // Game over logic here
//     // Display score and time survived
// }
void Game::gameOver()
{
    // Clear the window
    window.clear();

    // Create and configure a text object to display the score and time survived
    sf::Text gameOverText;
    sf:: Font font;
     if (!font.loadFromFile("fonts/PressStart2P-Regular.ttf"))
    {
        // Error handling if the font fails to load

        std::cout << "Could not load the font" << std::endl;
    }
    gameOverText.setFont(font); // 'font' is assumed to be the font you are using
    gameOverText.setCharacterSize(24);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(10.0f, 10.0f);

    // Construct the game over message using score and time survived
    std::ostringstream oss;
    oss << "Game Over!\n";
    oss << "Score: " << score << "\n";
    oss << "Time Survived: " << timer.getElapsedTime().asSeconds() << " seconds";
    gameOverText.setString(oss.str());

    // Draw the game over message to the window
    window.draw(gameOverText);

    // Display the window contents
    window.display();

    // Wait for a short duration to allow the player to see the game over screen
    sf::sleep(sf::seconds(3.0f));

    // Reset the game state to play again
    resetGameState();
}

