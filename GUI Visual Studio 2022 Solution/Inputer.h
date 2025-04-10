#ifndef INPUTER_H
#define INPUTER_H

class Inputer
{
    sf::Text text;
    sf::RectangleShape cursor;
    sf::Font textFont;
    sf::RenderWindow& window;
    sf::Event event = sf::Event();
    std::string inputText;
    bool textEntered = false;
    bool cursorVisible = false;
    sf::Clock cursorTimer;

    void reset()
    {
        text.setString("");
        inputText = "";
        textEntered = false;
        cursorVisible = false;
    }

public:
    Inputer(sf::RenderWindow& window) : window(window)
    {
        textFont.loadFromFile("assets/fonts/font coolvetica rg.otf");
        text.setFont(textFont);
        text.setCharacterSize(24);
        cursor.setFillColor(sf::Color::White);
        text.setString("Hj");
        cursor.setSize(sf::Vector2f(2.f, text.getGlobalBounds().height));
        text.setString("");
    }

    template <typename T>
    void operator>>(T& input)
    {
        textEntered = false;
        while (window.isOpen() && !textEntered)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    exit(0);
                }
                else if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r')
                    {
                        inputText += static_cast<char>(event.text.unicode);
                        text.setString(inputText);
                        text.setPosition(window.getSize().x / 2.f - text.getLocalBounds().width / 2.f, window.getSize().y / 2.f - text.getLocalBounds().height / 2.f);
                    }
                    else if (event.text.unicode == '\b' && !inputText.empty())
                    {
                        inputText.erase(inputText.size() - 1, 1);
                        text.setString(inputText);
                        text.setPosition(window.getSize().x / 2.f - text.getLocalBounds().width / 2.f, window.getSize().y / 2.f - text.getLocalBounds().height / 2.f);
                    }
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
                {
                    textEntered = true;
                }
            }

            // Blinking cursor
            if (cursorTimer.getElapsedTime().asSeconds() > 0.5f)
            {
                cursorVisible = !cursorVisible;
                cursorTimer.restart();
            }
            cursor.setPosition(text.findCharacterPos(inputText.size()));
            cursor.setFillColor(cursorVisible ? sf::Color::White : sf::Color::Transparent);

            window.clear();
            sprint.draw();
            window.draw(text);
            window.draw(cursor);
            window.display();
        }

        if constexpr (std::is_same_v<T, std::string>)
            input = inputText;
        else if constexpr (std::is_same_v<T, char>)
            input = inputText.empty() ? '\0' : inputText[0];
        else if constexpr (std::is_same_v<T, int>)
            input = std::stoi(inputText);
        else if constexpr (std::is_same_v<T, double>)
            input = std::stod(inputText);
        reset();
    }
    int choice(const char* text1, const char* text2, int ans1 = 1, int ans2 = 2)
    {
        sf::Vector2i mousePos;
        Button choice1(window.getSize().x / 2.f - 100 - 200, window.getSize().y / 2.f - 50, 200, 100, &textFont, text1, 50, sf::Color::Black, sf::Color(50, 50, 50, 255), sf::Color::Green, sf::Color(255, 255, 255, 230), sf::Color::White, sf::Color::Black);
        Button choice2(window.getSize().x / 2.f + 100, window.getSize().y / 2.f - 50, 200, 100, &textFont, text2, 50, sf::Color::Black, sf::Color(50, 50, 50, 255), sf::Color::Red, sf::Color(255, 255, 255, 230), sf::Color::White, sf::Color::Black);
        bool isClicked1 = false, isClicked2 = false;

        while (window.isOpen() && !textEntered)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    exit(0);
                }
                if (event.type == sf::Event::MouseMoved)
                {
                    mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    isClicked1 = choice1.isClickedEvent(mousePos, event);
                    isClicked2 = choice2.isClickedEvent(mousePos, event);
                }
                event = sf::Event();
            }
            

            window.clear();
            choice1.render(window);
            choice2.render(window);
            sprint.draw();
            window.display();

            if (isClicked1)
            {
                sf::sleep(sf::milliseconds(500));
                return ans1;
            }
            if (isClicked2)
            {
                sf::sleep(sf::milliseconds(500));
                return ans2;
            }
        }

        choice1.update(mousePos, event);
        choice2.update(mousePos, event);
    }

} input(mainWindow);


#endif