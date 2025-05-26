#pragma once
#include "./shapes.h"
class Block {
public:
	rect bl;
	float x, y;
	int i, j;
	sf::Uint8 alpha;
	float size;
public:
	Block(int row = 0, int col = 0, float s = 0, sf::Uint8 r = 0, sf::Uint8 g = 0, sf::Uint8 b = 0, sf::Uint8 a = 0)
	{
		size = s;
		i = row;
		j = col;
		x = i * (size + 2) + 2;
		y = j * (size + 2) + 2;
		bl.size(size, size);
		bl.pos(x, y);
		bl.nostroke();
		alpha = a;
		bl.fill(r, g, b, a);
	}

	int boundry(int row, int col)
	{
		if (row < 0) return -2;
		if (row >= rows) return +2;
		if (col < 0) return -1;
		if (col >= cols) return 1;
		return 0;
	}

	void set(int row, int col)
	{
		if (!boundry(row, col))
		{
			i = row;
			j = col;
			x = i * (size + 2) + 2;
			y = j * (size + 2) + 2;

			bl.pos(x, y);
		}
	}

	bool collides(Block & obj)
	{
		if (obj.i == i && obj.j == j)
		{
			return true;
		}
		return false;
	}

	void draw(float outline = 0)
	{
		if (outline)
		{
			bl.stroke(80, 0, 0, 255);
			bl.fill(80, 0, 0, 60);
			bl.outline(outline);
		}

		bl.draw();
	}
};