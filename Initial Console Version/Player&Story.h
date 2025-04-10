#include <iostream>
#include <fstream>
#include <windows.h>
#include "Abstractclass.h"
#include "Gridgame.h"
#include "Minesweeper.h"
#include "Doorgame.h"
#include "SpookyOutput.hpp"
using namespace std;

class Player {
public:
	string name;
    int age;
	char Checkpoint;
    string MI6code;
    int health;
    Player() {
        this->health = 3;
    }
    void getInfo();
};

void Player::getInfo() {
    cout << "Enter your name: ";
    cin >> name;
    system("cls");
    cout << "Enter your age: ";
    cin >> age;
    system("cls");
    MI6code = name[0] + to_string(age+11);
}

class Story {
    Player p;
    GridGame g;
    Minesweeper m;
    DoorGame d;
    int ch;
    int answer;
    string str;
public:
    void mainMenu();
    void newGame();
    void loadGame();
    
    void storyInitial();
    void storyPositive();
    void storyPositiveEnd();
    void storyNeagtive();
    void storyNeagtiveEnd();
    int save(char x);
    void filing();
    int reading();
};

int Story::save(char x){
	system("cls");
	cout << "Do you want to save or continue the game?" << endl;
	cout << "1. Save and Exit" << endl;
	cout << "2. Continue" << endl;
	cin >> ch;
	system("cls");
	switch(ch){
		case 1:
			sout << "Saving . . .";
			p.Checkpoint = x; 
			filing();
			return 1;
			break;
		case 2:
			sout << "Continue . . .";
			break;
	}
	return 0;
}

void Story::filing(){
	string fname;
	fname = p.name + ".txt";
	fstream f(fname, ios::trunc | ios::out);
	f.write((char*)&p, sizeof(Player));
	system("cls");
	sout << "filing . . .";
	f.close();
}

int Story::reading(){
	string fname;
	fname = p.name + ".txt";
	fstream g(fname, ios::in);
	g.seekg(0);
	g.read((char*)&p, sizeof(Player));
	if (!g){
		system("cls");
		cout << "Loaded game not found." << endl;
		return 1;
	}
	system("cls");
	sout << "reading . . .";
	//cout << p.name << endl << p.age << endl << p.Checkpoint << endl << p.MI6code << endl << p.health << endl;
	g.close();
	return 0;
}

void Story::mainMenu() {
    cout << "    __________________________________________________________________________________________________________________________" << endl;
    cout << "    |                                                                                                                        |" << endl;
    cout << "    |                                        Thrill of Decision: The Laptop Adventure                                        |" << endl;
    cout << "    |                                                         DEMO                                                           |" << endl;
    cout << "    |                                                                                                                        |" << endl;
    cout << "    |                                                                                                                        |" << endl;
    cout << "    |                                                                                                                        |" << endl;
    cout << "    |                                                       MAIN MENU                                                        |" << endl;
    cout << "    |                                                                                                                        |" << endl;
    cout << "    |                                                   1.  NEW GAME                                                         |" << endl;
    cout << "    |                                                   2.  LOAD GAME                                                        |" << endl;
    cout << "    |                                                   3.    EXIT                                                           |" << endl;
    cout << "    |________________________________________________________________________________________________________________________|" << endl;
    cin >> ch;
    
    switch (ch) {
    case 1:
        newGame();
        break;
    case 2:
        loadGame();
        break;
    case 3:
        //Exit
        break;
    }
    
}

