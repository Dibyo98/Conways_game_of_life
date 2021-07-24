#include <iostream>

#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Conway's Game of Life", sf::Style::Close);
	sf::CircleShape circle(200.0f);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	circle.setFillColor(sf::Color::Red);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			}
		}
		
		window.clear(sf::Color::White);
		window.draw(circle);
		window.display();
	}

	return 0;
}