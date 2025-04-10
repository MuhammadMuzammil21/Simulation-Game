#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SpookyOutput.hpp"
using namespace std;

class DoorGame: public Game
{
private:
    int correctDoor;
    int trapDoor;

public:
    DoorGame()
    {
        srand(time(NULL));
        correctDoor = rand() % 2 + 1;
        trapDoor = (correctDoor == 1) ? 2 : 1;
    }

    int play()
    {
        int chosenDoor;
        system("cls");
        sout << "Welcome to The Door game!";
        sout << "You are presented with two doors: Door 1 and Door 2.";
        sout << "Behind each door lies how I move forward reminding you of who you are. CHOOSE WISELY!!.";

        while (true)
        {
            cout << "Choose a door (1 or 2): ";
            cin >> chosenDoor;

            if (chosenDoor == 1 || chosenDoor == 2)
            {
                break;
            }
            sout << "Invalid input. Please choose either Door 1 or Door 2.";
        }
		
		system("cls");
        if (chosenDoor == correctDoor)
        {
            sout << "Lets move Foward.. We'll know how this choice effects you..";
            return 1;
        }
        else if (chosenDoor == trapDoor)
        {
            sout << "Lets move Foward.. We'll know how this choice effects you..";
            return 0;
        }
        return 2;
    }
};
