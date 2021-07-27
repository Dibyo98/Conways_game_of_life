#pragma once

#include <SFML/Graphics.hpp>

class Cells
{
public:
	Cells(const int& matrixSize, const float& cellSize, const sf::Color& fillColour, const sf::Color& backgroundColour, const sf::Color& outlineColour, const int& outlineThickness, const int& windowBorder);
	~Cells();
	void init();
	void draw(sf::RenderWindow& window);
	void update();
	void randomize();

private:
	enum class m_State { dead, alive };
	struct Cell
	{
		sf::RectangleShape cell;
		m_State state = m_State::dead;
	};
	Cell* cells;

	const int& matrixSize;
	const int arraySize;
	const float cellSize;
	const int& windowBorder;
	const int outlineThickness;
	const sf::Color fillColour;
	const sf::Color backgroundColour;
	const sf::Color outlineColour;
};

