#include <iostream>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Cells.h"

constexpr float updatePerSecond = 2.0f;

constexpr unsigned int matrixSize = 64;
constexpr unsigned int windowBorder = 5;
constexpr unsigned int windowSize = 800;
constexpr unsigned int outlineThickness = 1;

constexpr unsigned int topOffset = 25;
constexpr unsigned int leftOffset = 0;
constexpr unsigned int bottomOffset = 0;
constexpr unsigned int rightOffset = 0;

const sf::Color backgroundColour = sf::Color::Black;
const sf::Color fillColour = sf::Color::Green;
const sf::Color outlineColour = sf::Color::White;

constexpr unsigned int arraySize = matrixSize * matrixSize;
constexpr float cellSize = float(windowSize - windowBorder * 2 - outlineThickness * 2) / float(matrixSize);

int main()
{
	srand((unsigned int)time(NULL));
	sf::RenderWindow window(sf::VideoMode(windowSize + leftOffset + rightOffset, windowSize + topOffset + bottomOffset), "Conway's Game of Life", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	Cells cells(matrixSize, cellSize, windowBorder, outlineThickness, leftOffset, topOffset, fillColour, backgroundColour, outlineColour);
	cells.init();
	cells.randomize();
	cells.updateDisplay();

	sf::Event event;
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.0f / updatePerSecond);
	int generation = 0;
	int alive = 0, dead = 0, total = arraySize;

	sf::Font font;
	if (!font.loadFromFile("Monaco Regular.ttf"))
	{
		std::cout << "Font file not found" << std::endl;
		return 0;
	}
	sf::Text statusBar;
	std::stringstream statusText;
	statusBar.setPosition({ windowBorder, windowBorder });
	statusBar.setFont(font);
	statusBar.setCharacterSize(14);
	statusBar.setFillColor(outlineColour);

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
			alive = cells.update();

			dead = total - alive;
			generation++;
			std::stringstream().swap(statusText);
			statusText << "Generation: " << generation << "\tAlive/Dead/Total: " << alive << "/" << dead << "/" << total;
			statusText << "\t" << std::fixed << std::setprecision(2) << float(float(alive) / float(total) * 100) << "% alive";
			statusBar.setString(statusText.str());

			window.clear(backgroundColour);
			cells.draw(window);
			window.draw(statusBar);
			window.display();
		}
		accumulator += clock.restart();
	}

	return 0;
}