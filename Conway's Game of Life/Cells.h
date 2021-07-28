#pragma once

#include <SFML/Graphics.hpp>

class Cells
{
public:
	Cells(
		const int& matrixSize,
		const float& cellSize,
		const int& windowBorder = 0,
		const int& outlineThickness = 0,
		const int& xOffset = 0,
		const int& yOffset = 0,
		const sf::Color& fillColour = sf::Color::Green,
		const sf::Color& backgroundColour = sf::Color::White,
		const sf::Color& outlineColour = sf::Color::Black
	);
	~Cells();
	void init();
	void draw(sf::RenderWindow& window);
	void updateDisplay();
	int updateState();
	int update();
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

	const int matrixSize;
	const int arraySize;
	const float cellSize;
	const int windowBorder;
	const int outlineThickness;
	const int xOffset;
	const int yOffset;
	const sf::Color fillColour;
	const sf::Color backgroundColour;
	const sf::Color outlineColour;
	int alive;

private:
	m_State fate(const int& x, const int& y) const;
};

