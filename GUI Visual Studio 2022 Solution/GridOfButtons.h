#ifndef GRIDOFBUTTONS_H
#define GRIDOFBUTTONS_H

struct clickedGridIndex
{
	int row = 0;
	int column = 0;
	bool isClicked = false;
	bool isRightClicked = false;
};

class GridOfButtons
{
protected:
	int rows;
	int columns;
	float ButtonLength = 5;
	float ButtonWidth = 0;
	unsigned int gapBetweenButtons;
	sf::Font* fontForButtons;
	std::vector<std::vector<Button>> Buttons;

public:
	GridOfButtons(int x, int y, int rows, int columns, sf::Font* font, int fontSize, unsigned int gapBetweenButtons, float length, float width = 0,
		sf::Color text_idle_color = sf::Color(0, 0, 0, 255), sf::Color text_hover_color = sf::Color(0, 0, 0, 255), sf::Color text_pressed_color = sf::Color(0, 0, 0, 255),
		sf::Color idle_color = sf::Color(220, 220, 220, 255), sf::Color hover_color = sf::Color(255, 255, 255, 255), sf::Color active_color = sf::Color(200, 200, 200, 255), sf::Texture texture = sf::Texture(),
		sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent, float outline_thickness = 1.f)
		: rows(rows), columns(columns), gapBetweenButtons(gapBetweenButtons), ButtonLength(length)
	{
		width = (width == 0) ? length : width;
		this->ButtonWidth = width;
		this->fontForButtons = font;
		Buttons.resize(rows);
		for (int row = 0; row < rows; row++)
		{
			for (int column = 0; column < columns; column++)
			{
				Buttons[row].push_back(Button(x + ButtonWidth * column + gapBetweenButtons * column, y + ButtonLength * row + gapBetweenButtons * row, ButtonWidth, ButtonLength, fontForButtons, "", fontSize,
					text_idle_color, text_hover_color, text_pressed_color, idle_color, hover_color, active_color,
					texture, outline_idle_color, outline_hover_color, outline_active_color, outline_thickness));
			}
		}
	}
	void render(sf::RenderTarget& window)
	{
		for (int row = 0; row < rows; row++)
		{
			for (int column = 0; column < columns; column++)
			{
				Buttons[row][column].render(window);
			}
		}
	}
	clickedGridIndex updateAndGetClicked(const sf::Vector2i& mousePosWindow, sf::Event event)
	{
		clickedGridIndex returnValue;
		bool isClicked = false;
		int row = 0, column = 0;
		for (row = 0; row < rows && !isClicked; row++)
		{
			for (column = 0; column < columns && !isClicked; column++)
			{
				isClicked = Buttons[row][column].isClickedEvent(mousePosWindow, event);
				returnValue.isClicked = isClicked;
			}
		}

		if (returnValue.isClicked)
		{
			returnValue.column = column - 1;
			returnValue.row = row - 1;
			return returnValue;
		}

		return returnValue;
	}
	clickedGridIndex updateAndGetRightClicked(const sf::Vector2i& mousePosWindow, sf::Event event)
	{
		clickedGridIndex returnValue;
		bool isRightClicked = false;
		int row = 0, column = 0;
		for (row = 0; row < rows && !isRightClicked; row++)
		{
			for (column = 0; column < columns && !isRightClicked; column++)
			{
				isRightClicked = Buttons[row][column].isRightClickedEvent(mousePosWindow, event);
				returnValue.isRightClicked = isRightClicked;
			}
		}

		if (returnValue.isRightClicked)
		{
			returnValue.column = column - 1;
			returnValue.row = row - 1;
			return returnValue;
		}

		return returnValue;
	}
	void setFont(sf::Font *fontPtr)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				Buttons[i][j].setFont(fontPtr);
			}
		}
	}
};

#endif