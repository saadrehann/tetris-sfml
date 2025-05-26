#pragma once
#include <iostream>
#include "./block.h"

class Blocks
{
public:
	int map[4][4] = { {0, 0, 0, 0} ,
					  {0, 0, 0, 0} ,
					  {0, 0, 0, 0} ,
					  {0, 0, 0, 0} };
	
	int i, j;
	float x, y;
	float size;
	sf::Uint8 red, green, blue, alpha;
	int blocks_amount = 0;
	Block *blocks[12];
	int state = 0;
	Blocks(int row = 0, int col = 0, float s = 7.0F, sf::Uint8 r = 0, sf::Uint8 g = 0, sf::Uint8 b = 0, sf::Uint8 a = 255)
	{
	
		size = s;
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F; 
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}
	~Blocks()
	{
		delete[] *blocks;
	}

	bool collides(int x, int y)
	{
		for (int i = 0; i < blocks_amount; i++)
		{
			if (blocks[i]->i == x && blocks[i]->j == y)
			{
				return true;
			}
			return false;
		}
	}

	void setup()
	{
		blocks_amount = 0;
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map[j][i] == 1)
				{
					blocks[blocks_amount] = new Block(this->i + i, this->j + j, size, red, green, blue, alpha);
					blocks_amount++;
					
				}
			}
			
		}
	}
	void set(int y, int x)
	{
		map[x][y] = 1;
	}

	virtual Blocks* copy(int optional_state = 0)
	{
	Blocks *cpy = new Blocks(this->i, this->j, this->size, this->red, this->green, this->blue, this->alpha);
	while(cpy->state != optional_state) cpy->rotate();
		return cpy;	
	}
	void pos(int row, int col)
	{
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F; 
		setup();

	}
	void draw(float outline = 0)
	{
		
		for (int i = 0; i < blocks_amount; i++)
		{
			blocks[i]->draw(outline);	
		}
	}
	virtual void rotate()
	{
	
	}

	void reset()
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				map[i][j] = 0;
			}
		}
	}
};


