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
    int sizeX = 600;
    int sizeY = 600;
    LightIntensity color = LightIntensity(1, 0, 0);
    Image img = Image(sizeX, sizeY); 
    std::vector<ObjectOnScene*> objects;
    Vector3 c1 = Vector3(0, 0, 1);
    Vector3 c2 = Vector3(1, 0, 0);


    OrthogonalCamera cam1 = OrthogonalCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0));
    Sphere sfera1 = Sphere(Vector3(0, 0, 2), .4, c1);
    Sphere sfera2 = Sphere(Vector3(.5, 0, 4), .25, c2);
    objects.push_back(&sfera1);
    objects.push_back(&sfera2);


    PerspectiveCamera cam2 = PerspectiveCamera(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
    /*Sphere sfera3 = Sphere(Vector3(0, 0, 2), .5, c1);
    Sphere sfera4 = Sphere(Vector3(.6, 0, 4), .25, c2);
    objects.push_back(&sfera3);
    objects.push_back(&sfera4);*/

    //cam1.RenderImage(img, objects);
    cam1.RenderImage(img, objects);

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
