#ifndef GRIDGAME_H
#define GRIDGAME_H

#include "ProjectIncludes.h"

// Some future editable points:
// 1. GUI (Numberings in grids will be eliminate.)
// 2. Statements or alignment of grids.

// Forward Declaration
class myGrid;
class Pattern;

// Base class
class Grid
{
protected:
	// Data members
	char square[4][4] = {
		{'0', '0', '0', '0'},
		{'0', '-', '-', '-'},
		{'0', '-', '-', '-'},
		{'0', '-', '-', '-'}};
	char original[4][4] = {
		{'0', '0', '0', '0'},
		{'0', '-', '-', '-'},
		{'0', '-', '-', '-'},
		{'0', '-', '-', '-'}};
	int pos = 0;

public:
	// Member functions
	virtual void show() = 0; // show live grid
	void reset();			 // reset grids for new input
	int setpos(int choice, char square[4][4]);
	friend int compare(myGrid &g, Pattern &p);
};

// Grid mem f
void Grid::reset()
{
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			square[j][k] = original[j][k];
		}
	}
}

int Grid::setpos(int choice, char square[4][4])
{ // assigning position in my grid
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
	else
	{
		return 0;
	}
	return 1;
}

// Classses
class myGrid : public Grid, public GridOfButtons
{
	sf::Texture marked;
	sf::Texture notMarked;
	int inputMarks = 0;
	bool shown = false;

public:
	myGrid(int xPos, int yPos) : GridOfButtons(xPos, yPos, 3, 3, nullptr, 0, 5, 80, 80, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, notMarked, sf::Color::Transparent,  sf::Color::White, sf::Color::Transparent, 1)
	{
		marked.loadFromFile("assets/marked.png");
		notMarked.loadFromFile("assets/notMarked.png");
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Buttons[i][j].setTexture(notMarked);
			}
		}
	}
	void UpdateTextures()
	{
		for (int row = 1; row < 4; row++)
		{
			for (int col = 1; col < 4; col++)
			{
				if (square[row][col] == 'X')
				{
					Buttons[row - 1][col - 1].setTexture(marked);
				}
				else
				{
					Buttons[row - 1][col - 1].setTexture(notMarked);
				}
			}
		}
	}
	void setpos(int n, sf::Vector2i pos, sf::Event event) // inputing positon of player
	{
		clickedGridIndex index = updateAndGetClicked(pos, event);
		square[index.row + 1][index.column + 1] = (index.isClicked) ? 'X' : square[index.row + 1][index.column + 1];
		inputMarks = 0;
		for (int row = 1; row < 4; row++)
		{
			for (int col = 1; col < 4; col++)
			{
				if (square[row][col] == 'X')
					inputMarks++;
			}
		}
		UpdateTextures();
	}
	void show() { shown = true; }

	int getNumberOfMarks()
	{
		return inputMarks;
	}

	void reset()
	{
		Grid::reset();
		UpdateTextures();
	}
};

class Pattern : public Grid, public GridOfButtons
{
	sf::Texture marked;
	sf::Texture notMarked;

	bool shown = false;
	int N = 1;

public:
	Pattern(int xPos, int yPos) : GridOfButtons(xPos, yPos, 3, 3, nullptr, 0, 5, 80, 80)
	{
		marked.loadFromFile("assets/marked.png");
		notMarked.loadFromFile("assets/notMarked.png");
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Buttons[i][j].setTexture(notMarked);
			}
		}
	}
	void UpdateTextures()
	{
		for (int row = 1; row < 4; row++)
		{
			for (int col = 1; col < 4; col++)
			{
				if (square[row][col] == 'X')
				{
					Buttons[row - 1][col - 1].setTexture(marked);
				}
				else
				{
					Buttons[row - 1][col - 1].setTexture(notMarked);
				}
			}
		}
	}
	void show() { shown = true; }
	int posSet() { return N; }
	// setting pattern by random positions
	void setpos(int n)
	{
		N = n + 1;
		for (int i = 0; i < n; i++)
		{
			Grid::setpos(random(), square);
		}
		UpdateTextures();
	}
	int random() // returning random position for given pattern
	{
		int lower = 1, upper = 9;
		srand(time(0));
		int choice;
		while (1)
		{
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
	bool isShown() { return shown; }
	void toggleShown() { shown = !shown; }
	void reset()
	{
		Grid::reset();
		UpdateTextures();
	}
};

// Global
int compare(myGrid &g, Pattern &p)
{
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (g.square[j][k] != p.square[j][k])
			{
				return 0;
			}
		}
	}
	return 1;
}

