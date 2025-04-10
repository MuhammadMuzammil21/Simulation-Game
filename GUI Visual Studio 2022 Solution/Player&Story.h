class Player
{
public:
	string name;
	int age = -1;
	char Checkpoint = 0;
	string MI6code;
	int health = 3;
	void getInfo();
};

void Player::getInfo()
{
	sprint << "Enter your name: ";
	input >> name;
	sprint.clear();
	sprint << "Enter your age: ";
	input >> age;
	sprint.clear();
	MI6code = name[0] + to_string(age + 11);
}

class Story
{
	Player p;
	GridGame g;
	// Minesweeper m; // Initialized in playing function to reset everytime play() is called. + This also saves memory.
	DoorGame d;
	int ch = 0;
	int answer = 0;
	string str;

public:
	Story();

	void mainMenu();
	void newGame();
	void loadGame();

	void storyInitial();
	void storyPositive();
	void storyPositiveEnd();
	void storyNeagtive();
	void storyNeagtiveEnd();
	int save(char x);
	void filing();
	int reading();
	void endcredits();
	void showPic(const char* fileName);
};

Story::Story()
{
	mainWindow.setVerticalSyncEnabled(true);
}

int Story::save(char x)
{
	sprint.clear();
	sprint << "Do you want to save or continue the game?\n1. Save and Continue\n2. Save and Exit";
	input >> ch;
	sprint.clear();
	p.Checkpoint = x;
	filing();
	switch (ch)
	{
	case 2:
		sprint << "Saving . . .";
		return 1;
		break;
	case 1:
		sprint << "Continue . . .";
		break;
	}
	return 0;
}

void Story::filing()
{
	string fname;
	fname = p.name + ".txt";
	fstream f(fname, ios::out);
	f.write((char*)&p, sizeof(Player));
	sprint.clear();
	// sprint << "filing . . .";
	f.close();
}

int Story::reading()
{
	string fname;
	fname = p.name + ".txt";
	fstream g(fname, ios::in);
	g.seekg(0);
	g.read((char*)&p, sizeof(Player));
	if (!g)
	{
		sprint.clear();
		sprint << "Loaded game not found.";
		return 1;
	}
	sprint.clear();
	sprint << "reading . . .";
	// sprint << p.name << p.age << p.Checkpoint << p.MI6code << p.health;
	g.close();
	return 0;
}