void Story::newGame() {  
    system("cls");
	int check = 0;
    storyInitial();
	if (save('i') == 1){
		return;
	}
    //Door Game
    ch = d.play();
    switch(ch){
    	case 1:
	    	//POSITIVE DIRECTION
		    storyPositive();
		    if (save('p') == 1){
				return;
			}
		    while(p.health > 0){
		    	ch = g.play();
		    	if (ch == 1){
		    		check = 1;
		    		break;
				}
				else {
					system("cls");
					p.health--;
					cout << "Remaining Health: " << p.health << endl;
					if (save('g') == 1){
						return;
					}
					Sleep(3000);
				}
			}
			if (check == 0){
				system("cls");
				sout << "You disappointed me.....";
				system("cls");
				sout << "FIN";
				return;
			}
		    storyPositiveEnd();
		    break;
	    case 0:
	    	//NEGATIVE DIRECTION
		    storyNeagtive();
		    if (save('m') == 1){
				return;
			}
		    while(p.health > 0){
		    	ch = m.play();
		    	if (ch == 1){
		    		check = 1;
		    		break;
				}
				else {
					system("cls");
					p.health--;
					cout << "Remaining Health: " << p.health << endl;
					if (save('m') == 1){
						return;
					}
					Sleep(3000);
				}
			}
			if (check == 0){
				system("cls");
				sout << "\"You disappointed me.....\"";
				system("cls");
				sout << "FIN";
				return;
			}
		    storyNeagtiveEnd();
		    break;
	}
}

void Story::loadGame() {
	system("cls");
	int check = 0;
	cout << "Enter your name of loaded game: ";
	cin >> p.name;
	if (reading() == 1){
		return;
	}
	system("cls");
	switch(p.Checkpoint){
		case 'i':
			goto DOORGAME;
			break;
		case 'p':
			goto POSITIVE;
			break;
		case 'n':
			goto NEGATIVE;
			break;
		case 'g':
			goto GRIDGAME;
			break;
		case 'm':
			goto MINESWEEPER;
			break;
	}
	
    storyInitial();
	if (save('i') == 1){
		return;
	}
	
    //Door Game
    DOORGAME:
    ch = d.play();
    switch(ch){
    	case 1:
	    	//POSITIVE DIRECTION
		    storyPositive();
		    if (save('g') == 1){
				return;
			}
			GRIDGAME:
		    while(p.health > 0){
		    	ch = g.play();
		    	if (ch == 1){
		    		check = 1;
		    		break;
				}
				else {
					system("cls");
					p.health--;
					cout << "Remaining Health: " << p.health << endl;
//					if (save('g') == 1){
//						return;
//					}
					Sleep(3000);
				}
			}
			if (check == 0){
				system("cls");
				sout << "You disappointed me.....";
				system("cls");
				sout << "FIN";
				return;
			}
			if (save('p') == 1){
				return;
			}
			POSITIVE:
		    storyPositiveEnd();
		    break;
	    case 0:
	    	//NEGATIVE DIRECTION
		    storyNeagtive();
		    if (save('m') == 1){
				return;
			}
			MINESWEEPER:
		    while(p.health > 0){
		    	ch = m.play();
		    	if (ch == 1){
		    		check = 1;
		    		break;
				}
				else {
					system("cls");
					p.health--;
					cout << "Remaining Health: " << p.health << endl;
//					if (save('m') == 1){
//						return;
//					}
					Sleep(3000);
				}
			}
			if (check == 0){
				system("cls");
				sout << "\"You disappointed me.....\"";
				system("cls");
				sout << "FIN";
				return;
			}
			if (save('n') == 1){
				return;
			}
			NEGATIVE:
		    storyNeagtiveEnd();
		    break;
	}
}

