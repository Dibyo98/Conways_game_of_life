#include <iostream>
#include <SFML/Graphics.hpp>

#include "Cells.h"

constexpr float updatePerSecond = 2.0f;

constexpr unsigned int matrixSize = 64;
constexpr unsigned int windowBorder = 5;
constexpr unsigned int windowSize = 800;
constexpr unsigned int outlineThickness = 1;

const sf::Color backgroundColour = sf::Color::Black;
const sf::Color fillColour = sf::Color::Green;
const sf::Color outlineColour = sf::Color::White;

constexpr unsigned int arraySize = matrixSize * matrixSize;
constexpr float cellSize = float(windowSize - windowBorder * 2 - outlineThickness * 2) / float(matrixSize);

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Conway's Game of Life", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	Cells cells(matrixSize, cellSize, fillColour, backgroundColour, outlineColour, outlineThickness, windowBorder);
	cells.init();
	cells.randomize();
	cells.updateDisplay();

	sf::Event event;
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.0f / updatePerSecond);

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

		while (accumulator > ups)
		{
			accumulator -= ups;
			cells.update();

			window.clear(backgroundColour);
			cells.draw(window);
			window.display();
		}
		accumulator += clock.restart();
	}

	return 0;
}