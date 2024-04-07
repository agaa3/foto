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
#include "SpotLight.h"
#include "DirectionalLight.h"

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
    Material mat1 = Material(LightIntensity(0, 0, 1), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
                           //diffuseColor             kAmbient           kDiffuse           kSpecular          shininess
    Material mat2 = Material(LightIntensity(1, 0, 0), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
    Material mat3 = Material(LightIntensity(1, 1, 0),   LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
    Material mat4 = Material(LightIntensity(1, .1, 1),  LightIntensity(0.5), LightIntensity(.5), LightIntensity(.3), 16);
    Material mat5 = Material(LightIntensity(.2, .7, 1), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.3), 16);
    Material mat6 = Material(LightIntensity(.5, .5, .5), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
    Material mat7 = Material(LightIntensity(.7, .7, .7), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);

    PointLight light1 = PointLight(Vector3(0, 1, -2), LightIntensity(.5, .5, .5));
    //lights.push_back(&light1);
    PointLight light2 = PointLight(Vector3(-2, 0, -2), LightIntensity(.1, .5, .5));
    lights.push_back(&light2);
    //SpotLight light3 = SpotLight(Vector3(0, 1, -2), Vector3(0, 0, 1), LightIntensity(.5, .5, .5));
    //lights.push_back(&light3);
    DirectionalLight light4 = DirectionalLight(Vector3(0, 0.5, 1), LightIntensity(.5, .5, .5));
    lights.push_back(&light4);

    

    /*Sphere sfera1 = Sphere(Vector3(0, 0, 2), .4, c1);
    Sphere sfera2 = Sphere(Vector3(.5, 0, 4), .25, c2);
    objects.push_back(&sfera1);
    objects.push_back(&sfera2);*/


   
    Sphere sfera3 = Sphere(Vector3(.1, .1, .5), .5, mat2); //centralna
    objects.push_back(&sfera3);

    Sphere sfera2 = Sphere(Vector3(.1, 2, 5), 2, mat2); //centralna
    //objects.push_back(&sfera2);

    Sphere sfera4 = Sphere(Vector3(-2, 0, 4), 3, mat5); //lewa najbardziej z tylu
    //objects.push_back(&sfera4);

    Sphere sfera1 = Sphere(Vector3(2, 0, 4), 3, mat5); //lewa najbardziej z tylu
    //objects.push_back(&sfera1);

    Sphere sfera5 = Sphere(Vector3(1, .5, 3), 1, mat4); //prawa za centralna
    objects.push_back(&sfera5);

    Plane plane = Plane(Vector3(0, 0, 5), Vector3(0, 1, -1), mat4); //z tylu
    //objects.push_back(&plane);

    Plane plane1 = Plane(Vector3(0, -3.5, 0), Vector3(0, 1, 0), mat6); //dol
    //objects.push_back(&plane1);
    
    Plane plane2 = Plane(Vector3(0, 0, 4.5), Vector3(0, 0, -1), mat7); //z tylu
    //objects.push_back(&plane2);

    float backZ = 4.5;
    float backZ2 = 10;

    float frontZ = -2;
    float upY = 10;
    float downY = -3;
    float leftX = -10;
    float rightX = 10;

    Triangle triangle1 = Triangle(Vector3(leftX, downY, frontZ), Vector3(leftX, downY, backZ2), Vector3(rightX, downY, frontZ), mat1); //na dole / podloga
    //objects.push_back(&triangle1);

    Triangle triangle4 = Triangle(Vector3(leftX, downY, backZ2), Vector3(rightX, downY, backZ2), Vector3(rightX, downY, frontZ), mat1); //na dole / podloga
    //objects.push_back(&triangle4);

    Triangle triangle5 = Triangle(Vector3(leftX, downY, backZ), Vector3(leftX, upY, backZ), Vector3(rightX, downY, backZ), mat7); //sciana
    //objects.push_back(&triangle5);

    Triangle triangle6 = Triangle(Vector3(leftX, upY, backZ), Vector3(rightX, upY, backZ), Vector3(rightX, downY, backZ), mat7); //sciana
    //objects.push_back(&triangle6);

    Triangle triangle3 = Triangle(Vector3(0, -2, 1), Vector3(0, 1, 1), Vector3(5, 1, 1), mat1); //na dole / podloga
    //objects.push_back(&triangle3);

    Triangle triangle2 = Triangle(Vector3(-15, -7, 5), Vector3(0, 10, 5), Vector3(15, -7, 5), mat1); //z tylu
    //objects.push_back(&triangle2);



    //OrthogonalCamera cam1 = OrthogonalCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0), img);
    //OrthogonalCamera cam1 = OrthogonalCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0), img, 0, 0.05, objects, lights);
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
