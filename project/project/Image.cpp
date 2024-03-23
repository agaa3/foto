#include "Image.h"

void Image::setPixel(int x, int y, Color pixel) {
	int red = (int)(pixel.r * 255);
	int green = (int)(pixel.g * 255);
	int blue = (int)(pixel.b * 255);
	if (red > 255) red = 255;
	if (green > 255) green = 255;;
	if (blue > 255) blue = 255;;


	this->pixels.push_back(sf::Vertex(sf::Vector2f(x, y), sf::Color(red, green, blue)));

}

