#ifndef STORYPRINTER_H
#define STORYPRINTER_H

#include "ProjectIncludes.h"

class StoryPrinter
{
    sf::Text LaptopText;
    sf::Text NarrationText;
    sf::Font LaptopFont;
    sf::Font NarrationFont;
    sf::Clock VisibleClock;
    sf::Clock DelayClock;
    sf::RenderWindow &window;
    sf::Event event = sf::Event();
    bool printing = false;
    bool isLaptop = false;
    const size_t DELAY;

public:
    StoryPrinter(sf::RenderWindow& window, int characterSize = 16, size_t DELAY = 35) : window(window), DELAY(DELAY)
    {
        LaptopFont.loadFromFile("assets/fonts/Alpharush.ttf");
        NarrationFont.loadFromFile("assets/fonts/Monorama-Medium.otf");
        LaptopText.setFont(LaptopFont);
        LaptopText.setCharacterSize(characterSize + 10);
        NarrationText.setFont(NarrationFont);
        NarrationText.setCharacterSize(characterSize);
    }
    StoryPrinter &operator<<(std::string story);
    StoryPrinter &operator<<(const int& number);
    void clear();
    void wait(size_t ammountOfMilliseconds);
    void waitPlus(size_t milliseconds);
    void draw();

} sprint(mainWindow);

StoryPrinter &StoryPrinter::operator<<(std::string story)
{
    int count = 1;
    window.clear(sf::Color::Black);
    printing = true;
    isLaptop = false;
    DelayClock.restart();
    int initialSize = 25;
    bool isFIN = false;
    float wsize = window.getSize().x;
    if (story.find("FIN") != std::string::npos && story.length() <= 5)
    {
        LaptopText.setString("FIN");
        LaptopText.setCharacterSize(150);
        LaptopText.setPosition(wsize / 2.f - LaptopText.getLocalBounds().width / 2, 100);
        LaptopText.setString("");
        isLaptop = true;
        isFIN = true;
    }
    else if (story[0] == '\"' && story[story.length() - 1] == '\"')
    {
        LaptopText.setCharacterSize(initialSize + 100);
        LaptopText.setString(story.substr(1, story.length() - 2));
        do
        {
            LaptopText.setCharacterSize(--initialSize + 100);
            LaptopText.setPosition(wsize / 2.f - LaptopText.getLocalBounds().width / 2, 100);
        } while (LaptopText.getLocalBounds().width >= wsize);
        LaptopText.setString("");
        isLaptop = true;
    }
    else
    {
        NarrationText.setString(story.substr(0, story.length() - 1));
        NarrationText.setCharacterSize(initialSize);
        do
        {
            NarrationText.setCharacterSize(--initialSize);
            NarrationText.setPosition(wsize / 2.f - NarrationText.getLocalBounds().width / 2, 585);
        } while (NarrationText.getLocalBounds().width >= wsize);
        NarrationText.setString("");
    }
    while (window.isOpen() && printing)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                count = story.length() - 2;
            }
        }

        if (DelayClock.getElapsedTime().asMilliseconds() >= DELAY && count <= story.length())
        {
            DelayClock.restart();
            if (isLaptop)
            {
                if (count < story.length() - 1)
                {
                    LaptopText.setString(story.substr(1, count));
                    VisibleClock.restart();
                }
            }
            else
            {
                NarrationText.setString(story.substr(0, count));
                VisibleClock.restart();
            }
            count++;
        }
        if (count >= story.length())
        {
            if (isFIN)
                wait(3000);
            if (VisibleClock.getElapsedTime().asMilliseconds() >= 900)
            {
                printing = false;
            }
        }
        window.clear();
        window.draw(LaptopText);
        window.draw(NarrationText);
        window.display();
    }
    return *this;
}

StoryPrinter &StoryPrinter::operator<<(const int& number)
{
    std::string story = std::to_string(number);
    int count = 1;
    window.clear(sf::Color::Black);
    printing = true;
    isLaptop = false;
    DelayClock.restart();
    int initialSize = 25;
    bool isFIN = false;
    float wsize = window.getSize().x;
    if (story.find("FIN") != std::string::npos && story.length() <= 5)
    {
        LaptopText.setString("FIN");
        LaptopText.setCharacterSize(150);
        LaptopText.setPosition(wsize / 2.f - LaptopText.getLocalBounds().width / 2, 100);
        LaptopText.setString("");
        isLaptop = true;
        isFIN = true;
    }
    else if (story[0] == '\"' && story[story.length() - 1] == '\"')
    {
        LaptopText.setCharacterSize(initialSize + 100);
        LaptopText.setString(story.substr(1, story.length() - 2));
        do
        {
            LaptopText.setCharacterSize(--initialSize + 100);
            LaptopText.setPosition(wsize / 2.f - LaptopText.getLocalBounds().width / 2, 100);
        } while (LaptopText.getLocalBounds().width >= wsize);
        LaptopText.setString("");
        isLaptop = true;
    }
    else
    {
        NarrationText.setString(story.substr(0, story.length() - 1));
        NarrationText.setCharacterSize(initialSize);
        do
        {
            NarrationText.setCharacterSize(--initialSize);
            NarrationText.setPosition(wsize / 2.f - NarrationText.getLocalBounds().width / 2, 600);
        } while (NarrationText.getLocalBounds().width >= wsize);
        NarrationText.setString("");
    }
    while (window.isOpen() && printing)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                count = story.length() - 2;
            }
        }

        if (DelayClock.getElapsedTime().asMilliseconds() >= DELAY && count <= story.length())
        {
            DelayClock.restart();
            if (isLaptop)
            {
                if (count < story.length() - 1)
                {
                    LaptopText.setString(story.substr(1, count));
                    VisibleClock.restart();
                }
            }
            else
            {
                NarrationText.setString(story.substr(0, count));
                VisibleClock.restart();
            }
            count++;
        }
        if (count >= story.length())
        {
            if (isFIN)
                wait(3000);
            if (VisibleClock.getElapsedTime().asMilliseconds() >= 1500)
            {
                printing = false;
            }
        }
        window.clear();
        window.draw(LaptopText);
        window.draw(NarrationText);
        window.display();
    }
    return *this;
}

void StoryPrinter::clear()
{
    LaptopText.setString("");
    NarrationText.setString("");
    window.clear(sf::Color::Black);
    window.display();
}

inline void StoryPrinter::wait(size_t ammountOfMilliseconds)
{
    bool waiting = true;
    sf::Clock waitClock;
    while (window.isOpen() && waiting)
    {
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        if (waitClock.getElapsedTime().asMilliseconds() >= ammountOfMilliseconds)
            waiting = false;
    }
}

inline void StoryPrinter::waitPlus(size_t milliseconds)
{
    sf::Event event;
    sf::Clock waitClock;
    bool waiting = true;
    while (mainWindow.isOpen() && waiting)
    {
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                std::exit(0);
            }
        }
        if (waitClock.getElapsedTime().asMilliseconds() >= milliseconds)
        {
            waiting = false;
        }
    }
}

void StoryPrinter::draw()
{
    window.draw(LaptopText);
    window.draw(NarrationText);
}

#endif