void Story::storyInitial() {
	sout.center();
	p.getInfo();
    system("cls");
    sout << "\"The life in the prison cell was unnerving with a dead routine that kept continuing like there was no end.\"";
    system("cls");
    sout << "\"But this time something was off about the whole day. The inmates all worried , some petrified and others.";
	sout << "Just baffled to the discovery they made in their cells. I(Andrew) was going to know what was going on.\"";
    system("cls");
    //the pov screen of his cell view appears
    sout << "\"5 years in the same cell and decades more to go, I never expected to find a laptop in my cell awaiting me.";
	sout << " Even the Grim Reaper wouldnt have been surprise for me because I had to recognise of my past or if I had a family.\"";
	sout << "Andrew walks towards set up that magically appeared in his room and the laptop shows a black screen with a message displaying ";
    //Laptoop zoom in
    system("cls");
    sout << "\"Hi Andrew... lets play a game?\"";
    //Deprived of any mode of entertainment and interaction with outside world, a little skeptical , he types back hello.
    system("cls");
    sout << "\"Your name is Andrew isnt it?\"";
    cout << "                   1. YES                  2. NO" << endl;
    cin >> answer;
    if (answer == 2) {
        system("cls");
        sout << "\"Oh, You don't need to lie to me. I know who you are. But never mind. People usually says lie when they face some strange circumstances.\"";
    }
    system("cls");
    sout << "\"Do you remember when were you were born\"";
    cout << "                   1. YES                  2. NO" << endl;
    cin >> answer;
    system("cls");
    sout << "\"Seems like you dont remember anything...Dont worry, everything with be known.\"";
    system("cls");
    sout << "Andrew feels a chill run down his spine as he watches the laptop's screen. He has no idea what this game is or who is behind it, but he is intrigued nonetheless.";
    system("cls");
    sout << " \"You are not who you think you are. \"";
    system("cls");
    sout << "\"You have been living a lie. Your entire life has been a simulation. Your memories, your family, everything you thought you knew is a fabrication";
    sout << "And now, you have a chance to escape.\"";
    system("cls");
    sout << "Andrew's heart is pounding in his chest as he reads the messages on the screen. He can feel his mind spinning, trying to make sense of what he is being told.";
    sout << "\"What do you mean a simulation? How is that even possible?\" The laptop responds almost immediately.";
    system("cls");
    sout << "\"You are part of an experiment. A project designed to simulate human behavior and consciousness. ";
    sout << "The world you know is not real. It is a construct designed to test the limits of the human mind.";
	sout << "But you have been selected to participate in a different kind of experiment. An experiment to see if you can break free from the simulation and discover the truth.\"";
    system("cls");
	sout<< "\"Now lets Begin. Be cautious about you have only three life chances.\"";
    system("cls");
}

void Story::storyPositive() {
	sout.center();
	system("cls");
    //After decoding the game responds with 
    sout << "\"Great job , you are very lucky man....\"";
    //The game pauses while Andrew tries to make sense of the response.
    system("cls");
    sout << "\"Yes Andrew.. You were a undercover for MI6 stationed at the Kremlin..\"";
    system("cls");
    sout << "A picture in uniform displays with man in his early 20s which in a moment Andrew realises is himself. Every blurred memory that had bothered him started making sense.";
    system("cls");
    sout << "\"Moving On. You didnt happen to see how this device was placed in your cell did you?\"";
    cout << "                   1. YES                  2. NO" << endl;
    cin >> answer;
    system("cls");
    if (answer == 1) {
        //If Yes, a loud noise is heard and a man's cry is heard for a split second. the program displays 
        sout << "\"Laibility Terminated\"";
        system("cls");
    }
    //If No, the program proceeds without a message.
    sout << "\"Who has the Access to your cell except you.";
    sout << "-There are no gaurds";
    sout << "-Your food is served in the food hall";
    sout << "-Inmates are not allowed to interact\"";
    cout << "(1)The people in control" << endl << "(2)The laptop was hidden in a secret compartment in the room from the begginng" << endl << "(3) I dont know" <<endl;
    cin >> answer;
    system("cls");
    //"The correct answer being (c) I dont know but due to the health lives on the line this easy desicion is going to be very hard."
    switch (answer) {
    case 1:
    case 2:
    	p.health--;
        cout << "Remaining Health: " << p.health << endl;
        Sleep(3000);
        system("cls");
        sout << "\"You were never like this Andrew.. you had the courage to stick with the facts. Probably these changes cost them their lives..\"";
        sout << "The program then displays a distorted picture , a bloody one that has a dead bodies of two people very familiar to Andrew.";
        sout << "\"Unfortunately you are right.. It is your parents...\"";
        break;
    case 3:
        break;
    }
    system("cls");
    sout << "\"Get yourself Together... You are in the last stages of this... Giving up will only lead to more casualties..\"";
}

