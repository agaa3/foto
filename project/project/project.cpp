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
    Image img = Image(sizeX, sizeY);
    std::vector<ObjectOnScene*> objects;
    std::vector<Light*> lights;
                                 //diffuseColor             kAmbient             kDiffuse             kSpecular       shininess
    Material matYellow = Material(LightIntensity(1, 1, 0),   LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
    Material matMagenta = Material(LightIntensity(1, .1, 1),  LightIntensity(0.5), LightIntensity(.5), LightIntensity(.3), 16);
    Material matCyjan = Material(LightIntensity(.2, .7, 1), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.8), 32);
    Material matPurple = Material(LightIntensity(1, .5, 1), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
    Material matRed = Material(LightIntensity(.5, 0, 0), LightIntensity(0.5), LightIntensity(1), LightIntensity(.2), 1);
    Material matBlue = Material(LightIntensity(0, 0, .5), LightIntensity(0.5), LightIntensity(1), LightIntensity(.1), 8);
    Material matGrey = Material(LightIntensity(.4, .4, .4), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.4), 2);
    Material matGrey1 = Material(LightIntensity(.2, .2, .2), LightIntensity(1), LightIntensity(.5), LightIntensity(.2), 1);
    Material matDark = Material(LightIntensity(.1, .1, .1), LightIntensity(0.1), LightIntensity(.5), LightIntensity(.1), 1);

    Material matReflective = Material(LightIntensity(.7, .7, .7), reflective);
    Material matRefractive = Material(LightIntensity(.7, .7, .7), 1.8, refractive);


    //LIGHTS
    PointLight light1 = PointLight(Vector3(0, 1, 0), LightIntensity(.5));
    //lights.push_back(&light1);
    PointLight light2 = PointLight(Vector3(0, 3.9, 8), LightIntensity(1));
    lights.push_back(&light2);
    SpotLight light3 = SpotLight(Vector3(0, 1, -2), Vector3(0, -.2, 1), LightIntensity(1, .2, .75), 15, 0);
    //lights.push_back(&light3);
    DirectionalLight light4 = DirectionalLight(Vector3(0, .7, 1), LightIntensity(.5, .5, .5));
    //lights.push_back(&light4);

    
    Sphere sfera3 = Sphere(Vector3(-2, -1, 10), .5, matYellow); //centralna
    objects.push_back(&sfera3);

    Sphere sfera2 = Sphere(Vector3(3, -2, 12), 1, matPurple); //centralna
    objects.push_back(&sfera2);

    Sphere sfera4 = Sphere(Vector3(-1, -3, 11.5), 1, matReflective); //lewa najbardziej z tylu
    objects.push_back(&sfera4);

    Sphere sfera6 = Sphere(Vector3(.5, -3, 8.5), 1, matRefractive); //lewa najbardziej z tylu
    objects.push_back(&sfera6);

    Sphere sfera1 = Sphere(Vector3(2, 0, 4), 3, matCyjan); //lewa najbardziej z tylu
    //objects.push_back(&sfera1);

    Sphere sfera5 = Sphere(Vector3(1, .5, 3), 1, matMagenta); //prawa za centralna
    //objects.push_back(&sfera5);

    Plane plane = Plane(Vector3(0, 0, 16), Vector3(0, 0, -1), matGrey); //przodu
    objects.push_back(&plane);

    Plane plane1 = Plane(Vector3(0, -4, 0), Vector3(0, 1, 0), matGrey1); //dol
    objects.push_back(&plane1);
    
    Plane plane2 = Plane(Vector3(0, 0, -16), Vector3(0, 0, 1), matDark); //z tylu
    objects.push_back(&plane2);

    Plane plane3 = Plane(Vector3(-4, 0, 0), Vector3(1, 0, 0), matRed); //z lewej
    objects.push_back(&plane3);

    Plane plane4 = Plane(Vector3(4, 0, 0), Vector3(-1, 0, 0), matBlue); //z prawej
    objects.push_back(&plane4);

    Plane plane5 = Plane(Vector3(0, 4, 0), Vector3(0, -1, 0), matDark); //na górze
    objects.push_back(&plane5);


    float backZ = 10;
    float backZ2 = 10;

    float frontZ = -2;
    float upY = 10;
    float downY = -3;
    float leftX = -10;
    float rightX = 10;

    Triangle triangle1 = Triangle(Vector3(leftX, downY, frontZ), Vector3(leftX, downY, backZ2), Vector3(rightX, downY, frontZ), matPurple); //na dole / podloga
    //objects.push_back(&triangle1);

    Triangle triangle4 = Triangle(Vector3(leftX, downY, backZ2), Vector3(rightX, downY, backZ2), Vector3(rightX, downY, frontZ), matPurple); //na dole / podloga
    //objects.push_back(&triangle4);

    Triangle triangle5 = Triangle(Vector3(leftX, downY, backZ), Vector3(leftX, upY, backZ), Vector3(rightX, downY, backZ), matPurple); //sciana
    //objects.push_back(&triangle5);

    Triangle triangle6 = Triangle(Vector3(leftX, upY, backZ), Vector3(rightX, upY, backZ), Vector3(rightX, downY, backZ), matPurple); //sciana
    //objects.push_back(&triangle6);

    Triangle triangle3 = Triangle(Vector3(0, -2, 1), Vector3(5, 1, 1), Vector3(0, 1, 1), matPurple); //na dole / podloga
    //objects.push_back(&triangle3);

    Triangle triangle2 = Triangle(Vector3(-15, -7, 5), Vector3(0, 10, 5), Vector3(15, -7, 5), matPurple); //z tylu
    //objects.push_back(&triangle2);

    Triangle triangle7 = Triangle(Vector3(-4, -3, 14), Vector3(0, 4,10), Vector3(4, -2, 14), matRefractive); //z tylu
    //objects.push_back(&triangle7);


    //OrthogonalCamera cam1 = OrthogonalCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0), img, 0, 0.05, objects, lights);
    PerspectiveCamera cam1 = PerspectiveCamera(Vector3(0, -1, -1), Vector3(0, 0, 1), Vector3(0, 1, 0), img, 2, 0.05, objects, lights);
    cam1.RenderImage(2);


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
