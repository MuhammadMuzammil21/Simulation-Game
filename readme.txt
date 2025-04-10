$$$$$$$$\ $$\                 $$\ $$\ $$\        $$$$$$\   $$$$$$\        $$$$$$$\                      $$\           $$\                     
\__$$  __|$$ |                \__|$$ |$$ |      $$  __$$\ $$  __$$\       $$  __$$\                     \__|          \__|                    
   $$ |   $$$$$$$\   $$$$$$\  $$\ $$ |$$ |      $$ /  $$ |$$ /  \__|      $$ |  $$ | $$$$$$\   $$$$$$$\ $$\  $$$$$$$\ $$\  $$$$$$\  $$$$$$$\  
   $$ |   $$  __$$\ $$  __$$\ $$ |$$ |$$ |      $$ |  $$ |$$$$\           $$ |  $$ |$$  __$$\ $$  _____|$$ |$$  _____|$$ |$$  __$$\ $$  __$$\ 
   $$ |   $$ |  $$ |$$ |  \__|$$ |$$ |$$ |      $$ |  $$ |$$  _|          $$ |  $$ |$$$$$$$$ |$$ /      $$ |\$$$$$$\  $$ |$$ /  $$ |$$ |  $$ |
   $$ |   $$ |  $$ |$$ |      $$ |$$ |$$ |      $$ |  $$ |$$ |            $$ |  $$ |$$   ____|$$ |      $$ | \____$$\ $$ |$$ |  $$ |$$ |  $$ |
   $$ |   $$ |  $$ |$$ |      $$ |$$ |$$ |       $$$$$$  |$$ |            $$$$$$$  |\$$$$$$$\ \$$$$$$$\ $$ |$$$$$$$  |$$ |\$$$$$$  |$$ |  $$ |
   \__|   \__|  \__|\__|      \__|\__|\__|       \______/ \__|            \_______/  \_______| \_______|\__|\_______/ \__| \______/ \__|  \__|

Thrill Of Decision - A branched decision-based game developed in C++ and SFML GUI framework.





SFML OOP PROJECT
Contains: 
1. The main GUI Simulation game COMPILED
2. The main GUI Simulation game main.cpp inside the Visual Studio solution
3. The project report
4. The class diagram
5. The initial console simulation game



 __ ___  ___ ____    ___   ____  ______  ___  __  __ ______      ___   ___   __  __ ______ ____    ___   __     __ 
 || ||\\//|| || \\  // \\  || \\ | || | // \\ ||\ || | || |     //    // \\  ||\ || | || | || \\  // \\  ||    (( \
 || || \/ || ||_// ((   )) ||_//   ||   ||=|| ||\\||   ||      ((    ((   )) ||\\||   ||   ||_// ((   )) ||     \\ 
 || ||    || ||     \\_//  || \\   ||   || || || \||   ||       \\__  \\_//  || \||   ||   || \\  \\_//  ||__| \_))

//	Left-click: 	use to skip story printing.
//
//	Right-click on minesweeper: used to flag mines.
//
//	Make the right choice...

Dependencies
The "Story" class has dependencies on the following classes:

Player
GridGame
Minesweeper
DoorGame
Class Members
Player p: an object of the Player class that stores the player's information, such as name, age, checkpoint, MI6 code, and health.
GridGame g: an object of the GridGame class that is used to play the grid game.
Minesweeper m: an object of the Minesweeper class that is used to play the minesweeper game.
DoorGame d: an object of the DoorGame class that is used to play the door game.
int ch: an integer that is used to store the user's choice.
int answer: an integer that is used to store the answer to a question.
string str: a string that is used to store a message or a question.
Member Functions
Story(): a constructor that sets the vertical sync to true.
int save(char x): a member function that asks the user if they want to save the game or continue playing. It then saves the player's checkpoint and information to a file.
void filing(): a member function that creates a file and saves the player's information to the file.
int reading(): a member function that reads the player's information from a file.
void showPic(const char* fileName): a member function that displays a picture in the game window.
void mainMenu(): a member function that displays the game's main menu and asks the user if they want to start a new game or load a saved game.
void newGame(): a member function that starts a new game and progresses through the story. It asks the user to play the door game, and depending on their choice, it progresses through the positive or negative story arc.
void loadGame(): a member function that loads a saved game and continues from the player's last checkpoint.
void storyInitial(): a member function that displays the initial story of the game.
void storyPositive(): a member function that displays the positive story arc of the game.
void storyPositiveEnd(): a member function that displays the end of the positive story arc.
void storyNeagtive(): a member function that displays the negative story arc of the game.
void storyNeagtiveEnd(): a member function that displays the end of the negative story arc.
void endcredits(): a member function that displays the game's end credits.
Controls

Conclusion
This README file explained the different member functions of the "Story" class and how they work. The "Story" class is an important class in the game as it handles the story and the gameplay. It is recommended to read this README file before playing the game to understand how the game works and how to progress through the story.