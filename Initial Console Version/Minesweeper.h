#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

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
class mGrid
{
private:
    vector<vector<Cell>> cells;
    int numRows;
    int numCols;
    int numMines;

public:
    mGrid(int numRows, int numCols, int numMines) : numRows(numRows), numCols(numCols), numMines(numMines)
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
        random_device rd;
        mt19937 gen(rd() + chrono::system_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> distRows(0, numRows - 1);
        uniform_int_distribution<int> distCols(0, numCols - 1);

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

    void print()
    {
        cout << "  ";
        for (int col = 0; col < numCols; col++)
        {
            cout << col << " ";
        }
        cout << endl;

        for (int row = 0; row < numRows; row++)
        {
            cout << row << " ";
            for (int col = 0; col < numCols; col++)
            {
                if (cells[row][col].isRevealed)
                {
                    if (cells[row][col].isMine)
                    {
                        cout << "* ";
                    }
                    else
                    {
                        cout << cells[row][col].numAdjacentMines << " ";
                    }
                }
                else if (cells[row][col].isFlagged)
                {
                    cout << "F ";
                }
                else
                {
                    cout << ". ";
                }
            }
            cout << endl;
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

class Minesweeper: public Game{
public:
	int play(){
		int numRows = 10;
	    int numCols = 10;
	    int numMines = 10;
	
	    mGrid grid(numRows, numCols, numMines);
	    
		system("cls");
	    while (!grid.isGameOver() && !grid.isGameWon())
	    {
	    	grid.print();
	        int row, col;
	        string action;
	        cout << "Enter row and column (e.g. 3 4 x), or toggle flag (e.g. 3 4 f): ";
	        cin >> row >> col >> action;
	        if (action == "f")
	        {
	            grid.toggleFlag(row, col);
	        }
	        else
	        {
	            grid.reveal(row, col);
	        }
	        grid.print();
	        system("cls");
	    }
	
	    if (grid.isGameOver())
	    {
	        sout << "Lost...";
	        return 0;
	    }
	    else
	    {
	        sout << "You cleared this stage";
	        return 1;
	    }
	}
};
