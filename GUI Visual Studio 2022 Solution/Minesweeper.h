#include "ProjectIncludes.h"

#ifndef MINESWEEPER_H
#define MINESWEEPER_H


enum textureOption { IDLE = 0, MINE, FLAGGED };
class MinesweeperButtons : public GridOfButtons
{

	sf::Texture mine;
	sf::Texture flag;
	sf::Font MinesweeperFont;

public:
	MinesweeperButtons(int x, int y, int rows, int columns, int fontSize, unsigned int gapBetweenButtons, float buttonLengths) : GridOfButtons(x, y, rows, columns, nullptr, fontSize, gapBetweenButtons, buttonLengths)
	{
		MinesweeperFont.loadFromFile("assets/fonts/SummerPixel.ttf");
		GridOfButtons::setFont(&MinesweeperFont);
		mine.loadFromFile("assets/mine.png");
		flag.loadFromFile("assets/flag.png");
	}
	void SetTextAndTexture(int row, int column, textureOption option, std::string text = "")
	{
		switch (option)
		{
		case IDLE:
			Buttons[row][column].setTexture(sf::Texture());
			Buttons[row][column].setText(text);
			break;
		case MINE:
			Buttons[row][column].setText(text);
			Buttons[row][column].setTexture(mine);
			break;
		case FLAGGED:
			Buttons[row][column].setText(text);
			Buttons[row][column].setTexture(flag);
			break;
		default:
			break;
		}
	}
};


// A cell in the game grid
class Cell
{
public:
	bool isMine;
	bool isRevealed;
	bool isFlagged;
	int numAdjacentMines;
	Cell() : isMine(false), isRevealed(false), isFlagged(false), numAdjacentMines(0) {}
};

// The game grid
class MinesweeperGUI
{
private:
	std::vector<std::vector<Cell>> cells;
	MinesweeperButtons Buttons;
	int numRows;
	int numCols;
	int numMines;
	sf::Font* font;
public:
	MinesweeperGUI(int numRows, int numCols, int numMines, int xPos, int yPos, int fontSize, unsigned int gapBetweenButtons = 3, float ButtonLength = 40) : numRows(numRows), numCols(numCols), numMines(numMines), Buttons(MinesweeperButtons(xPos, yPos, numRows, numCols, fontSize, gapBetweenButtons, ButtonLength))
	{
		cells.resize(numRows);
		for (int i = 0; i < numRows; i++)
		{
			cells[i].resize(numCols, Cell());
		}
		generateMines();
		countAdjacentMines();
	}

