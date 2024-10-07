# Details about repository
This repository contains a project for a hardware-based Tic-Tac-Toe 3x3 game using ESP8266 and C++. The game logic and decision-making will run primarily on the ESP8266, while the C++ Qt application will serve as a graphical interface for user to interact with game.


# Task details
## Task 1
Main goals to this task is to create repository with main branch **develop**. Then create branch with name **feature/develop/task1** and create `README.md` file with all descriptions. Also create **TAG** and make pull request.

 ## Student details
| Student number | Game | Config format |
| :-----------: | :-------------: | :-----------: |
| 17 | Tic-Tac-Toe 3x3 | JSON |

## Technology Stack and Hardware

### Hardware
- **ESP8266**: The ESP8266 board will handle the game logic, including managing inputs, processing the current game state and sending data to the client desktop C++ Qt application.

### Software
- **Qt Framework**: Used for creating desktop application with graphical user interface (GUI) that displays the game board and allows user to view the game progress in real time.
- **Platformio**: This multiple framework tool used for developing firmware for ESP8266 microcontroller. The code is written in C/C++.

### Programming Languages
- **C/C++**: Used for developing firmware and desktop application.

### Communication
- **Serial Communication**: The microcontroller will communicate with desktop client app through an UART interface to send game status and receive user input.
