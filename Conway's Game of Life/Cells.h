#pragma once

#include <SFML/Graphics.hpp>

class Cells
{
public:
	Cells(const int& matrixSize, const float& cellSize, const sf::Color& fillColour, const sf::Color& backgroundColour, const sf::Color& outlineColour, const int& outlineThickness, const int& windowBorder);
	~Cells();
	void init();
	void draw(sf::RenderWindow& window);
	void updateDisplay();
	void updateState();
	void update();
	int neighbourCount(const int& x, const int& y) const;
	void randomize();

private:
	enum class m_State { dead, alive };
	struct Cell
	{
		sf::RectangleShape cell;
		m_State state = m_State::dead;
	};

	Cell* cells;
	m_State* buffer;

	const int& matrixSize;
	const int arraySize;
	const float cellSize;
	const int& windowBorder;
	const int outlineThickness;
	const sf::Color fillColour;
	const sf::Color backgroundColour;
	const sf::Color outlineColour;

private:
	m_State fate(const int& x, const int& y) const;
};

