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
#include "Color.h"
#include "Material.h"
#include "Light.h"
#include "PointLight.h"

const int SIZE = 60;

int main()
{
    int sizeX = 600;
    int sizeY = 600;
    //LightIntensity color = LightIntensity(1, 0, 0);
    Image img = Image(sizeX, sizeY);
    std::vector<ObjectOnScene*> objects;
    std::vector<Light*> lights;
    /*Vector3 c1 = Vector3(0, 0, 1);
    Vector3 c2 = Vector3(1, 0, 0);*/
    Material mat1 = Material(LightIntensity(0, 0, 1));
                           //diffuseColor             kAmbient           kDiffuse           kSpecular          shininess
    Material mat2 = Material(LightIntensity(1, .1, .1), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
    Material mat3 = Material(LightIntensity(1, 1, 0));

    PointLight light1 = PointLight(Vector3(4, 0, -2), LightIntensity(1, 1, 1));
    lights.push_back(&light1);

    //OrthogonalCamera cam1 = OrthogonalCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0), img);
    //OrthogonalCamera cam1 = OrthogonalCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0), img, 3, 0.05);

    /*Sphere sfera1 = Sphere(Vector3(0, 0, 2), .4, c1);
    Sphere sfera2 = Sphere(Vector3(.5, 0, 4), .25, c2);
    objects.push_back(&sfera1);
    objects.push_back(&sfera2);*/


   
    Sphere sfera3 = Sphere(Vector3(0, .5, 0), 1, mat2);
    //Plane plane = Plane(Vector3(0, -0.5, 0), Vector3(0, 1, -1), mat2);
    Sphere sfera4 = Sphere(Vector3(0, -1, 2), 1, mat2);
    objects.push_back(&sfera3);
    //objects.push_back(&plane);
    objects.push_back(&sfera4);

    Triangle triangle1 = Triangle(Vector3(-1, -1.5, 0), Vector3(0, -1.5, 1), Vector3(1, -1.5, 0), mat1);
    //objects.push_back(&triangle1);

    PerspectiveCamera cam1 = PerspectiveCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0), img, 0, 0.05, objects, lights);
    cam1.RenderImage();


    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "SFML works!");
    window.setSize(sf::Vector2u(sizeX, sizeY));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < (cam1.img).pixels.size(); i++) {
            window.draw(&(cam1.img).pixels[i], 1, sf::Points);

        }
        //window.draw(&vertices[i], 1, sf::Points);
        //window.draw(shape);
        window.display();
    }


    return 0;
}
