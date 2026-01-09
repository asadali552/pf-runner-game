# pf-runner-game
2D Runner Game built in C++ using OpenGL

🎮 PF Runner Game (C++ OpenGL)

A fast-paced 2D runner game built in C++ using OpenGL (GLUT) as part of a Programming Fundamentals (PF) project.
The player controls a flying character, dodges obstacles, collects coins, and survives against an AI enemy while the game speed increases over time.

## Academic Context

This project was developed as a **Programming Fundamentals (PF) final project at FAST-NUCES**.

The OpenGL / GLUT framework and utility files (`util.h`, `util.cpp`, `game-release.h`) were provided by the course instructors as a graphics framework.  
All game logic, movement, collision detection, scoring, AI behavior, and gameplay code was written by the student.

No AI code generators or external code sources were used in the development of this project, in compliance with FAST-NUCES academic integrity and plagiarism policies.


🧩 Game Features

🚀 Player-controlled flying character

🧱 Randomly generated falling obstacles

🪙 Coin (Bitcoin) collection system

🤖 AI enemy that chases the player

❤️ Life system (3 lives)

📈 Distance & score tracking

⏸ Pause & Resume functionality

🎮 Keyboard controls

🖥 Smooth OpenGL rendering

🎯 Objective

Survive as long as possible while:

Avoiding obstacles

Collecting coins

Escaping the AI enemy

Maximizing distance and score

The longer you survive, the harder the game becomes.

🎮 Controls
Key	Action
⬅ Left Arrow	Move left
➡ Right Arrow	Move right
⬆ Up Arrow	Move up
⬇ Down Arrow	Move down
P	Pause the game
R	Resume / Restart
ESC	Exit game
🧠 Game Mechanics
Player

The player moves between three vertical lanes and can move up or down to avoid obstacles and reach coins.

Obstacles

Obstacles fall from the top of the screen.
If the player collides with an obstacle, one life is lost.

Coins

Coins appear randomly in lanes.
Collecting a coin increases the score by 10 points.

AI Enemy

After a certain distance, a red AI enemy spawns and actively chases the player.
Collision with the AI also reduces a life.

Difficulty Scaling

As distance increases:

Obstacles fall faster

The game becomes more difficult

🛠 Built With

C++

OpenGL (GLUT)

PF Game Utility Framework (util.h)

▶ How to Run

Make sure OpenGL and GLUT are installed

Compile using:

g++ TETRIS.cpp util.cpp -lglut -lGL -lGLU -o game


Run:

./game

📁 Project Files

TETRIS.cpp – Main game logic

util.h / util.cpp – Graphics & drawing utilities

game-release.h – Game framework

📌 Academic Purpose

This project was created as part of the Programming Fundamentals (PF) course to demonstrate:

Game loops

Collision detection

Real-time graphics

Keyboard input

Basic AI behavior

👤 Author

Asad Ali
FAST NUCES — Software Engineering
