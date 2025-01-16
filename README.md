Pong Game with Raylib - Live Demo : https://www.youtube.com/watch?v=bVwlE0WVMVg

A modern take on the classic Pong game built using Raylib.

Features
Play against an AI opponent.
Retro-inspired design with custom colors.
Live score tracking and smooth paddle movement.

How to Play
Player Controls:
UP Arrow: Move paddle up.
DOWN Arrow: Move paddle down.
The first player to reach the target score wins!

How to Run

Clone the repository:
git clone https://github.com/jlin1599/pong_game.git

Install Dependencies (if necessary):
If you're on Linux (Ubuntu), you can install Raylib with:
sudo apt-get install libraylib-dev

Build the game:
g++ -o pong main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

Run the game:
./pong

Customization
Edit the main.cpp file to:

Change colors.
Adjust paddle and ball speeds.
Modify screen dimensions.


