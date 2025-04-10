#include "projectIncludes.h"


int main()
{    // Playing menu music
    sf::Music menuMusic;
    if (!menuMusic.openFromFile("assets/main menu music.ogg"))
        return -1; // error if no assets folder
    menuMusic.play();
    menuMusic.setVolume(55);

    // Loading the icon for the .exe file.
    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    mainWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Starting the story.
    Story s;
    s.mainMenu();

    
    return 0;
}