#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(400, 400), "Window");
	sf::RectangleShape rect(sf::Vector2f(300.0f, 100.0f));
	rect.setFillColor(sf::Color::Cyan);
	while (window->isOpen())
	{
		sf::Event m_event;

		while (window->pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				window->close();
			}
		}
		window->clear();
		window->draw(rect);
		window->display();

	}
	delete window;
	window = NULL;
}