// Main class
class GridGameGUI
{
protected:
	myGrid PlayerGrid;
	Pattern pattern;
	int check = 0;
	int currentNumberOfMarks = 1;
	sf::Clock DelayClock;
	bool DrawPattern = true;
	int delayCalls = 0;
	bool GameWon = false;
	bool GameLost = false;

public:
	GridGameGUI(int x, int y) : PlayerGrid(x, y), pattern(x, y)
	{
		pattern.setpos(currentNumberOfMarks);
	}
	void updateGame(sf::Vector2i mousePos, sf::Event event)
	{
		if (currentNumberOfMarks <= 6)
		{
			if (pattern.posSet() <= currentNumberOfMarks)
			{
				pattern.setpos(currentNumberOfMarks);
				DrawPattern = true;
			}
			if (DrawPattern)
			{
				if (delayCalls == 0)
				{
					delayCalls++;
					DelayClock.restart();
				}
				if (DelayClock.getElapsedTime().asMilliseconds() > 200)
				{
					DrawPattern = false;
					delayCalls = 0;
				}
			}
			else
			{
				if (currentNumberOfMarks > PlayerGrid.getNumberOfMarks())
				{
					PlayerGrid.myGrid::setpos(currentNumberOfMarks, mousePos, event);
				}
				else
				{
					// Compare
					check = compare(PlayerGrid, pattern);
					if (check == 0)
					{
						GameLost = false;
					}
					else
					{
						DrawPattern = true;
						pattern.reset();
						PlayerGrid.reset();
						GameWon = (currentNumberOfMarks == 6) ? true : false;
						currentNumberOfMarks++;
					}
				}
			}
		}
		else GameWon = true;
	}
	void draw(sf::RenderTarget &window)
	{
		if (DrawPattern)
		{
			pattern.render(window);
		}
		else
		{
			PlayerGrid.render(window);
		}
	}
	bool isGameWon() { return GameWon; }
	bool isGameLost() { return GameLost; }
};

class GridGame : public GridGameGUI, public Game
{

public:
	GridGame() : GridGameGUI(380, 200)
	{
		
	}
	int end()
	{
		if (check == 0) {
			sprint << "\"You failed.\"";
			return 0;
		}
		else {
			sprint << "\"Congratulation. You passed this stage.\"";
			return 1;
		}
	}
	int play()
	{
		sf::Font MenuButtonFont;
		sf::Event event = sf::Event();
		sf::Vector2i mousePos;
		PlayerGrid.reset();
		pattern.reset();
		pattern.setpos(1);
		MenuButtonFont.loadFromFile("assets/fonts/Monorama-Medium.otf");
		sprint << "Welcome for new challenge.";
		sprint << "This is pattern grid game. You have to follow the given pattern.";
		
		while (mainWindow.isOpen() && !isGameLost() && !isGameWon())
		{
			while (mainWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					mainWindow.close();

				if (event.type == sf::Event::MouseMoved)
				{
					mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					updateGame(mousePos, event);
					event = sf::Event();
				}
			}
			updateGame(mousePos, event);
			mainWindow.clear();
			draw(mainWindow);
			mainWindow.display();
		}

		return end();
	}
};
#endif