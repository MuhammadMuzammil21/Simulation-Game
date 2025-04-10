#ifndef PROJECTINCLUDES_H
#define PROJECTINCLUDES_H

// Library includes
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <cmath>
#include <string>
#include <type_traits>
using namespace std;

// SFML Includes
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Global window initialization.
sf::RenderWindow mainWindow(sf::VideoMode(1000, 720), "Thrill of Decision: The Laptop Adventure", sf::Style::Close | sf::Style::Titlebar);

// Custom header files
#include "Button.h"
#include "GridOfButtons.h"
#include "StoryPrinter.h"
#include "inputer.h"
#include "abstractClass.h"
#include "Minesweeper.h"
#include "GridGame.h"
#include "DoorGame.h"
#include "Player&Story.h"

#endif // !INCLUDES