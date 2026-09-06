// MidGame.cpp : Defines the entry point for the application.
//

#include "MidGame.h"
#include "src/Utilities/Utils.h"
#include "src/Game/Player.h"
#include "src/Game/Game.h"

using namespace std;

int main()
{
	// system params
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "MidGame");
	sf::Clock clock;

	Game gameInstance(window);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				gameInstance.KeyPressed(keyPressed->scancode);
			}
			if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				gameInstance.KeyReleased(keyReleased->scancode);
			}
		}

		float deltaTime = clock.restart().asSeconds();
		gameInstance.Update(deltaTime);
		

		window.clear();
		gameInstance.Draw();
		window.display();
	}

	return 0;
}
