#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
	enum button_states { IDLE = 0, HOVER, PRESSED };
	enum clicked_states { NotClicked = 0, LeftClicked, RightClicked, MiddleMouseClicked, LeftRightClicked };
	short unsigned buttonState;
	bool PreviousClick;
	bool PreviousRightClick;
	short unsigned id;
	int height;
	int width;


	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textPressedColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlinePressedColor;

	sf::Clock updateClock;
	sf::Clock clickClock;
	sf::Clock updateClockRight;
	sf::Clock clickClockRight;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_pressed_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Texture texture = sf::Texture(),
		sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent, float outline_thickness = 1.f,
		short unsigned id = 0);
	~Button();

	//Accessors
	const bool isPressed() const;
	const std::string getText() const;
	const short unsigned& getId() const;
	bool isClicked(const sf::Vector2i& mousePosWindow);
	bool isClickedEvent(const sf::Vector2i& mousePosWindow, const sf::Event& event);
	bool isRightClickedEvent(const sf::Vector2i& mousePosWindow, const sf::Event& event);

	//Modifiers
	void setText(const std::string text);
	void setId(const short unsigned id);
	void setTexture(const sf::Texture& newTexture);
	void setFont(sf::Font *fontPtr);

	//Functions
	void update(const sf::Vector2i& mousePosWindow, const sf::Event &event);
	void render(sf::RenderTarget& target);
};
Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_pressed_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Texture texture,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color, float outline_thickness,
	short unsigned id)
{
	this->buttonState = IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(outline_thickness);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);

	this->text.setPosition(shape.getPosition().x + shape.getSize().x / 2 - this->text.getLocalBounds().width / 2, shape.getPosition().y + shape.getSize().y / 2 - this->text.getLocalBounds().height);


	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textPressedColor = text_pressed_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->pressedColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlinePressedColor = outline_active_color;
	this->width = width;
	this->height = height;

	this->texture = texture;
	// loading texture
	sprite.setPosition(x, y);
	sprite.setTexture(this->texture);
	float scaleX = shape.getSize().x / texture.getSize().x;
	float scaleY = shape.getSize().y / texture.getSize().y;
	sprite.setScale(scaleX, scaleY);
}

Button::~Button()
{

}

//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == PRESSED)
		return true;

	return false;
}

const std::string Button::getText() const
{
	return this->text.getString();
}

const short unsigned& Button::getId() const
{
	return this->id;
}

bool Button::isClicked(const sf::Vector2i& mousePosWindow)
{
	if (updateClock.getElapsedTime().asMilliseconds() >= 80)
	{
		updateClock.restart();
		this->buttonState = IDLE;

		//Hover
		if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->buttonState = HOVER;

			//Pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && PreviousClick == false)
			{
				this->buttonState = PRESSED;
			}
		}

		switch (this->buttonState)
		{
		case IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			this->shape.setOutlineColor(this->outlineIdleColor);
			break;

		case HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			break;

		case PRESSED:
			this->shape.setFillColor(this->pressedColor);
			this->text.setFillColor(this->textPressedColor);
			this->shape.setOutlineColor(this->outlinePressedColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::Blue);
			this->shape.setOutlineColor(sf::Color::Green);
			break;
		}
	}

	if (PRESSED == this->buttonState && clickClock.getElapsedTime().asMilliseconds() >= 250)
	{
		clickClock.restart();
		PreviousClick = true;
		return true;
	}
	PreviousClick = false;
	return false;
}

