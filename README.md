# Arkanoid Game using SFML

This repository contains an Arkanoid game implemented using SFML (Simple and Fast Multimedia Library). The game is developed as part of our IT class project.

## Game Description

Arkanoid is a classic arcade game where the player controls a paddle at the bottom of the screen and tries to break all the bricks at the top using a bouncing ball. The player must prevent the ball from falling off the bottom of the screen by moving the paddle left and right. Each time a brick is hit, it gets destroyed, and the player earns points. The goal is to clear all the bricks on the screen and achieve the highest score possible.

## Technologies Used

- C++: The game is implemented in C++ programming language.
- SFML: Simple and Fast Multimedia Library (SFML) is used for graphics, audio, and input handling.
- Docker: Docker is used for containerization.

## Features

- Interactive gameplay with paddle and bouncing ball.
- Multiple levels with increasing difficulty.
- Power-ups and bonuses to enhance gameplay.
- High score tracking and display.
- Sound effects and background music.

## Getting Started

These instructions will help you get a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- C++ compiler
- SFML library
- Docker: Make sure you have Docker installed on your machine.

### Installation

 -- Clone the repository to your local machine using the following command:git clone https://github.com/Younes-boutelidjane/arkanoid-game.git 
- Install the necessary dependencies, including the SFML library.
- Build the project using your preferred C++ compiler. Make sure to link the SFML libraries properly.
- Run the executable file generated after the build.
# Or:
- Build the Docker image using the provided Dockerfile: sudo docker build -t myproject .
- Run the Docker container: sudo docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix myproject
  

## Contributing

Contributions to this project are welcome. If you have any ideas, suggestions, or bug fixes, please open an issue or submit a pull request.


## Acknowledgments

- The project is developed as part of our IT class and inspired by the classic Arkanoid game.
- We would like to express our gratitude to the creators and contributors of the SFML library for providing a powerful and user-friendly multimedia framework.



