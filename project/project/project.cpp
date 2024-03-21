// project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

#include "Vector3.h"
#include "Quaternion.h"
#include "Ray.h"
#include "Plane.h"
#include "Camera.h"
#include "Sphere.h"
#include "Triangle.h"
#include "ObjectOnScene.h"
#include <SFML/Graphics.hpp>
#include "Image.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"

const int SIZE = 60;

int main()
{
    int sizeX = 400;
    int sizeY = 400;
    LightIntensity color = LightIntensity(1, 0, 0);
    Image img = Image(sizeX, sizeY); 
    
    PerspectiveCamera cam2 = PerspectiveCamera(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));

    OrthogonalCamera cam1 = OrthogonalCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0));
    Sphere sfera = Sphere(Vector3(0, 0, 2), 1);
     
    std::vector<ObjectOnScene*> objects;
    objects.push_back(&sfera);

    //cam1.RenderImage(img, objects);
    cam2.RenderImage(img, objects);

    //for (int i = 0; i < sizeY; i++) { //rzedy
    //   for (int j = 0; j < sizeX; j++) { //kolumnach
    //       img.setPixel(j, i, color);

    //    }
    //}





    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "SFML works!");
    window.setSize(sf::Vector2u(sizeX, sizeY));
    //sf::CircleShape shape(100.f);
    
    //shape.setFillColor(sf::Color::Green);

    //sf::Vertex point(sf::Vector2f(10, 10), sf::Color::Green);

    //sf::VertexArray image1(sf::Vector2f);
    

    //std::vector<sf::Vertex> vertices;
    //vertices[3][4] = 

    //for (int i = 0; i < sizeY; i++) { //rzedy
    //    for (int j = 0; j < sizeX; j++) { //kolumnach
    //        vertices.push_back(sf::Vertex(sf::Vector2f(i, j), sf::Color(255, 255, 0)));
    //        /*
    //        if(j >100){
    //            vertices.push_back(sf::Vertex(sf::Vector2f(i, j), sf::Color(255, 255, 0)));
    //        }
    //        else {
    //            vertices.push_back(sf::Vertex(sf::Vector2f(i, j), sf::Color(255, 0, 0)));
    //            //vertices[i * sizeY + j].color(100, 100, 100);
    //        }*/

    //    }
    //   //std::cout << i <<"\n";
    //}


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < img.pixels.size(); i++) {
            window.draw(&img.pixels[i], 1, sf::Points);

        }
		//window.draw(&vertices[i], 1, sf::Points);
        //window.draw(shape);
        window.display();
    }

    //strzelamy promieniamy z kamery, jak sie przetnie to bierzemy lokacjê trafienia, obliczamy kolor i wpisujemy do tablicy VertexArray
        
    return 0;
}
