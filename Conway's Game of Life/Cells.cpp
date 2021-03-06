#include "Cells.h"

#include <SFML/Graphics.hpp>

Cells::Cells(
	const int& matrixSize,
	const float& cellSize,
	const int& windowBorder,
	const int& outlineThickness,
	const int& xOffset,
	const int& yOffset,
	const sf::Color& fillColour,
	const sf::Color& backgroundColour,
	const sf::Color& outlineColour
)
	: matrixSize(matrixSize)
	, arraySize(matrixSize * matrixSize)
	, cellSize(cellSize)
	, windowBorder(windowBorder)
	, outlineThickness(outlineThickness)
	, xOffset(xOffset)
	, yOffset(yOffset)
	, fillColour(fillColour)
	, backgroundColour(backgroundColour)
	, outlineColour(outlineColour)
{
	cells = new Cell[arraySize];
	buffer = new m_State[arraySize];
	alive = 0;
}

Cells::~Cells()
{
	delete[] cells;
	delete[] buffer;
}

void Cells::init()
{
	float xPos = 0.0f, yPos = 0.0f;
	for (int i = 0; i < arraySize; i++)
	{
		cells[i].cell.setSize({ cellSize, cellSize });
		cells[i].cell.setFillColor(backgroundColour);
		cells[i].cell.setOutlineColor(outlineColour);
		cells[i].cell.setOutlineThickness(float(outlineThickness));
		xPos = float(xOffset + windowBorder + outlineThickness);
		yPos = float(yOffset + windowBorder + outlineThickness);
		xPos += float(int(i % matrixSize) * cellSize);
		yPos += float(int(i / matrixSize) * cellSize);
		cells[i].cell.setPosition({ xPos, yPos });
		cells[i].state = m_State::dead;
		buffer[i] = m_State::dead;
	}
}

void Cells::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < arraySize; i++)
		window.draw(cells[i].cell);
}

void Cells::updateDisplay()
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

int Cells::updateState()
{
	int alive = 0;
	int neighbourCount = 0;
	int x = 0, y = 0;
	for (int i = 0; i < arraySize; i++)
	{
		x = i % matrixSize;
		y = i / matrixSize;
		buffer[y * matrixSize + x] = fate(x, y);
	}

	for (int i = 0; i < arraySize; i++)
	{
		cells[i].state = buffer[i];
		alive += static_cast<int>(cells[i].state);
	}
	return alive;
}

int Cells::update()
{
	int ret = updateState();
	updateDisplay();
	return ret;
}

int Cells::neighbourCount(const int& x, const int& y) const
{
	int neighbourCount = 0;
	
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((y + i) < 0 || (x + j) < 0 || (y + i + 1) >= matrixSize || (x + j + 1) >= matrixSize)
				continue;
			else if ((i == 0) && (j == 0))
				continue;
			else
				neighbourCount += static_cast<int>(cells[(y + i) * matrixSize + (x + j)].state);
		}
	}

	/*
	neighbourCount =
		static_cast<int>(cells[(y - 1) * matrixSize + (x - 1)].state) +
		static_cast<int>(cells[(y - 1) * matrixSize + x].state) +
		static_cast<int>(cells[(y - 1) * matrixSize + (x + 1)].state) +
		static_cast<int>(cells[y * matrixSize + (x - 1)].state) +
		static_cast<int>(cells[y * matrixSize + (x + 1)].state) +
		static_cast<int>(cells[(y + 1) * matrixSize + (x - 1)].state) +
		static_cast<int>(cells[(y + 1) * matrixSize + x].state) +
		static_cast<int>(cells[(y + 1) * matrixSize + (x + 1)].state);
	*/

	return neighbourCount;
}

Cells::m_State Cells::fate(const int& x, const int& y) const
{
	int nCount = neighbourCount(x, y);

	if (nCount == 3)
		return m_State::alive;
	else if (nCount == 2)
		return cells[y * matrixSize + x].state;
	else
		return m_State::dead;
}

void Cells::randomize()
{
	for (int i = 0; i < arraySize; i++)
	{
		cells[i].state = m_State(rand() % 2);
	}
}