void Story::mainMenu()
{
	sf::Texture LaptopTexture;
	LaptopTexture.loadFromFile("assets/Laptop on desk.jpeg");


	bool titleDone = false;

	sf::Sprite MenuBackground(LaptopTexture);
	MenuBackground.setScale(0.5f, 0.5f);
	MenuBackground.setOrigin(960, 920);
	MenuBackground.setPosition(480, 460);

	enum GAME_STATES
	{
		TITLE,
		MAIN_MENU,
		TRANSITION,
		NEW_GAME,
		LOAD_GAME,
		EXIT
	} currentState = TITLE;

	sf::Font MenuButtonFont;
	MenuButtonFont.loadFromFile("assets/fonts/Monorama-Medium.otf");
	sf::Font MinesweeperFont;
	MinesweeperFont.loadFromFile("assets/fonts/SummerPixel.ttf");
	sf::Font TitleFont;
	TitleFont.loadFromFile("assets/fonts/Phage Rough.otf");

	sf::Text Title1("THRILL OF DECISION", TitleFont, 80);
	sf::Text Title2("The Laptop Adventure", TitleFont, 40);
	Title1.setPosition(mainWindow.getSize().x / 2.f - Title1.getLocalBounds().width / 2.f, mainWindow.getSize().y / 2.f - Title1.getLocalBounds().height / 2.f - 40);
	Title2.setPosition(mainWindow.getSize().x / 2.f - Title2.getLocalBounds().width / 2.f, mainWindow.getSize().y / 2.f - Title2.getLocalBounds().height / 2.f + 40);

	bool startClicked = false, MousePressed = false, NewGamePressed = false, LoadGamePressed = false, ExitPressed = false;
	sf::Vector2i mousePos;

	sf::Color gray(224, 224, 224, 224);
	Button NewGameButton(100, 100, 100, 25, &MenuButtonFont, "New Game", 24, sf::Color(224, 224, 224, 224), sf::Color::White, sf::Color(124, 124, 124, 224), sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
	Button LoadGameButton(100, 160, 110, 25, &MenuButtonFont, "Load Game", 24, sf::Color(224, 224, 224, 224), sf::Color::White, sf::Color(124, 124, 124, 224), sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
	Button ExitButton(100, 220, 50, 25, &MenuButtonFont, "EXIT", 24, sf::Color(224, 224, 224, 224), sf::Color::White, sf::Color(124, 124, 124, 224), sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

	sf::Clock TransitionClock;
	float scale = 0;
	sf::Event event;

	while (mainWindow.isOpen())
	{
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();

			if (event.type == sf::Event::MouseMoved)
			{
				mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
			}

			if (event.type == sf::Event::MouseButtonPressed && currentState != EXIT)
			{
				NewGamePressed = NewGameButton.isClickedEvent(mousePos, event);
				LoadGamePressed = LoadGameButton.isClickedEvent(mousePos, event);
				ExitPressed = ExitButton.isClickedEvent(mousePos, event);
			}
		}

		switch (currentState)
		{
		case TITLE:
		{
			mainWindow.clear();
			unsigned int time = TransitionClock.getElapsedTime().asMilliseconds();
			if (!titleDone)
			{
				TransitionClock.restart();
				titleDone = true;
			}
			if (time <= 4000)
			{
				Title1.setFillColor(sf::Color(255, 255, 255, (time <= 1500 ? time / 6 : 255)));
				Title2.setFillColor(sf::Color(255, 255, 255, (time <= 1500 ? time / 6 : 255)));

			}
			else
				currentState = MAIN_MENU;
			mainWindow.draw(Title1);
			mainWindow.draw(Title2);
			break;
		}
		case MAIN_MENU:
		{
			//window.clear(sf::Color(0, 0, 0, (TransitionClock.getElapsedTime().asMilliseconds() > 4000 && TransitionClock.getElapsedTime().asMilliseconds() <= 6000) ? (TransitionClock.getElapsedTime().asMilliseconds() - 4000) / 8 : 255));
			NewGamePressed = NewGameButton.isClickedEvent(mousePos, event);
			LoadGamePressed = LoadGameButton.isClickedEvent(mousePos, event);
			ExitPressed = ExitButton.isClickedEvent(mousePos, event);

			mainWindow.draw(MenuBackground);
			LoadGameButton.render(mainWindow);
			ExitButton.render(mainWindow);
			NewGameButton.render(mainWindow);

			if (NewGamePressed)
			{
				currentState = TRANSITION;
			}
			if (LoadGamePressed)
			{
				currentState = LOAD_GAME;
			}
			if (ExitPressed)
			{
				currentState = EXIT;
			}
			break;
		}
		case TRANSITION:
		{
			mainWindow.clear();
			if (scale == 0)
				TransitionClock.restart();
			if (TransitionClock.getElapsedTime().asMilliseconds() <= 2500)
			{
				scale = 1 + 0.5 * sinf(TransitionClock.getElapsedTime().asMilliseconds() * std::_Pi / 10000);
				MenuBackground.scale(scale, scale);
			}
			else
				currentState = NEW_GAME;
			mainWindow.draw(MenuBackground);
			break;
		}
		case NEW_GAME:
		{
			newGame();
			currentState = EXIT;
			break;
		}
		case LOAD_GAME:
		{
			loadGame();
			currentState = EXIT;
			break;
		}
		case EXIT:
		{
			endcredits();
			sf::Text exit("Exiting", MenuButtonFont, 50);
			exit.setPosition(420, 330);
			sf::Clock clock;
			int count = 0;
			while (mainWindow.isOpen())
			{
				if (clock.getElapsedTime().asMilliseconds() > 700)
				{
					clock.restart();
					exit.setString(exit.getString() + '.');
					count++;
					if (count == 4)
					{
						mainWindow.close();
						std::exit(0);
					}
				}
				mainWindow.clear();
				mainWindow.draw(exit);
				mainWindow.display();
			}
			break;
		}
		default:
			break;
		}
		mainWindow.display();
	}

}

void Story::newGame()
{
	sprint.clear();
	int check = 0;
	storyInitial();
	if (save('i') == 1)
	{
		return;
	}
	// Door Game
	ch = d.play();
	switch (ch)
	{
	case 1:
		// POSITIVE DIRECTION
		storyPositive();
		if (save('g') == 1)
		{
			return;
		}
		while (p.health > 0)
		{
			ch = g.play();
			if (ch == 1)
			{
				check = 1;
				break;
			}
			else
			{
				sprint.clear();
				p.health--;
				sprint << "Remaining Health: ";
				sprint << p.health;
			}
		}
		if (check == 0)
		{
			sprint.clear();
			sprint << "\"You disappointed me.....\"";
			sprint.clear();
			sprint << "\"FIN\"";
			endcredits();
			return;
		}
		if (save('p') == 1)
		{
			return;
		}
		storyPositiveEnd();
		break;
	case 0:
		// NEGATIVE DIRECTION
		storyNeagtive();
		if (save('m') == 1)
		{
			return;
		}
		while (p.health > 0)
		{
			Minesweeper m;
			sprint.clear();
			ch = m.play();
			if (ch == 1)
			{
				check = 1;
				break;
			}
			else
			{
				sprint.clear();
				p.health--;
				sprint << "Remaining Health: ";
				sprint << p.health;
			}
		}
		if (check == 0)
		{
			sprint.clear();
			sprint << "\"You disappointed me.....\"";
			sprint.clear();
			sprint << "\"FIN\"";
			endcredits();
			return;
		}
		if (save('n') == 1)
		{
			return;
		}
		storyNeagtiveEnd();
		break;
	}
}

void Story::loadGame()
{
	sprint.clear();
	int check = 0;
	sprint << "Enter your name of loaded game: ";
	input >> p.name;
	if (reading() == 1)
	{
		return;
	}
	sprint.clear();
	switch (p.Checkpoint)
	{
	case 'i':
		goto DOORGAME;
		break;
	case 'p':
		goto POSITIVE;
		break;
	case 'n':
		goto NEGATIVE;
		break;
	case 'g':
		goto GRIDGAME;
		break;
	case 'm':
		goto MINESWEEPER;
		break;
	}

	storyInitial();
	if (save('i') == 1)
	{
		return;
	}

	// Door Game
DOORGAME:
	ch = d.play();
	switch (ch)
	{
	case 1:
		// POSITIVE DIRECTION
		storyPositive();
		if (save('g') == 1)
		{
			return;
		}
	GRIDGAME:
		while (p.health > 0)
		{
			ch = g.play();
			if (ch == 1)
			{
				check = 1;
				break;
			}
			else
			{
				sprint.clear();
				p.health--;
				sprint << "Remaining Health: " << p.health;
				//					if (save('g') == 1){
				//						return;
				//					}
				sprint.wait(3000);
			}
		}
		if (check == 0)
		{
			sprint.clear();
			sprint << "\"You disappointed me.....\"";
			sprint.clear();
			sprint << "\"FIN\"";
			endcredits();
			return;
		}
		if (save('p') == 1)
		{
			return;
		}
	POSITIVE:
		storyPositiveEnd();
		break;
	case 0:
		// NEGATIVE DIRECTION
		storyNeagtive();
		if (save('m') == 1)
		{
			return;
		}
	MINESWEEPER:
		while (p.health > 0)
		{
			Minesweeper m;
			ch = m.play();
			if (ch == 1)
			{
				check = 1;
				break;
			}
			else
			{
				sprint.clear();
				p.health--;
				sprint << "Remaining Health: ";
				sprint << p.health;
				//  if (save('m') == 1){
				//		return;
				//  }
			}
		}
		if (check == 0)
		{
			sprint.clear();
			sprint << "\"You disappointed me.....\"";
			sprint.clear();
			sprint << "\"FIN\"";
			endcredits();
			return;
		}
		if (save('n') == 1)
		{
			return;
		}
	NEGATIVE:
		storyNeagtiveEnd();
		break;
	}
}

void Story::storyInitial()
{

	p.getInfo();
	sprint.clear();
	sprint.wait(2000);
	sprint << "The life in the prison cell was unnerving with a dead routine that kept continuing like there was no end.";
	sprint.clear();
	sprint << "But this time something was off about the whole day. The inmates all worried , some petrified and others.";
	sprint << "Just baffled to the discovery they made in their cells. I(Andrew) was going to know what was going on.";
	sprint.clear();
	// the pov screen of his cell view appears
	sprint << "5 years in the same cell and decades more to go, I never expected to find a laptop in my cell awaiting me.";
	sprint << "Even the Grim Reaper wouldnt have been surprise for me because I had to recognise of my past or if I had a family.";
	sprint << "Andrew walks towards set up that magically appeared in his room\nand the laptop shows a black screen with a message displaying ";
	// Laptoop zoom in
	sprint.clear();
	sprint << "\"Hi Andrew... lets play a game?\"";
	// Deprived of any mode of entertainment and interaction with outside world, a little skeptical , he types back hello.
	sprint.clear();
	sprint << "\"Your name is Andrew isnt it?\"";
	answer = input.choice("YES", "NO");
	if (answer == 2)
	{
		sprint.clear();
		sprint << "\"Oh, You don't need to lie to me. I know who you are.\n But never mind. People usually says lie when they face some strange circumstances.\"";
	}
	sprint.clear();
	sprint << "\"Do you remember when were you were born\"";
	answer = input.choice("YES", "NO");
	sprint.clear();
	sprint << "\"Seems like you dont remember anything... Dont worry, everything with be known.\"";
	sprint.clear();
	sprint << "Andrew feels a chill run down his spine as he watches the laptop's screen.\nHe has no idea what this game is or who is behind it,\n but he is intrigued nonetheless.";
	sprint.clear();
	sprint << "\"You are not who you think you are.\"";
	sprint.clear();
	sprint << "\"You have been living a lie. Your entire life has been a simulation.\nYour memories, your family, everything you thought you knew is a fabrication\nAnd now, you have a chance to escape.\"";
	sprint.clear();
	sprint << "Andrew's heart is pounding in his chest as he reads the messages on the screen. \nHe can feel his mind spinning, trying to make sense of what he is being told.";
	sprint << "\"What do you mean a simulation? How is that even possible?\" The laptop responds almost immediately.";
	sprint.clear();
	sprint << "\"You are part of an experiment. A project designed to simulate human behavior and consciousness.\nThe world you know is not real. It is a construct designed to test the limits of the human mind.\"";
	sprint.clear();
	sprint << "\"But you have been selected to participate in a different kind of experiment.\nAn experiment to see if you can break free from the simulation and discover the truth.\"";
	sprint.clear();
	sprint << "\"Now lets Begin. Be cautious about you have only three life chances.\"";
	sprint.clear();
}

void Story::storyPositive()
{
	
	sprint.clear();
	sprint.wait(2000);
	// After decoding the game responds with
	sprint << "\"Great job , you are very lucky man....\"";
	// The game pauses while Andrew tries to make sense of the response.
	sprint.clear();
	sprint << "\"Yes Andrew.. You were a undercover for MI6 stationed at the Kremlin..\"";
	sprint.clear();
	sprint << "A picture in uniform displays with man in his early 20s which in a moment Andrew realises is himself.\nEvery blurred memory that had bothered him started making sense.";
	//ADD A PICTURE OF A GUY IN UNIFORM
	showPic("assets/andrew.jpg");
	sprint.clear();
	sprint << "\"Moving On. You didnt happen to see how this device was placed in your cell did you?\"";
	answer = input.choice("YES", "NO");
	sprint.clear();
	if (answer == 1)
	{
		// If Yes, a loud noise is heard and a man's cry is heard for a split second. the program displays
		sf::Music gunshot;
		gunshot.openFromFile("assets/gunShot.ogg");
		gunshot.play();
		sprint << "\"Liability Terminated\"";
		sprint.wait(400);
		sprint.clear();
		sprint << "A gunshot is sounded and Andrew gets scared.\nSomeone is shot dead.";
		sprint.wait(1000);
		sprint.clear();
	}
	// If No, the program proceeds without a message.
	sprint << "\"Who has the Access to your cell except you.\n-There are no gaurds\n-Your food is served in the food hall\n-Inmates are not allowed to interact\"";
	sprint << "(1)The people in control\n(2)The laptop was hidden in a secret compartment in the room from the begginng\n(3) I dont know";
	input >> answer;
	sprint.clear();
	//"The correct answer being (c) I dont know but due to the health lives on the line this easy desicion is going to be very hard."
	switch (answer)
	{
	case 1:
	case 2:
		p.health--;
		sprint << "Remaining Health: " << p.health;
		sprint.wait(3000);
		sprint.clear();
		sprint << "\"You were never like this Andrew.. you had the courage to stick with the facts.\nProbably these changes cost them their lives..\"";
		//ADD PICTURE OF TWO BODIES
		showPic("assets/two.jpg");
		sprint << "The program then displays a distorted picture , a bloody one that has a dead bodies of two people very familiar to Andrew.";
		sprint << "\"Unfortunately you are right.. It is your parents...\"";
		break;
	case 3:
		break;
	}
	sprint.clear();
	sprint << "\"Get yourself Together... You are in the last stages of this...\nGiving up will only lead to more casualties..\"";
}

void Story::storyPositiveEnd()
{

	sprint.clear();
	sprint.wait(2000);
	sprint << "\"You are too close seeing the end...\"";
	sprint.clear();
	sprint << "\"All these questions uptil now have been very random and out of context.... But its the end now.\nHeres your last test...\"";
	while (p.health > 0)
	{
		sprint.clear();
		sprint << "\"What was your call code in MI6?\"";
		if (p.health == 1)
		{
			sprint << "\"Be aware of your life. You have only last chance.\nSo I will show you a mercy by giving you some clue.\n(Hint: It is three letters and related to user Name and age(+11) which is saved)\"";
		}
		input >> str;
		sprint.clear();
		if (str == p.MI6code)
		{
			sprint << "\"You passed.. You can ask me anything you like.\"";
			sprint.clear();
			sprint << "At this , with a sigh of relief Andrew types \"Who are you ??\" The program answers...";
			sprint.wait(1000);
			sprint.clear();
			sprint << "\"I am you.\"";
			sprint.clear();
			// "Cliff hanger.";
			sprint << "\"FIN\"";
			endcredits();
			return;
		}
		else
		{
			p.health--;
			sprint << "Remaining Health: " << p.health;
			sprint.wait(3000);
			if (p.health == 0)
			{
				sprint.clear();
				sprint << "\"You disappointed me.....\"";
				sprint.clear();
				sprint << "\"FIN\"";
				endcredits();
				return;
			}
		}
	}
}

void Story::storyNeagtive()
{

	sprint.clear();
	sprint.wait(2000);
	sprint << "\"Nice going there. Just like old times when you played these games with your friends..\n unfortunate not to be with you anymore..\"";
	sprint.clear();
	sprint << "A picture of a couple of guys shows up with blood stained on them.";
	//ADD PICTURE OF THREE GUYS WITH BLOOD STAINS
	showPic("assets/threeGuys.jpg");
	sprint.clear();
	sprint << "\"They your friends right? Dont worry they still alive.\nBARELY...\"";
	sprint.clear();
	sprint << "\"Lets make it more interesting\"";
	sprint.clear();
	sprint << "\"You familiar with Minesweeper right?\nA puzzle game where the player tries to clear a minefield without detonating any mines.\"";
	sprint.clear();
	sprint << "\"Only change is you denote a mine you loose a life.. Enjoy\"";
	sprint.clear();
}

void Story::storyNeagtiveEnd()
{

	sprint.clear();
	sprint.wait(2000);
	sprint << "\"Well done, Guess it brings out the best in you when your life is on the line?\"";
	sprint.clear();
	sprint << "\"But dont worry its almost the end of the line for us, it's your Last Test.\"";
	while (p.health > 0)
	{
		sprint.clear();
		sprint << "\"What was your call code in MI6?\"";
		if (p.health == 1)
		{
			sprint << "\"Be aware of your life. You have only last chance.\nSo I will show you a mercy by giving you some clue.\n(Hint: It is three letters and related to user Name and age(+11) which is saved)\"";
		}
		input >> str;
		sprint.clear();
		if (str == p.MI6code)
		{
			sprint << "\"You really desperate to get out yet you left it unnoticed that even though you answered the first question right ,\nit wasnt what it was supposed to be and you lost a life there.. \"";
			sprint.clear();
			sprint << "\"It made me take you in whole different direction. \nNot the direction you were quiet looking forward to...\"";
			sprint.clear();
			sprint << "\"A little disappointed But I HAD FUNN.. I am going to miss you...\"";
			sprint.clear();
			sprint << "The self destruct sequence intiates..";
			//ADD a Counter from 5 to 1 if possible
			sprint.clear();
			sprint << "\"5\"";
			sprint << "\"4\"";
			sprint << "\"3\"";
			sprint << "\"2\"";
			sprint << "\"1\"";
			sprint.clear();
			sprint << "\"FIN.\"";
			endcredits();
			return;
		}
		else
		{
			p.health--;
			sprint << "Remaining Health: " << p.health;
			sprint.wait(3000);
			if (p.health == 0)
			{
				sprint.clear();
				sprint << "\"You disappointed me.....\"";
				sprint.clear();
				sprint << "\"FIN\"";
				endcredits();
				return;
			}
		}
	}
}

void Story::endcredits()
{
	sprint.wait(2000);
	std::string creditString = "Credits go to these LEGENDS\nAsim Majeed\nHeo Juseong\nMuhammad Muzammil";
	vector <sf::Text> creditTexts;
	sf::Font MenuButtonFont;
	MenuButtonFont.loadFromFile("assets/fonts/PrinceOutfitDemo.ttf");

	size_t i = 0, j = 0;
	while (i < creditString.length())
	{
		if (creditString[i] == '\n')
		{
			creditTexts.push_back(sf::Text(creditString.substr(j, i - j), MenuButtonFont, 35));
			j = i + 1;
		}
		i++;
	}
	creditTexts.push_back(sf::Text(creditString.substr(j), MenuButtonFont, 35));
	
	// centering all the lines:
	int gap = 15;
	i = 0;
	for (auto && text: creditTexts)
	{
		text.setPosition(mainWindow.getSize().x / 2.f - text.getLocalBounds().width / 2.f, mainWindow.getSize().y / 2.f - text.getLocalBounds().height + text.getLocalBounds().height * i + gap * i++);
		text.setFillColor(sf::Color::White);
	}
	bool printing = true;
	sf::Event event = sf::Event();
	sf::Clock MoveClock;
	while (mainWindow.isOpen() && printing)
	{
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mainWindow.close();
				exit(0);
			}
		}
		if (MoveClock.getElapsedTime().asMilliseconds() >= 15)
		{
			MoveClock.restart();
			for (auto&& text : creditTexts)
			{
				text.move(0, -1);
			}
		}
		mainWindow.clear();
		for (auto&& text : creditTexts)
		{
			mainWindow.draw(text);
		}
		mainWindow.display();
		if (creditTexts[creditTexts.size() - 1].getPosition().y < -50) {
			printing = false;
		}
	}
	return;
}


