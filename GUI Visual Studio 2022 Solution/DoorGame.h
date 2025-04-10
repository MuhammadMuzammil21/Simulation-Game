#ifndef DOORGAME_H
#define DOORGAME_H

class DoorGame : public Game
{
private:
    int correctDoor;
    int trapDoor;
    bool chosen = false;

    int chooseDoor() // GUI For Door game
    {
        sf::Texture redDoor, blueDoor;
        sf::Vector2i mousePos;
        redDoor.loadFromFile("assets/redDoor.png"); blueDoor.loadFromFile("assets/blueDoor.png");
        float winW = mainWindow.getSize().y;
        Button buttonRed((winW / 2) + 150 + 122, mainWindow.getSize().y / 2 - 284 / 2, 122, 283, nullptr, "", 0, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, redDoor, sf::Color::Transparent, sf::Color(255, 255, 255, 128), sf::Color::White, 2);
        Button buttonBlue((winW / 2) - 150, mainWindow.getSize().y / 2 - 284 / 2, 130, 284, nullptr, "", 0, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, blueDoor, sf::Color::Transparent, sf::Color(255, 255, 255, 128), sf::Color::White, 2);
        bool isRedPressed = false;
        bool isBluePressed = false;
        
        sf::Event event = sf::Event();
        while (mainWindow.isOpen() && !chosen)
        {
            while (mainWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    mainWindow.close();
                    exit(1);
                }
                else if (event.type == sf::Event::MouseMoved)
                    mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    isRedPressed = buttonRed.isClickedEvent(mousePos, event);
                    if (isRedPressed) return 2;
                    isBluePressed = buttonBlue.isClickedEvent(mousePos, event);
                    if (isBluePressed) return 1;
                }
            }
            buttonRed.update(mousePos, sf::Event());
            buttonBlue.update(mousePos, sf::Event());
            mainWindow.clear();
            buttonBlue.render(mainWindow);
            buttonRed.render(mainWindow);
            mainWindow.display();
        }
    }
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
        sprint << "Welcome to The Door game!";
        sprint << "You are presented with two doors: Door 1 and Door 2.";
        sprint << "Behind each door lies how I move forward reminding you of who you are. CHOOSE WISELY!!.";

        while (true)
        {
            sprint << "Choose a door (1 or 2):";
            chosenDoor = chooseDoor();

            if (chosenDoor == 1 || chosenDoor == 2)
            {
                break;
            }
            sprint << "Invalid input. Please choose either Door 1 or Door 2.";
        }

        sprint.clear();
        if (chosenDoor == correctDoor)
        {
            sprint << "Lets move Foward.. We'll know how this choice effects you..";
            return 1;
        }
        else if (chosenDoor == trapDoor)
        {
            sprint << "Lets move Foward.. We'll know how this choice effects you..";
            return 0;
        }
        return 2;
    }
};


#endif