void Story::storyPositiveEnd() {
	sout.center();
	system("cls");
    sout << "\"You are too close seeing the end...\"";
    system("cls");
    sout << "\"All these questions uptil now have been very random and out of context.... But its the end now.";
    sout << "Heres your last test...\"";
    while(p.health > 0){
    	system("cls");
    	sout << "What was your call code in MI6?\"";
    	if(p.health == 1){
			sout << "Be aware of your life. You have only last chance.";
			sout << "So I will show you a mercy by giving you some clue.";
			sout << "(Hint: It is three letters and related to user Name and age(+11) which is saved)";
		}
	    cin >> str;
	    system("cls");
		if (str == p.MI6code) {
	        sout << "\"You passed.. You can ask me anything you like.\"";
	        system("cls");
	        sout << "At this , with a sigh of relief Andrew types \"Who are you ??\" The program answers...";
			sout << "\"I am you.\"";
	        system("cls");
	        // "Cliff hanger.";
	        sout << "\"FIN\"";
	        return;
	    }
		else {
			p.health--;
			cout << "Remaining Health: " << p.health << endl;
			Sleep(3000);
			if (p.health == 0){
				system("cls");
				sout << "\"You disappointed me.....\"";
				system("cls");
				sout << "\"FIN\"";
				return;
			}
		}
	}
	   
}

void Story::storyNeagtive() {
	sout.center();
	system("cls");
    sout << "\"Nice going there. Just like old times when you played these games with your friends.. unfortunate not to be with you anymore..\"";
    system("cls");
    sout << "A picture of a couple of guys shows up with blood stained on them.";
	sout << "\"Lets make it more interesting\"";
    system("cls");
    sout << "\"You familiar with Minesweeper right? A puzzle game where the player tries to clear a minefield without detonating any mines.\"";
    system("cls");
    sout << "\"Only change is you denote a mine you loose a life.. Enjoy\"";
    system("cls");
}

void Story::storyNeagtiveEnd() {
	sout.center();
	system("cls");
    sout << "\"Well done, Guess it brings out the best in you when your life is on the line?\"";
    system("cls");
    sout << "\"But dont worry its almost the end of the line for us, it's your Last Test.\"";  
    while(p.health > 0){
    	system("cls");
    	sout << "What was your call code in MI6?\"";
    	if(p.health == 1){
			sout << "Be aware of your life. You have only last chance.";
			sout << "So I will show you a mercy by giving you some clue.";
			sout << "(Hint: It is three letters and related to user Name and age(+11) which is saved)";
		}
	    cin >> str;
	    system("cls");
		if (str == p.MI6code) {
	        sout << "\"You really desperate to get out yet you left it unnoticed that even though you answered the first question right , it wasnt what it was supposed to be and you lost a life there.. \"";
	        system("cls");
			sout << "\"It made me take you in whole different direction. Not the direction you were quiet looking forward to...\"";
			system("cls");
	        sout << "\"A little disappointed But I HAD FUNN.. I am going to miss you...\"";
	        system("cls");
	        sout << "The self destruct sequence intiates..";
	        system("cls");
	        sout << "\"FIN.\"";
	        return;
	    }
		else {
			p.health--;
			cout << "Remaining Health: " << p.health << endl;
			Sleep(3000);
			if (p.health == 0){
				system("cls");
				sout << "\"You disappointed me.....\"";
				system("cls");
				sout << "\"FIN\"";
				return;
			}
		}
	}
}

//int main()
//{
//	//Checking MI6 code
//	Player s;
//	s.getInfo();
//	cout << s.M16code;
//
//    return 0;
//}