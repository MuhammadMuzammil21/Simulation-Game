#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include "SpookyOutput.hpp"
#define DELAY 400 //in milliseconds
using namespace std;

//Some future editable points:
//1. GUI (Numberings in grids will be eliminate.)
//2. Statements or alignment of grids.

//Forward Declaration
class myGrid;
class Pattern;

//3rd Class
class GUIGrid{
	char square[4][4] = {
                      {'0', '0', '0', '0'},
                      {'0', '-', '-', '-'},
                      {'0', '-', '-', '-'},
                      {'0', '-', '-', '-'} };
public:
	void show(char grid[4][4]);    
};

void GUIGrid:: show(char grid[4][4]){
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			square[j][k] = grid[j][k];
		}
	}
	cout << " _______________________" << endl;
	cout << "|1      |2      |3      |" << endl;
	cout << "|   "<< square[1][1] <<"   |   " << square[1][2] << "   |   " << square[1][3] << "   |   " << endl;
	cout << "|_______|_______|_______|" << endl;
	cout << "|4      |5      |6      |" << endl;
	cout << "|   " << square[2][1] << "   |   " << square[2][2] << "   |   " << square[2][3] << "   |" << endl;
	cout << "|_______|_______|_______|" << endl;
	cout << "|7      |8      |9      |" << endl;
	cout << "|   " << square[3][1] << "   |   " << square[3][2] << "   |   " << square[3][3] << "   |" << endl;
	cout << "|_______|_______|_______|" << endl;
	cout << endl << endl;
	Sleep(400); 
}


//Base class
class Grid {
protected: 
	//Data members
    char square[4][4] = {
                      {'0', '0', '0', '0'},
                      {'0', '-', '-', '-'},
                      {'0', '-', '-', '-'},
                      {'0', '-', '-', '-'} };
    char original[4][4] = {
                      {'0', '0', '0', '0'},
                      {'0', '-', '-', '-'},
                      {'0', '-', '-', '-'},
                      {'0', '-', '-', '-'} };
    int pos = 0;
public: 
    //Member functions
	virtual void show(GUIGrid) = 0; //show live grid
	void reset(); //reset grids for new input
	int setpos(int choice, char square[4][4]);
	friend int compare (myGrid & g, Pattern & p);
};

//Grid mem f
void Grid::reset() {
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			square[j][k] = original[j][k];
		}
	}
}

int Grid::setpos(int choice, char square[4][4]) { //assigning position in my grid
	char mark = 'X';
	if (choice == 1 && square[1][1] == '-')
		square[1][1] = mark;

	else if (choice == 2 && square[1][2] == '-')
		square[1][2] = mark;

	else if (choice == 3 && square[1][3] == '-')
		square[1][3] = mark;

	else if (choice == 4 && square[2][1] == '-')
		square[2][1] = mark;

	else if (choice == 5 && square[2][2] == '-')
		square[2][2] = mark;

	else if (choice == 6 && square[2][3] == '-')
		square[2][3] = mark;

	else if (choice == 7 && square[3][1] == '-')
		square[3][1] = mark;

	else if (choice == 8 && square[3][2] == '-')
		square[3][2] = mark;

	else if (choice == 9 && square[3][3] == '-')
		square[3][3] = mark;
	else {
		return 0;
	}
	return 1;
}


//Classses
class myGrid: public Grid{
public:
    //Member functions
    void setpos(int, GUIGrid); //inputing positon of player 
	void show(GUIGrid); //show player live inputed grid
};

class Pattern: public Grid {
public:
    //Member functions
	void setpos(int); //setting pattern by random positions
	int random(); //returning random position for given pattern
	void show(GUIGrid); //show set pattern which player should be follow
};

//Pattern mem f
void Pattern::setpos(int n) {
	for (int i = 0; i < n; i++) {
		Grid::setpos(random(), square);
	}
}

int Pattern::random() {
	int lower = 1, upper = 9;
	srand(time(0));
	int choice;
	while (1) {
		choice = (rand() % (upper - lower + 1)) + lower;
		if (choice == 1 && square[1][1] == '-')
			return choice;

		else if (choice == 2 && square[1][2] == '-')
			return choice;

		else if (choice == 3 && square[1][3] == '-')
			return choice;

		else if (choice == 4 && square[2][1] == '-')
			return choice;

		else if (choice == 5 && square[2][2] == '-')
			return choice;

		else if (choice == 6 && square[2][3] == '-')
			return choice;

		else if (choice == 7 && square[3][1] == '-')
			return choice;

		else if (choice == 8 && square[3][2] == '-')
			return choice;

		else if (choice == 9 && square[3][3] == '-')
			return choice;
	}

}

void Pattern::show(GUIGrid G) {
	system("cls");
	cout << "         Pattern" << endl;
	G.show(square);
	Sleep(DELAY); //time delay required
	system("cls");
}

//myGrid mem f
void myGrid::setpos(int n, GUIGrid G) {
	//int* pos = new int(n);
	int p;
	myGrid::show(G);
    for (int i = 0; i < n; i++) {
        cout << "Enter position " << i + 1 << ": ";
		cin >> p;
		Grid::setpos(p, square);
		if (i == n-1){
			continue;
		}
		myGrid::show(G);
    }
}

void myGrid::show(GUIGrid G) {
	system("cls");
	cout << "         My Grid" << endl;
	G.show(square);
	Sleep(400); //Time delay required. 
}

//Global
int compare(myGrid & g, Pattern & p) {
	system("cls");
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			if (g.square[j][k] != p.square[j][k]) {
				return 0;
			}
		}
	}
	return 1;
}

//Main class
class GridGame: public Game{
	myGrid g;
	Pattern p;
	GUIGrid G;
	int check = 0;
public: 
	void start();
	int play();
	int end();	
};

void GridGame :: start(){
	system("cls");
    sout << "Welcome for new challenge.";
    sout << "This is pattern grid game. You have to follow the given pattern.";
	sout << "If you are ready, press any key.";
	_getch();
}

int GridGame :: end(){
	//Game ending statement
	system("cls");
	if (check == 0) {
		sout << "You failed.";
		return 0;
	}
	else {
		sout << "Congratulation. You passed this stage.";
		return 1;
	}
}

int GridGame :: play(){
	p.reset();
	g.reset();
	start();
	for (int i = 1; i < 6; i++) {
		//Give Pattern
		p.Pattern::setpos(i);
		p.Pattern::show(G);
		
		//Player input
		g.myGrid::setpos(i, G); // I donot checked invalid inputs as we are going to implement through GUI.

		//Compare
		check = compare(g, p);
		if (check == 0) {
			break;
		}

		//Reset Grid and Pattern
		p.reset();
		g.reset();
	}
	return end();
}

////main function
//int main() {
//    GridGame g;
//    g.play();
//	return 0;
//}
//
//
