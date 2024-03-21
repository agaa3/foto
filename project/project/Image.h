#pragma once
#include "LightIntensity.h"
#include <SFML/Graphics.hpp>
#include "Vector3.h"


class Image
{
public:
	int col, rows;
	//LightIntensity** pixels;
    std::vector<sf::Vertex> pixels;

	
    Image(int sizeX, int sizeY) : col(sizeX), rows(sizeY) {
        //// Alokuje pami�� na tablic� dwuwymiarow�
        //pixels = new LightIntensity* [rows];
        //for (int i = 0; i < rows; ++i) {
        //    pixels[i] = new LightIntensity[col];
        //}
    }

    // Destruktor zwalniaj�cy zaalokowan� pami��
    ~Image() {
        /*for (int i = 0; i < rows; ++i) {
            delete[] pixels[i];
        }
        delete[] pixels;*/
    }

	//Image(int sizeX, int sizeY) : col(sizeX), rows(sizeY) {};

	void setPixel(int x, int y, LightIntensity pixel);

};

