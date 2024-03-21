#include "Image.h"

void Image::setPixel(int x, int y, LightIntensity pixel) {
	int red = (int)(pixel.r * 255);
	int green = (int)(pixel.g * 255);
	int blue = (int)(pixel.b * 255);

	this->pixels.push_back(sf::Vertex(sf::Vector2f(x, y), sf::Color(red, green, blue)));

}

