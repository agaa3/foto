#pragma once
#include "Color.h"
#include <SFML/Graphics.hpp>
#include "Vector3.h"


class Image
{
public:
	int col, rows;
	std::vector<sf::Vertex> pixels;

	Image() = default;
	Image(int sizeX, int sizeY) : col(sizeX), rows(sizeY) {};

	~Image() = default;

	void setPixel(int x, int y, Color pixel);

};