inline void Story::showPic(const char *fileName)
{
	sf::Image theImage;
	theImage.loadFromFile(fileName);
	sf::RectangleShape clearingRect;

	sf::Texture texture;
	texture.loadFromImage(theImage);
	sf::Sprite thePic;
	thePic.setTexture(texture, true);
	thePic.setScale(0.5f, 0.5f);
	clearingRect.setSize(sf::Vector2f(thePic.getLocalBounds().width, 512));

	sf::Color currentColor = thePic.getColor();
	currentColor.a = 0;
	thePic.setColor(currentColor);
	thePic.setPosition(mainWindow.getSize().x / 2.f - thePic.getLocalBounds().width / 4, 50);
	clearingRect.setPosition(thePic.getPosition());
	clearingRect.setFillColor(sf::Color::Black);

	float fadeInTime = 2.5f; // Time in seconds to fade in
	sf::Time fadeInterval = sf::seconds(1.0f / 60.0f); // Time between color updates
	int numFadeSteps = fadeInTime / fadeInterval.asSeconds(); // Number of color updates
	float alphaIncrement = 255.0f / numFadeSteps; // Alpha value change per update
	
	for (int i = 0; i < numFadeSteps; ++i)
	{
		currentColor.a += alphaIncrement;
		thePic.setColor(currentColor);
		mainWindow.draw(thePic);
		mainWindow.display();
		sprint.waitPlus(fadeInterval.asMilliseconds());
	}

	// Display the picture for a set duration
	float displayTime = 0.25f; // Time in seconds to display
	sf::Time displayInterval = sf::seconds(1.0f / 60.0f); // Time between updates
	int numDisplaySteps = displayTime / displayInterval.asSeconds(); // Number of updates
	for (int i = 0; i < numDisplaySteps; ++i)
	{
		mainWindow.draw(thePic);
		mainWindow.display();
		sprint.waitPlus(displayInterval.asMilliseconds());
	}

	// Fade out the picture
	float fadeOutTime = 2.5f; // Time in seconds to fade out
	int numFadeOutSteps = fadeOutTime / fadeInterval.asSeconds(); // Number of color updates
	float alphaDecrement = 255.0f / numFadeOutSteps; // Alpha value change per update
	
	for (int i = 0; i < numFadeOutSteps && currentColor.a > 0; ++i)
	{
		currentColor.a -= alphaDecrement;
		thePic.setColor(currentColor);
		mainWindow.draw(clearingRect);
		mainWindow.draw(thePic);
		mainWindow.display();
		sprint.waitPlus(fadeInterval.asMilliseconds());
	}
}
