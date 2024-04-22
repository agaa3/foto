#pragma once
#include "LightIntensity.h"
#include <SFML/Graphics.hpp>
#include "Vector3.h"


class Image
{
public:
	int col, rows;
	std::vector<sf::Vertex> pixels;

	Image() = default;
	Image(int sizeX, int sizeY) : col(sizeX), rows(sizeY) {
		pixels.resize(col * rows); //wypelnia domyslnymi wartosciami i alokuje tyle ile trzeba 
	};

	~Image() = default;

	void setPixel(int x, int y, LightIntensity pixel);

};

