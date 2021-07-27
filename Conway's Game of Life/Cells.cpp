#include "Cells.h"

#include <SFML/Graphics.hpp>

Cells::Cells(
	const int& matrixSize,
	const float& cellSize,
	const sf::Color& fillColour = sf::Color::Green,
	const sf::Color& backgroundColour = sf::Color::White,
	const sf::Color& outlineColour = sf::Color::Black,
	const int& outlineThickness = 0,
	const int& windowBorder = 0
)
	: matrixSize(matrixSize)
	, arraySize(matrixSize* matrixSize)
	, cellSize(cellSize)
	, fillColour(fillColour)
	, backgroundColour(backgroundColour)
	, outlineColour(outlineColour)
	, outlineThickness(outlineThickness)
	, windowBorder(windowBorder)
{
	cells = new Cell[arraySize];
}

Cells::~Cells()
{
	delete[] cells;
}

void Cells::init()
{
	float xPos = 0.0f, yPos = 0.0f;
	for (int i = 0; i < arraySize; i++)
	{
		cells[i].cell.setSize({ cellSize, cellSize });
		cells[i].cell.setFillColor(backgroundColour);
		cells[i].cell.setOutlineColor(outlineColour);
		cells[i].cell.setOutlineThickness(outlineThickness);
		xPos = windowBorder + outlineThickness;
		yPos = windowBorder + outlineThickness;
		xPos += float(int(i % matrixSize) * cellSize);
		yPos += float(int(i / matrixSize) * cellSize);
		cells[i].cell.setPosition({ xPos, yPos });
	}
}

void Cells::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < arraySize; i++)
		window.draw(cells[i].cell);
}

void Cells::update()
{
	for (int i = 0; i < arraySize; i++)
	{
		switch (cells[i].state)
		{
		case m_State::dead:
			cells[i].cell.setFillColor(backgroundColour);
			break;
		case m_State::alive:
			cells[i].cell.setFillColor(fillColour);
			break;
		}
	}
}

void Cells::randomize()
{
	for (int i = 0; i < arraySize; i++)
	{
		cells[i].state = m_State(rand() % 2);
	}
}