bool Button::isClickedEvent(const sf::Vector2i& mousePosWindow, const sf::Event& event)
{
	static sf::Vector2i previous;
	if (previous == mousePosWindow && clickClock.getElapsedTime().asSeconds() < 1)
		return false;
	if (updateClock.getElapsedTime().asMilliseconds() >= 80)
	{
		updateClock.restart();
		this->buttonState = IDLE;

		//Hover
		if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->buttonState = HOVER;

			//Pressed
			if (PreviousClick == false && event.mouseButton.button == sf::Mouse::Left)
			{
				this->buttonState = PRESSED;
			}
		}

		switch (this->buttonState)
		{
		case IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			this->shape.setOutlineColor(this->outlineIdleColor);
			break;

		case HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			break;

		case PRESSED:
			this->shape.setFillColor(this->pressedColor);
			this->text.setFillColor(this->textPressedColor);
			this->shape.setOutlineColor(this->outlinePressedColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::Blue);
			this->shape.setOutlineColor(sf::Color::Green);
			break;
		}
	}

	if (PRESSED == this->buttonState && clickClock.getElapsedTime().asMilliseconds() >= 200)
	{
		previous = mousePosWindow;
		clickClock.restart();
		this->buttonState = IDLE;
		PreviousClick = true;
		return true;
	}

	PreviousClick = false;
	return false;
}

inline bool Button::isRightClickedEvent(const sf::Vector2i& mousePosWindow, const sf::Event& event)
{
	static sf::Vector2i previous;
	if (previous == mousePosWindow && clickClockRight.getElapsedTime().asSeconds() < 1)
		return false;
	if (updateClockRight.getElapsedTime().asMilliseconds() >= 80)
	{
		updateClockRight.restart();
		this->buttonState = IDLE;

		//Hover
		if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->buttonState = HOVER;

			//Pressed
			if (PreviousRightClick == false && event.mouseButton.button == sf::Mouse::Right)
			{
				this->buttonState = PRESSED;
			}
		}

		switch (this->buttonState)
		{
		case IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			this->shape.setOutlineColor(this->outlineIdleColor);
			break;

		case HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			break;

		case PRESSED:
			this->shape.setFillColor(this->pressedColor);
			this->text.setFillColor(this->textPressedColor);
			this->shape.setOutlineColor(this->outlinePressedColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::Blue);
			this->shape.setOutlineColor(sf::Color::Green);
			break;
		}
	}

	if (PRESSED == this->buttonState && clickClock.getElapsedTime().asMilliseconds() >= 200)
	{
		clickClockRight.restart();
		this->buttonState = IDLE;
		PreviousRightClick = true;
		previous = mousePosWindow;
		return true;
	}

	PreviousRightClick = false;
	return false;
}

//Modifiers
void Button::setText(const std::string text)
{
	this->text.setString(text);

	// Recalculate text position
	this->text.setPosition(shape.getPosition().x + shape.getSize().x / 2 - this->text.getLocalBounds().width / 2, shape.getPosition().y + shape.getSize().y / 2 - this->text.getLocalBounds().height);
}

void Button::setId(const short unsigned id)
{
	this->id = id;
}

void Button::setTexture(const sf::Texture& newTexture)
{
	this->texture = newTexture;
	// loading texture
	sprite.setTexture(texture, true);
	float scaleX = shape.getSize().x / texture.getSize().x;
	float scaleY = shape.getSize().y / texture.getSize().y;
	sprite.setScale(scaleX, scaleY);
}

inline void Button::setFont(sf::Font* fontPtr)
{
	font = fontPtr;
	text.setFont(*fontPtr);
	setText(text.getString());
}


// Functions

/*Update the booleans for hover and pressed*/
void Button::update(const sf::Vector2i& mousePosWindow, const sf::Event& event)
{
	if (updateClock.getElapsedTime().asMilliseconds() >= 100)
	{
		updateClock.restart();
		this->buttonState = IDLE;

		//Hover
		if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->buttonState = HOVER;

			//Pressed
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				this->buttonState = PRESSED;
			}
		}

		switch (this->buttonState)
		{
		case IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			this->shape.setOutlineColor(this->outlineIdleColor);
			break;

		case HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			break;

		case PRESSED:
			this->shape.setFillColor(this->pressedColor);
			this->text.setFillColor(this->textPressedColor);
			this->shape.setOutlineColor(this->outlinePressedColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::Blue);
			this->shape.setOutlineColor(sf::Color::Green);
			break;
		}
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->sprite);
	target.draw(this->text);
}
#endif