class LLshape : public Blocks 
{
public:
	LLshape(int row, int col, float size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
	:Blocks(row, col, size, r, g, b, a)
	{
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F;
		
		rotate();
		rotate();
		rotate();
		rotate();
		setup();

	}

	virtual Blocks* copy(int optional_state = 0)
	{
		Blocks* cpy = new LLshape(this->i, this->j, this->size, this->red, this->green, this->blue, this->alpha);
		while (cpy->state != optional_state) cpy->rotate();
		return cpy;
	}

	void rotate()
	{
		reset();
		switch (state)
		{
			case 0:
				set(1, 0);
				set(1, 1);
				set(1, 2);
				set(0, 2);
				state++;
				break;
			case 1:
				set(2, 1);
				set(1, 1);
				set(3, 1);
				set(3, 2);
				state++;
				break;
			case 2:
				set(1, 0);
				set(1, 1);
				set(1, 2);
				set(2, 0);
				state++;
				break;
			case 3:
				set(2, 1);
				set(1, 1);
				set(0, 1);
				set(0, 0);
				state++;
				break;
			default:
				state = 0;
				set(1, 0);
				set(1, 1);
				set(1, 2);
				set(0, 2);
				state++;
		}
			}
};

class LRshape : public Blocks
{
public:
	LRshape(int row, int col, float size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
		:Blocks(row, col, size, r, g, b, a)
	{
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F;
		
		rotate();
		rotate(); 
		rotate();
		rotate();
		setup();

	}
	virtual Blocks* copy(int optional_state = 0)
	{
		Blocks* cpy = new LRshape(this->i, this->j, this->size, this->red, this->green, this->blue, this->alpha);
		while (cpy->state != optional_state) cpy->rotate();
		return cpy;
	}
	void rotate()
	{
		
		reset();
		switch (state)
		{
		case 0:
			set(1, 0);
			set(1, 1);
			set(1, 2);
			set(2, 2);
			state++;
			break;
		case 1:
			set(3, 0);
			set(1, 1);
			set(2, 1);
			set(3, 1);
			state++;
			break;
		case 2:
			set(1, 0);
			set(1, 1);
			set(1, 2);
			set(0, 0);
			state++;
			break;
		case 3:
			set(2, 1);
			set(1, 1);
			set(0, 1);
			set(0, 2);
			state++;
			break;
		default:
			state = 0;
			set(1, 0);
			set(1, 1);
			set(1, 2);
			set(2, 2);
			state++;
		}
	}
};

class Sshape : public Blocks
{
public:
	Sshape(int row, int col, float size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
		:Blocks(row, col, size, r, g, b, a)
	{
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F;

		rotate();
		setup();

	}

	virtual Blocks* copy(int optional_state = 0)
	{
		Blocks* cpy = new Sshape(this->i, this->j, this->size, this->red, this->green, this->blue, this->alpha);
		while (cpy->state != optional_state) cpy->rotate();
		return cpy;
	}

	void rotate()
	{
		reset();
		switch (state)
		{
			
		case 0:
			set(1, 0);
			set(2, 0);
			set(1, 1);
			set(2, 1); 
			state++;
			break;
		case 1:
			set(1, 0);
			set(2, 0);
			set(1, 1);
			set(2, 1);
			state++;
			break;
		case 2:
			set(1, 0);
			set(2, 0);
			set(1, 1);
			set(2, 1);
			state++;
			break;
		case 3:
			set(1, 0);
			set(2, 0);
			set(1, 1);
			set(2, 1);
			state++;
			break;

		default:
			state = 0;
			set(1, 0);
			set(2, 0);
			set(1, 1);
			set(2, 1);

			state++;
		}
	}

};

class ZLshape : public Blocks
{
public:
	ZLshape(int row, int col, float size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
		:Blocks(row, col, size, r, g, b, a)
	{
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F;

		rotate();
		setup();

	}

	virtual Blocks* copy(int optional_state = 0)
	{
		Blocks* cpy = new ZLshape(this->i, this->j, this->size, this->red, this->green, this->blue, this->alpha);
		while (cpy->state != optional_state) cpy->rotate();
		return cpy;
	}

	void rotate()
	{
		reset();

		switch (state)
		{
			
		case 0:
			set(0, 0);
			set(1, 0);
			set(1, 1);
			set(2, 1);
			state++;
			break;
		case 1:
			set(1, 0);
			set(1, 1);
			set(0, 1);
			set(0, 2);
			state++;
			break;
		case 2:
			set(1, 1);
			set(0, 1);
			set(1, 2);
			set(2, 2);
			state++;
			break;
		case 3:
			set(2, 0);
			set(2, 1);
			set(1, 1);
			set(1, 2);
			state++;
			break;
		default:
			state = 0;
			set(0, 0);
			set(1, 0);
			set(1, 1);
			set(2, 1);
			state++;
		}
	}
};

class ZRshape : public Blocks
{
public:
	ZRshape(int row, int col, float size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
		:Blocks(row, col, size, r, g, b, a)
	{
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F;

		rotate();
		setup();

	}

	virtual Blocks* copy(int optional_state = 0)
	{
		Blocks* cpy = new ZRshape(this->i, this->j, this->size, this->red, this->green, this->blue, this->alpha);
		while (cpy->state != optional_state) cpy->rotate();
		return cpy;
	}

	void rotate()
	{

		reset();

		switch (state)
		{
			
		case 0:
			set(1, 0);
			set(2, 0);
			set(1, 1);
			set(0, 1); 
			state++;
			break;
		case 1:
			set(0, 0);
			set(0, 1);
			set(1, 1);
			set(1, 2);
			state++;
			break;
		case 2:
			set(1, 1);
			set(1, 2);
			set(0, 2);
			set(2, 1);
			state++;
			break;
		case 3:
			set(2, 1);
			set(2, 2);
			set(1, 1);
			set(1, 0);
			state++;
			break;
		default:
			state = 0;
			set(1, 0);
			set(2, 0);
			set(1, 1);
			set(0, 1);
			state++;
		}
	}
};

class Ishape : public Blocks
{
public:
	Ishape(int row, int col, float size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
		:Blocks(row, col, size, r, g, b, a)
	{
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F;
		rotate();
		rotate();
		setup();

	}

	virtual Blocks* copy(int optional_state = 0)
	{
		Blocks* cpy = new Ishape(this->i, this->j, this->size, this->red, this->green, this->blue, this->alpha);
		while (cpy->state != optional_state) cpy->rotate();
		return cpy;
	}

	void rotate()
	{

		reset();

		switch (state)
		{
			
		case 0:
			set(1, 0);
			set(1, 1);
			set(1, 2);
			set(1, 3);
			state++;
			break;
		case 1:
			set(0, 1);
			set(1, 1);
			set(2, 1);
			set(3, 1);
			state++;
			break;
		case 2:
			set(1, 0);
			set(1, 1);
			set(1, 2);
			set(1, 3);
			state++;
			break;
		case 3:
			set(0, 1);
			set(1, 1);
			set(2, 1);
			set(3, 1);
			state++;
			break;
		default:
			state = 0;
			set(1, 0);
			set(1, 1);
			set(1, 2);
			set(1, 3);
			state++;
		}
	}
};

class Tshape : public Blocks
{
public:
	Tshape(int row, int col, float size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
		:Blocks(row, col, size, r, g, b, a)
	{
		i = row;
		j = col;
		x = i * (size + 2.0F) + 2.0F;
		y = j * (size + 2.0F) + 2.0F;

		rotate();
		setup();

	}

	virtual Blocks* copy(int optional_state = 0)
	{
		Blocks* cpy = new Tshape(this->i, this->j, this->size, this->red, this->green, this->blue, this->alpha);
		while (cpy->state != optional_state) cpy->rotate();
		return cpy;
	}

	void rotate()
	{
		reset();

		switch (state)
		{
			
		case 0:
			set(1, 0);
			set(1, 1);
			set(0, 1);
			set(2, 1);
			state++;
			break;
		case 1:
			set(1, 0);
			set(1, 1);
			set(0, 1);
			set(1, 2);
			state++;
			break;
		case 2:
			set(0, 1);
			set(1, 1);
			set(1, 2);
			set(2, 1);
			state++;
			break;
		case 3:
			set(1, 0);
			set(1, 1);
			set(2, 1);
			set(1, 2);

			state++;
			break;
		default:
			state = 0;
			set(1, 0);
			set(1, 1);
			set(0, 1);
			set(2, 1);
			state++;
		}
	}
};