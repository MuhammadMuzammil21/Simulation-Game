# Simulation Game: Thrill of Decision – The Laptop Adventure

A branching narrative simulation game built using **C++** and **SFML**. In this interactive adventure, your decisions determine the outcome of the story as you navigate through various mini-games and challenges. With stunning graphics, engaging sound design, and multiple gameplay modes, every playthrough is unique.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
  - [Directory Layout](#directory-layout)
  - [Class Diagram](#class-diagram)
- [Installation & Setup](#installation--setup)
- [Compilation & Running](#compilation--running)
- [How to Play](#how-to-play)
- [Assets](#assets)
- [Credits](#credits)
- [License](#license)

---

## Overview

**Simulation Game** (also known as *Thrill of Decision – The Laptop Adventure*) is a story-driven simulation where every decision matters. Using SFML and object-oriented principles in C++, the project presents the player with a series of challenges—from choosing between doors to solving grid-based puzzles and even a Minesweeper-like challenge—all integrated into one evolving narrative.

The game starts with a mysterious story displayed through an animated GUI, background music, and interactive menus. The storyline unfolds based on the player's choices and performance in various mini-games, ultimately testing both wit and courage.

---

## Features

- **Branching Narrative:** Your choices drive the story forward. Each decision, no matter how small, affects the outcome.
- **Multiple Game Modes:**
  - **Door Game:** Choose one of two doors to reveal your fate.  
    (File: [DoorGame.h](./GUI%20Visual%20Studio%202022%20Solution/DoorGame.h))
  - **Grid Game:** A pattern-matching challenge testing your memory and reaction.  
    (File: [GridGame.h](./GUI%20Visual%20Studio%202022%20Solution/GridGame.h))
  - **Minesweeper Challenge:** A twist on the classic puzzle where wrong moves cost you health.  
    (File: [Minesweeper.h](./GUI%20Visual%20Studio%202022%20Solution/Minesweeper.h))
- **Interactive GUI:** Custom buttons, text input, and animations make for a responsive, engaging interface.  
  (Files: [Button.h](./GUI%20Visual%20Studio%202022%20Solution/Button.h), [Inputer.h](./GUI%20Visual%20Studio%202022%20Solution/Inputer.h))
- **Save & Load System:** Progress is saved to a file so that you can resume your adventure later.
- **Rich Storytelling:** The story is complemented by atmospheric sound, smooth transitions, and dynamic visual effects.
- **SFML-Powered:** Leverages the SFML library for multimedia functions, providing cross-platform compatibility.

---

## Project Structure

### Directory Layout

Below is an example screenshot of the folder structure and solution layout:

![Project Structure](./image.png)

<details>
  <summary>High-Level Directory Tree</summary>

```
.
├── Initial Console Version/
├── Thrill Of Decision/
├── GUI Visual Studio 2022 Solution/
│   ├── abstractClass.h
│   ├── Button.h
│   ├── DoorGame.h
│   ├── GridGame.h
│   ├── GridOfButtons.h
│   ├── Inputer.h
│   ├── main.cpp
│   ├── Minesweeper.h
│   ├── Player&Story.h
│   ├── ProjectIncludes.h
│   └── ...
├── Class Diagram.jpg
├── .gitignore
└── README.md
```
</details>

### Class Diagram

For an architectural overview of the classes and their relationships, see the diagram below. It captures how the `Game` abstract class, story components, and GUI elements interconnect:

![Class Diagram](./Class%20Diagram.jpg)

*(Make sure `Class Diagram.jpg` is placed in the same folder as this README or adjust the path accordingly.)*

---

## Installation & Setup

### Prerequisites

- **Operating System:** Windows (compatible with other OSes with SFML support)
- **Compiler:** Visual Studio 2022
- **Libraries:**  
  - [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/)  
    Recommended version: SFML 2.5.1 or later  
- **Assets:** Ensure that the `assets` folder containing images, fonts, and audio (e.g., `assets/icon.png`, `assets/main menu music.ogg`, `assets/gunShot.ogg`, etc.) is in the project directory.

### Setting Up in Visual Studio 2022

1. **Clone the Repository:**  
   ```bash
   git clone https://github.com/MuhammadMuzammil21/Simulation-Game.git
   ```
2. **Open the Project:**  
   Open the `.sln` file located in the `GUI Visual Studio 2022 Solution` folder using Visual Studio 2022.
3. **Configure SFML:**  
   - Download and install the SFML library.
   - Configure your project properties (include directories, library directories, linker input) to point to the SFML headers and libraries.
   - Ensure the SFML DLLs are copied to your executable directory or added to your system path.

---

## Compilation & Running

1. **Compile the Project:**  
   Build the solution in Visual Studio 2022 (using either Debug or Release mode).
2. **Run the Executable:**  
   After compilation, run the generated executable. Make sure the `assets` folder is in the same directory as the executable.
3. **Troubleshooting:**  
   - If you experience runtime errors related to missing DLLs, double-check that the SFML DLLs are accessible.
   - Ensure that file paths for assets (images, fonts, and audio) are correct relative to the executable.

---

## How to Play
(You can play the compiled version on windows [here](/Thrill%20Of%20Decision/SFML%20OOP%20Project.exe))
- **Starting the Game:**  
  When the game starts, you'll be greeted with a title screen and introductory story text. Follow the on-screen prompts to enter your name and age.
- **Main Menu:**  
  - **New Game:** Begin a fresh adventure.  
  - **Load Game:** Resume from a previous save.
- **Mini-Games & Challenges:**  
  - **Door Game:** Choose between two doors using mouse input. Your choice unlocks a new branch in the storyline.
  - **Grid Game:** Follow a pattern displayed on a grid. Accurately replicate the pattern to progress.
  - **Minesweeper:** A variant of the classic game is presented where incorrect moves reduce your health.
- **Decision Making:**  
  The narrative unfolds based on your correct answers and decisions. Poor choices may reduce your health or lead to a shorter adventure.
- **Saving & Loading:**  
  You can save your progress at checkpoints. Saved files are created using your name (e.g., `YourName.txt`).

---

## Assets

All assets (images, fonts, audio) are located in the `assets` folder. These include:

- **Images:**  
  - Door images (e.g., `redDoor.png`, `blueDoor.png`)
  - Game backgrounds and story illustrations (e.g., `Laptop on desk.jpeg`, `andrew.jpg`, `two.jpg`, `threeGuys.jpg`)
- **Audio:**  
  - Background music and sound effects (e.g., `main menu music.ogg`, `gunShot.ogg`)
- **Fonts:**  
  - Custom fonts used for menu text, story narration, and in-game interfaces (e.g., `Monorama-Medium.otf`, `Phage Rough.otf`, `SummerPixel.ttf`, `PrinceOutfitDemo.ttf`)

---

## Credits

Special thanks to the legendary contributors whose names appear within the game:
  
- Asim Majeed  
- Heo Juseong  
- Muhammad Muzammil  

(See credits in the end credits sequence of the game.)

---

## License

This project is open-source and available under the [MIT License](LICENSE). Please refer to the LICENSE file for more information.

---

Enjoy shaping the adventure with every decision you make, and remember—your choices truly matter in *Thrill of Decision: The Laptop Adventure*!