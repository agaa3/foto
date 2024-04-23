#include "Image.h"

void Image::setPixel(int x, int y, LightIntensity pixel) {
	int red = (int)(pixel.R * 255);
	int green = (int)(pixel.G * 255);
	int blue = (int)(pixel.B * 255);
	if (red > 255) red = 255;
	if (green > 255) green = 255;
	if (blue > 255) blue = 255;
	this->pixels[x * col + y] = sf::Vertex(sf::Vector2f(x, y), sf::Color(red, green, blue));

}

