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

			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePressed->button == sf::Mouse::Button::Left)
				{
					gameInstance.OnLeftBtnPressed(mousePressed->position);
				}
			}
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
			{
				gameInstance.OnMouseMoved(mouseMoved->position);
			}
			if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
			{
				if (mouseReleased->button == sf::Mouse::Button::Left)
				{
					gameInstance.OnLeftBtnReleased(mouseReleased->position);
				}
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
