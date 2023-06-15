#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include "Game.h"

using namespace sf;

int main()
{
    int m = 100;
    int score = 10;
    bool blocksMovingRight = true;
    float blockSpeed = 2.0f;
    int triangularTimer = 500; // Time in milliseconds for triangular block appearance
    int triangularDisappearTime = 3000; // Time in milliseconds for triangular block disappearance
    int triangularMovementDistance = 20; // Distance in pixels for triangular block movement
    int maxBlocks = 6; // Maximum number of blocks appearing on the screen

    srand(time(0));

    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("audio/endm.wav"))
    {
        // Error handling if the audio file fails to load
        std::cout << "Could not load the audio" << std::endl;
    }
    sf::Music endm;
    if (!endm.openFromFile("audio/endm.wav"))
    {
        // Handle error loading the sound
        std::cout << "Could not load the audio" << std::endl;
    }
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("audio/gameplay.wav"))
    {
        // Handle error loading the sound
        std::cout << "Could not load the audio" << std::endl;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
    sf::Music win;
    if (!win.openFromFile("audio/win.wav"))
    {
        // Handle error loading the sound
        std::cout << "Could not load the audio" << std::endl;
    }

    Font font;
    if (!font.loadFromFile("fonts/PressStart2P-Regular.ttf"))
    {
        // Error handling if the font fails to load

        std::cout << "Could not load the font" << std::endl;
    }

    // Create text objects
    Text text;
    text.setFont(font);
    text.setCharacterSize(28);
    text.setFillColor(Color::Black);
    text.setPosition(100, 200);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);

    // Create a clock for time calculations

    Clock clock;
        Clock scoreTimer; // Timer for score decrement

    Texture t1, t2, t3, t4;
    t1.loadFromFile("images/block02.png");
    t2.loadFromFile("images/background.png");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(300, 440);

    Sprite block[1000];

    int n = 0;
    for (int i = 2; i <= 6; i = i + 3)
    {
        for (int j = 2; j <= 6; j = j + 2)
        {
            block[n].setTexture(t1);
            block[n].setPosition(i * 43, j * 25);
            n++;
        }
    }
    std::cout << "The number of blocks is: " << n << std::endl;

    float dx = 6, dy = 5;
    float x = 300, y = 300;

    bool ballMoving = true;
    bool gameOver = false;
    bool triangularVisible = false;
    int triangularTimerCounter = triangularTimer;
    Clock triangularClock;
    int remainingBlocks = maxBlocks;

    while (app.isOpen())
    {
        sf::Time dt = clock.restart();

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
            else if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Space && gameOver)
                {
                    // Reset the game if spacebar is pressed and game over
                    ballMoving = true;
                    gameOver = false;
                    text.setString("");
                    backgroundMusic.play();
                    score = 0;
                    remainingBlocks = maxBlocks;

                }
            }
        }

        if (ballMoving)
        {
            if (y > 450 ||score==0)
                   {
                       // Ball hit the bottom
                       ballMoving = false;
                       gameOver = true;
                       text.setString("You lost! ");
                        endm.play();
                       backgroundMusic.stop();
                   }



            if (scoreTimer.getElapsedTime().asSeconds() >= 4.0f)
                        {
                            score -= 1;
                            scoreTimer.restart();
                        }

            x += dx;
            for (int i = 0; i < n; i++)

            {
                if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
                {
                    block[i].setPosition(-999, 999);
                    dx = -dx;

                    // Update score when a block is hit
                    score += 1;

                    // Count the remaining blocks

                    remainingBlocks--;

                    std::cout << "Remaining blocks: " << remainingBlocks << std::endl;
                }
            }

            y += dy;
            for (int i = 0; i < n; i++)
            {
                // Move the blocks right
                if (blocksMovingRight)
                {
                    block[i].move(blockSpeed, 0);
                    // Check if the block has reached the right edge of the screen
                    if (block[i].getPosition().x + block[i].getGlobalBounds().width > app.getSize().x)
                    {
                        blocksMovingRight = false; // Change direction to left
                        block[i].move(-blockSpeed, 0); // Move the block back to avoid going out of the screen
                    }
                }
                // Move the blocks left
                else
                {
                    block[i].move(-blockSpeed, 0);
                    // Check if the block has reached the left edge of the screen
                    if (block[i].getPosition().x < 0)
                    {
                        blocksMovingRight = true; // Change direction to right
                        block[i].move(blockSpeed, 0); // Move the block back to avoid going out of the screen
                    }
                }
            }

            if (x < 0 || x > 520)
                dx = -dx;
            if (y < 0 || y > 450)
                dy = -dy;

            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                if (sPaddle.getPosition().x + sPaddle.getLocalBounds().width < app.getSize().x)
                    sPaddle.move(7, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                if (sPaddle.getPosition().x > 0)
                    sPaddle.move(-7, 0);
            }

            // Triangular Block Handling
            if (triangularVisible)
            {
                // Check collision with triangular block
                if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds()))
                {
                    dy = -(rand() % 5 + 2);
                    triangularVisible = false;
                    triangularTimerCounter = triangularTimer;


                }
                else if (triangularClock.getElapsedTime().asMilliseconds() > triangularDisappearTime)
                {
                    // Triangular block disappeared without being hit
                    triangularVisible = false;
                    triangularTimerCounter = triangularTimer;

                    // Reduce score when triangular block disappears
                    score=score-1;

                    std::cout << "Score: " << score << std::endl;
                }
                else
                {
                    // Move the triangular block left and right
                    if (blocksMovingRight)
                    {
                        sPaddle.move(triangularMovementDistance * dt.asSeconds(), 0);
                        if (sPaddle.getPosition().x + sPaddle.getLocalBounds().width > app.getSize().x)
                        {
                            blocksMovingRight = false; // Change direction to left
                            sPaddle.move(-triangularMovementDistance * dt.asSeconds(), 0);
                        }
                    }
                    else
                    {
                        sPaddle.move(-triangularMovementDistance * dt.asSeconds(), 0);
                        if (sPaddle.getPosition().x < 0)
                        {
                            blocksMovingRight = true; // Change direction to right
                            sPaddle.move(triangularMovementDistance * dt.asSeconds(), 0);
                        }
                    }
                }
            }
            else
            {
                // Check if it's time to show the triangular block
                if (triangularTimerCounter <= 0)
                {
                    triangularVisible = true;
                    triangularClock.restart();
                    triangularTimerCounter = triangularTimer;
                }
                else
                {
                    triangularTimerCounter -= dt.asMilliseconds();
                }
            }

            // Check if the player lost all points
            if (score <= 0)
            {
                gameOver = true;
                ballMoving = false;
                text.setString("Game Over! Press Space to Restart");
                text.setPosition(70, 200);
                backgroundMusic.stop();
                endm.play();
                if (e.key.code == Keyboard::Space && gameOver)
                {
                    // Reset the game if spacebar is pressed and game over
                    ballMoving = true;
                    gameOver = false;
                    text.setString("");
                    backgroundMusic.play();
                    score = 0;
                    remainingBlocks = maxBlocks;

                }
            }

            // Check if the player destroyed all the blocks
            if (remainingBlocks <= 0)
            {
                gameOver = true;
                ballMoving = false;
                text.setString("You Won!");
                text.setPosition(120, 200);
                backgroundMusic.stop();
                win.play();

            }

            if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds()))
                dy = -(rand() % 5 + 2);

            sBall.setPosition(x, y);

            // Draw everything
            app.clear();
            app.draw(sBackground);
            app.draw(sBall);
            app.draw(sPaddle);
            for (int i = 0; i < n; i++)
                app.draw(block[i]);
            app.draw(text);
            scoreText.setString("Score: " + std::to_string(score));
            app.draw(scoreText);

            app.display();
        }
    }
    

    return 0;
}
