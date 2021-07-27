#include <iostream>
#include <SFML/Graphics.hpp>

#include "Cells.h"

constexpr unsigned int matrixSize = 16;
constexpr unsigned int windowBorder = 5;
constexpr unsigned int windowSize = 800;
constexpr unsigned int outlineThickness = 1;

const sf::Color backgroundColour = sf::Color::Black;
const sf::Color fillColour = sf::Color::Blue;
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
	cells.update();

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
		
		window.clear(backgroundColour);
		cells.draw(window);
		window.display();
	}

	return 0;
}