	void generateMines()
	{
		std::random_device rd;
		std::mt19937 gen(rd() + std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> distRows(0, numRows - 1);
		std::uniform_int_distribution<int> distCols(0, numCols - 1);

		int numMinesPlaced = 0;
		while (numMinesPlaced < numMines)
		{
			int row = distRows(gen);
			int col = distCols(gen);
			if (!cells[row][col].isMine)
			{
				cells[row][col].isMine = true;
				numMinesPlaced++;
			}
		}
	}

	void countAdjacentMines()
	{
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (!cells[row][col].isMine)
				{
					int count = 0;
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -1; j <= 1; j++)
						{
							int adjRow = row + i;
							int adjCol = col + j;
							if (adjRow >= 0 && adjRow < numRows && adjCol >= 0 && adjCol < numCols && cells[adjRow][adjCol].isMine)
							{
								count++;
							}
						}
					}
					cells[row][col].numAdjacentMines = count;
				}
			}
		}
	}

	void reveal(int row, int col)
	{
		if (cells[row][col].isRevealed || cells[row][col].isFlagged)
		{
			return;
		}
		cells[row][col].isRevealed = true;
		if (cells[row][col].isMine)
		{
			// Game over
			return;
		}
		if (cells[row][col].numAdjacentMines == 0)
		{
			// Reveal all adjacent cells
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int adjRow = row + i;
					int adjCol = col + j;
					if (adjRow >= 0 && adjRow < numRows && adjCol >= 0 && adjCol < numCols)
					{
						reveal(adjRow, adjCol);
					}
				}
			}
		}
	}

	void toggleFlag(int row, int col)
	{
		if (cells[row][col].isRevealed)
		{
			return;
		}
		cells[row][col].isFlagged = !cells[row][col].isFlagged;
	}

	void UpdateGame(sf::Vector2i MousePosition, sf::Event event)
	{
		clickedGridIndex currentClicked = Buttons.updateAndGetClicked(MousePosition, event);
		clickedGridIndex currentRightClicked = Buttons.updateAndGetRightClicked(MousePosition, event);
		if (currentClicked.isClicked && !isGameWon() && !isGameOver())
		{
			reveal(currentClicked.row, currentClicked.column);
		}
		else if (currentRightClicked.isRightClicked && !isGameWon() && !isGameOver())
		{
			toggleFlag(currentRightClicked.row, currentRightClicked.column);
		}
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (cells[row][col].isRevealed)
				{
					if (cells[row][col].isMine)
					{
						Buttons.SetTextAndTexture(row, col, MINE);
					}
					else
					{
						Buttons.SetTextAndTexture(row, col, IDLE, std::to_string(cells[row][col].numAdjacentMines));
					}
				}
				else if (cells[row][col].isFlagged)
				{
					Buttons.SetTextAndTexture(row, col, FLAGGED);
				}
				if (!cells[row][col].isFlagged)
				{
					Buttons.SetTextAndTexture(row, col, IDLE, "");
				}
			}
		}
	}

	void MainGame(sf::RenderTarget& window, const sf::Vector2i& mousePos, sf::Event event)
	{
		clickedGridIndex currentClicked = Buttons.updateAndGetClicked(mousePos, event);
		clickedGridIndex currentRightClicked = Buttons.updateAndGetRightClicked(mousePos, event);
		if (currentClicked.isClicked)
		{
			reveal(currentClicked.row, currentClicked.column);
		}
		else if (currentRightClicked.isRightClicked)
		{
			toggleFlag(currentRightClicked.row, currentRightClicked.column);
		}
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (cells[row][col].isRevealed)
				{
					if (cells[row][col].isMine)
					{
						Buttons.SetTextAndTexture(row, col, MINE);
					}
					else
					{
						Buttons.SetTextAndTexture(row, col, IDLE, std::to_string(cells[row][col].numAdjacentMines));
					}
				}
				else if (cells[row][col].isFlagged)
				{
					Buttons.SetTextAndTexture(row, col, FLAGGED);
				}
				else if (!(cells[row][col].isFlagged))
				{
					Buttons.SetTextAndTexture(row, col, IDLE, "");
				}
			}
		}
		Buttons.render(window);
	}

	void print()
	{
		std::cout << "  ";
		for (int col = 0; col < numCols; col++)
		{
			std::cout << col << " ";
		}
		std::cout << std::endl;

		for (int row = 0; row < numRows; row++)
		{
			std::cout << row << " ";
			for (int col = 0; col < numCols; col++)
			{
				if (cells[row][col].isRevealed)
				{
					if (cells[row][col].isMine)
					{
						std::cout << "* ";
					}
					else
					{
						std::cout << cells[row][col].numAdjacentMines << " ";
					}
				}
				else if (cells[row][col].isFlagged)
				{
					std::cout << "F ";
				}
				else
				{
					std::cout << ". ";
				}
			}
			std::cout << std::endl;
		}
	}

	bool isGameOver()
	{
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (cells[row][col].isMine && cells[row][col].isRevealed)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool isGameWon()
	{
		int numUnrevealedNonMines = 0;
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (!cells[row][col].isMine && !cells[row][col].isRevealed)
				{
					numUnrevealedNonMines++;
				}
			}
		}
		return numUnrevealedNonMines == 0;
	}
};

class Minesweeper : public MinesweeperGUI, public Game
{
public:
	Minesweeper() : MinesweeperGUI(10, 10, 10, 300, 200, 20, 5, 38)
	{

	}
	int play()
	{
		sprint.clear();
		mainWindow.clear();
		sf::Font MenuButtonFont;
		MenuButtonFont.loadFromFile("assets/fonts/Monorama-Medium.otf");
		sf::Font MinesweeperFont;
		MinesweeperFont.loadFromFile("assets/fonts/SummerPixel.ttf");
		sf::Text gameOverMsg("", MenuButtonFont, 24);
		sf::Vector2i mousePos;
		sf::Event event = sf::Event();
		int ret = 3;
		while (mainWindow.isOpen() && !isGameOver() && !isGameWon())
		{
			while (mainWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					mainWindow.close();
					exit(0);
				}

				if (event.type == sf::Event::MouseMoved)
				{
					mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					MainGame(mainWindow, mousePos, event);
				}
			}
			MainGame(mainWindow, mousePos, event);
			if (isGameWon())
			{
				gameOverMsg.setString("You Won!");
				ret = 1;
			}
			else if (isGameOver())
			{
				gameOverMsg.setString("You Lost!");
				ret = 0;
			}
			MainGame(mainWindow, mousePos, event);
			gameOverMsg.setPosition(mainWindow.getSize().x / 2.f - gameOverMsg.getLocalBounds().width / 2.f, 100);
			mainWindow.draw(gameOverMsg);
			mainWindow.display();
			if (ret == 0 || ret == 1)
				sf::sleep(sf::milliseconds(2500));
		}
		return ret;
	}
};

#endif