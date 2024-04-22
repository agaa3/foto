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
#include "DiffuseMaterial.h"
#include "ReflectiveMaterial.h"
#include "RefractiveMaterial.h"


const int SIZE = 60;

int main()
{
    int sizeX = 400;
    int sizeY = 400;

    int depth = 4;
    int number = 4;

    Image img = Image(sizeX, sizeY);
    std::vector<ObjectOnScene*> objects;
    std::vector<Light*> lights;
                                 //diffuseColor             kAmbient             kDiffuse             kSpecular       shininess
    auto matYellow = std::make_shared<DiffuseMaterial>(LightIntensity(1, 1, 0),   LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
    auto matMagenta = std::make_shared<DiffuseMaterial>(LightIntensity(1, .1, 1),  LightIntensity(0.5), LightIntensity(.5), LightIntensity(.3), 16);
    auto matCyjan = std::make_shared<DiffuseMaterial>(LightIntensity(.2, .7, 1), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.8), 32);
    auto matPurple = std::make_shared<DiffuseMaterial>(LightIntensity(1, .5, 1), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.2), 16);
    auto matRed = std::make_shared<DiffuseMaterial>(LightIntensity(.5, 0, 0), LightIntensity(0.5), LightIntensity(1), LightIntensity(.2), 1);
    auto matBlue = std::make_shared<DiffuseMaterial>(LightIntensity(0, 0, .5), LightIntensity(0.5), LightIntensity(1), LightIntensity(.1), 8);
    auto matGrey = std::make_shared<DiffuseMaterial>(LightIntensity(.4, .4, .4), LightIntensity(0.5), LightIntensity(.5), LightIntensity(.4), 2);
    auto matGrey1 = std::make_shared<DiffuseMaterial>(LightIntensity(.2, .2, .2), LightIntensity(1), LightIntensity(.5), LightIntensity(.2), 1);
    auto matDark = std::make_shared<DiffuseMaterial>(LightIntensity(.1, .1, .1), LightIntensity(0.1), LightIntensity(.5), LightIntensity(.1), 1);
    
    auto matReflective = std::make_shared<ReflectiveMaterial>(0.2);
    auto matRefractive = std::make_shared<RefractiveMaterial>(10);


    //LIGHTS
    PointLight light1 = PointLight(Vector3(0, 6.5, 8), LightIntensity(1), 3);
    lights.push_back(&light1);
    PointLight light2 = PointLight(Vector3(0, -3.9, 0), LightIntensity(1, 1, 0.5), 2);
    //lights.push_back(&light2);
    PointLight light5 = PointLight(Vector3(3.9, -2, 10), LightIntensity(0, 1, 1), 1);
    lights.push_back(&light5);


    Sphere sfera2 = Sphere(Vector3(2, -1, 12), 1, matPurple);
    objects.push_back(&sfera2);

    Sphere sfera6 = Sphere(Vector3(0, 1, 8), 1, matYellow);
    objects.push_back(&sfera6);

    Sphere sfera4 = Sphere(Vector3(-2, -2, 10), 2, matReflective); 
    objects.push_back(&sfera4);

    Sphere sfera3 = Sphere(Vector3(.5, -1.5, 6), 1, matRefractive);
    objects.push_back(&sfera3);

    Sphere sfera7 = Sphere(Vector3(-1, 0, -5), 3, matBlue); 
    objects.push_back(&sfera7);

    //Sphere sfera2 = Sphere(Vector3(3, -2, 12), 1, matPurple); //centralna
    //objects.push_back(&sfera2);

    //Sphere sfera4 = Sphere(Vector3(-1, -3, 11.5), 1, matRed); //lewa najbardziej z tylu
    //objects.push_back(&sfera4);

    //Sphere sfera6 = Sphere(Vector3(.5, -3, 8.5), 1, matRefractive); //lewa najbardziej z tylu
    //objects.push_back(&sfera6);

    //Sphere sfera1 = Sphere(Vector3(0, 0, 4), 1, matReflective); //lewa najbardziej z tylu
    //objects.push_back(&sfera1);

    //Sphere sfera5 = Sphere(Vector3(2, .5, 1), 1, matMagenta); //prawa za centralna
    //objects.push_back(&sfera5);
    
    

   Plane plane = Plane(Vector3(0, 0, 12), Vector3(0, 0, -1), matGrey); //przodu
   objects.push_back(&plane);

   Plane plane1 = Plane(Vector3(0, -4, 0), Vector3(0, 1, 0), matGrey1); //dol
   objects.push_back(&plane1);
   
   Plane plane2 = Plane(Vector3(0, 0, -10), Vector3(0, 0, 1), matDark); //z tylu
   objects.push_back(&plane2);

   Plane plane3 = Plane(Vector3(-4, 0, 0), Vector3(1, 0, 0), matRed); //z lewej
   objects.push_back(&plane3);

   Plane plane4 = Plane(Vector3(4, 0, 0), Vector3(-1, 0, 0), matBlue); //z prawej
   objects.push_back(&plane4);

   Plane plane5 = Plane(Vector3(0, 4, 0), Vector3(0, -1, 0), matDark); //na górze
   objects.push_back(&plane5);


   float backZ = 16;

   float frontZ = -16;
   float upY = 4;
   float downY = -4;
   float leftX = -4;
   float rightX = 4;

   //Triangle triangle1 = Triangle(Vector3(leftX, downY, frontZ), Vector3(leftX, downY, backZ), Vector3(rightX, downY, frontZ), matPurple); //na dole / podloga
   ////objects.push_back(&triangle1);

   //Triangle triangle4 = Triangle(Vector3(leftX, downY, backZ), Vector3(rightX, downY, backZ), Vector3(rightX, downY, frontZ), matPurple); //na dole / podloga
   ////objects.push_back(&triangle4);

   //Triangle triangle5 = Triangle(Vector3(leftX, downY, backZ), Vector3(leftX, upY, backZ), Vector3(rightX, downY, backZ), matPurple); //sciana
   ////objects.push_back(&triangle5);

   //Triangle triangle6 = Triangle(Vector3(leftX, upY, backZ), Vector3(rightX, upY, backZ), Vector3(rightX, downY, backZ), matPurple); //sciana
   ////objects.push_back(&triangle6);

   //Triangle triangle9 = Triangle(Vector3(leftX, downY, frontZ), Vector3(leftX, upY, frontZ), Vector3(leftX, downY, backZ), matPurple); //sciana
   ////objects.push_back(&triangle9);

   //Triangle triangle8 = Triangle(Vector3(leftX, upY, frontZ), Vector3(leftX, upY, backZ), Vector3(leftX, downY, backZ), matPurple); //sciana
   ////objects.push_back(&triangle8);

   //Triangle triangle10 = Triangle(Vector3(rightX, downY, frontZ), Vector3(rightX, downY, backZ), Vector3(rightX, upY, backZ), matPurple); //sciana
   ////objects.push_back(&triangle10);

   //Triangle triangle11 = Triangle(Vector3(rightX, upY, backZ), Vector3(rightX, upY, frontZ), Vector3(rightX, downY, frontZ), matPurple); //sciana
   ////objects.push_back(&triangle11);

   //Triangle triangle12 = Triangle(Vector3(leftX, upY, frontZ), Vector3(rightX, downY, backZ), Vector3(rightX, upY, backZ), matPurple); //sciana
   ////objects.push_back(&triangle12);

   //Triangle triangle13 = Triangle(Vector3(rightX, upY, backZ), Vector3(rightX, upY, frontZ), Vector3(rightX, downY, frontZ), matPurple); //sciana
   ////objects.push_back(&triangle13);

   //Triangle triangle3 = Triangle(Vector3(0, -2, 1), Vector3(5, 1, 1), Vector3(0, 1, 1), matPurple); //na dole / podloga
   ////objects.push_back(&triangle3);

   //Triangle triangle2 = Triangle(Vector3(-15, -7, 5), Vector3(0, 10, 5), Vector3(15, -7, 5), matPurple); //z tylu
   ////objects.push_back(&triangle2);

   //Triangle triangle7 = Triangle(Vector3(-4, -3, 5), Vector3(4, -2, 4), Vector3(0, 4, 4), matRefractive); //z tylu
   //objects.push_back(&triangle7);


   //OrthogonalCamera cam1 = OrthogonalCamera(Vector3(0, 0, -2), Vector3(0, 0, 1), Vector3(0, 1, 0), img, 0, 0.05, objects, lights);
   PerspectiveCamera cam1 = PerspectiveCamera(Vector3(0, 0, -1), Vector3(0, 0, 1), Vector3(0, 1, 0), img, 0, 0.05, objects, lights, depth, number);
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
        /*for (int i = 0; i < (cam1.img).pixels.size(); i++) {
            window.draw(&(cam1.img).pixels[i], 1, sf::Points, sf::RenderStates::Default);

        }*/

        window.draw(cam1.img.pixels.data(), cam1.img.pixels.size(), sf::Points, sf::RenderStates::Default);

        //window.draw(&vertices[i], 1, sf::Points);
        //window.draw(shape);
        window.display();
    }


    return 0;
}
