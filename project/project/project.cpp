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

const int SIZE = 60;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }



    //1
    //2
    Vector3 v1 = Vector3(1, 2, 3);
    Vector3 v2 = Vector3(10, 11, 12);
    Vector3 result1 = v1 + v2;
    Vector3 result2 = v2 + v1;


    std::cout
        << "2. Dodawanie 1: " << result1 << "\nDodawanie 2: " << result2;

    //3
    Vector3 v3 = Vector3(0, 3, 0);
    Vector3 v4 = Vector3(5, 5, 0);
    float angle = acosf((v3.dotProduct(v4))/(v3.length() * v4.length()));
    angle = angle * 180 / M_PI;
    std::cout
        << "\n\n3. Kat (w stopniach): " << angle;

    //4
    Vector3 v5 = Vector3(4, 5, 1);
    Vector3 v6 = Vector3(4, 1, 3);
    Vector3 result3 = v5.cross(v6);
    std::cout
        << "\n\n4. Wektor: " << result3;

    

    //5
    Vector3 norm1 = result3.normalize();
    std::cout
        << "\n\n5. Wektor znormalizowany: " << norm1;

    //6
    //7
    Sphere s = Sphere(Vector3(0, 0, 0), 10);

    //8
    Ray r1 = Ray(Vector3(0, 0, -20), s.center, false);

    //9
    Ray r2 = Ray(r1.origin, Vector3(0, 1, 0));

    //10
    Vector3 intPoint1 = Vector3();
    Vector3 intPoint2 = Vector3();

    bool intersectionSphereR1 = s.hit(r1, intPoint1); // ten sie pownienie przciaæ
    bool intersectionSphereR2 = s.hit(r2, intPoint2);

    std::cout
        << "\n\n10. Czy istnieje przeciecie sfery i r1: " << intersectionSphereR1;
    if (intersectionSphereR1) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint1;
    }

    std::cout
        << "\nCzy istnieje przeciecie sfery i r2: " << intersectionSphereR2;
    if (intersectionSphereR2) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint2;
    }

    //12
    Ray r3 = Ray(Vector3(0, -1, 10), Vector3(0, 1, 0));
    Vector3 intPoint3 = Vector3();
    bool intersectionSphereR3 = s.hit(r3, intPoint3); // ten sie pownienie przciaæ
    std::cout
        << "\n\n12. Czy istnieje przeciecie sfery i r3: " << intersectionSphereR3;
    if (intersectionSphereR3) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint3;
    }

    //13 14
    Plane p1 = Plane(Vector3(0, 0, 0), Vector3(0, 1, 1));
    Vector3 intPoint4 = Vector3();

    bool intersectionPlaneR2 = p1.hit(r2, intPoint4);
    std::cout
        << "\n\n14. Punkt przeciecia: " << intPoint4;

    //15
    Triangle t1 = Triangle(Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, 0));

    Vector3 point1 = Vector3(-1, 0.5, 0);
    Vector3 point2 = Vector3(1, 0.5, 0);
    Vector3 intPoint5 = Vector3();
    Vector3 intPoint6 = Vector3();


    Ray r4 = Ray(point1, point2, false);
    Ray r5 = Ray(point2, point1, false);

    bool intersectionTriangleR4 = t1.hit(r4, intPoint5); //linia przechodzi przez trojk¹t na planie 2D (linia jest prostopad³a do wektora normalnego trójk¹ta)
    std::cout
        << "\n\n15.1. Czy istnieje przeciecie trojkata i r4: " << intersectionTriangleR4;
    if (intersectionTriangleR4) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint5;
    }
    bool intersectionTriangleR5 = t1.hit(r5, intPoint5);
    std::cout
        << "\nCzy istnieje przeciecie trojkata i r5: " << intersectionTriangleR5;
    if (intersectionTriangleR5) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint5;
    }

    //16
    Vector3 point3 = Vector3(2, -1, 0);
    Vector3 point4 = Vector3(2, 2, 0);

    Ray r6 = Ray(point3, point4, false);
    Ray r7 = Ray(point4, point3, false);

    bool intersectionTriangleR6 = t1.hit(r6, intPoint5); //linia przechodzi przez trojk¹t na planie 2D (linia jest prostopad³a do wektora normalnego trójk¹ta)
    std::cout
        << "\n\n15.2. Czy istnieje przeciecie trojkata i r6: " << intersectionTriangleR6;
    if (intersectionTriangleR6) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint5;
    }
    bool intersectionTriangleR7 = t1.hit(r7, intPoint5);
    std::cout
        << "\nCzy istnieje przeciecie trojkata i r7: " << intersectionTriangleR7;
    if (intersectionTriangleR7) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint5;
    }

    //15.3
    Vector3 point5 = Vector3(0, 0, -1);
    Vector3 point6 = Vector3(0, 0, 1);

    Ray r8 = Ray(point5, point6, false);
    Ray r9 = Ray(point6, point5, false);

    bool intersectionTriangleR8 = t1.hit(r8, intPoint5); //linia przechodzi przez trojk¹t na planie 2D (linia jest prostopad³a do wektora normalnego trójk¹ta)
    std::cout
        << "\n\n15.3. Czy istnieje przeciecie trojkata i r8: " << intersectionTriangleR8;
    if (intersectionTriangleR8) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint5;
    }
    bool intersectionTriangleR9 = t1.hit(r9, intPoint5);
    std::cout
        << "\nCzy istnieje przeciecie trojkata i r9: " << intersectionTriangleR9;
    if (intersectionTriangleR9) {
        std::cout
            << "\nPunkt przeciecia: " << intPoint5;
    }



    

    /*Ray r4 = Ray(Vector(0, 0, -20), Vector(0, 1, -1));
    bool intersectionPlaneR4 = p1.intersects(r4, 1000, intPoint4);
    std::cout
        << "\nCzy przecina: " << intersectionPlaneR4;*/

    /*
    //bryla2x2x2
    float cubeSize = 2;
    Plane p_front = Plane(Vector(-cubeSize / 2, -cubeSize / 2, cubeSize / 2), Vector(0, 0, 1));
    Plane p_back = Plane(Vector(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2), Vector(0, 0, -1));
    Plane p_left = Plane(Vector(-cubeSize / 2, -cubeSize / 2, cubeSize / 2), Vector(-1, 0, 0));
    Plane p_right = Plane(Vector(cubeSize / 2, -cubeSize / 2, cubeSize / 2), Vector(1, 0, 0));
    Plane p_bottom = Plane(Vector(-cubeSize / 2, -cubeSize / 2, cubeSize / 2), Vector(0, -1, 0));
    Plane p_up = Plane(Vector(-cubeSize / 2, cubeSize / 2, cubeSize / 2), Vector(0, 1, 0));

    char tab[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tab[i][j] = '.';
        }
    }

    float width = 2;

    Camera cam = Camera(3);

    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;
    float zoom = 3;

    int input = ' ';*/
    /*
    do {
        cam = Camera(zoom);
        cam.rotateX1(angleX);
        //        std::cout << "pos: " << cam.position << ", dir: " << cam.direction << ", up: " << cam.up << std::endl;

        cam.rotateY1(angleY);
        //        std::cout << "pos: " << cam.position << ", dir: " << cam.direction << ", up: " << cam.up << std::endl;

                //cam.rotateAxis(45, Vector(1, 1, 0));
        cam.rotateZ1(angleZ);
        //std::cout << "pos: " << cam.position << ", dir: " << cam.direction << ", up: " << cam.up << std::endl;

        Vector rightDirectionView = cam.direction.cross(cam.up);
        Line ray = Line(cam.position, cam.direction);
        Vector point;
        bool isCrossing = false;
        for (int i = 0; i < SIZE; i++) { //wiersze
            for (int j = 0; j < SIZE; j++) { //kolumny
                ray.direction =
                    cam.direction +
                    Vector((j - SIZE / 2) * (width / 60) * rightDirectionView.x,
                        (j - SIZE / 2) * (width / 60) * rightDirectionView.y,
                        (j - SIZE / 2) * (width / 60) * rightDirectionView.z) +
                    Vector((SIZE / 2 - i) * width / 60 * cam.up.x,
                        (SIZE / 2 - i) * width / 60 * cam.up.y,
                        (SIZE / 2 - i) * width / 60 * cam.up.z);; //od górnego lewego rogu
                if (Plane::isLineAndPlaneCrossing(ray, p_front)) {
                    point = Plane::crossingOfLineAndPlane(ray, p_front);
                    if (point.x <= cubeSize / 2 && point.y <= cubeSize / 2 && point.z <= cubeSize / 2
                        && point.x >= -cubeSize / 2 && point.y >= -cubeSize / 2 && point.z >= -cubeSize / 2) {
                        isCrossing = true;
                    }
                }
                if (Plane::isLineAndPlaneCrossing(ray, p_back)) {
                    point = Plane::crossingOfLineAndPlane(ray, p_back);
                    if (point.x <= cubeSize / 2 && point.y <= cubeSize / 2 && point.z <= cubeSize / 2
                        && point.x >= -cubeSize / 2 && point.y >= -cubeSize / 2 && point.z >= -cubeSize / 2) {
                        isCrossing = true;
                    }
                }
                if (Plane::isLineAndPlaneCrossing(ray, p_left)) {
                    point = Plane::crossingOfLineAndPlane(ray, p_left);
                    if (point.x <= cubeSize / 2 && point.y <= cubeSize / 2 && point.z <= cubeSize / 2
                        && point.x >= -cubeSize / 2 && point.y >= -cubeSize / 2 && point.z >= -cubeSize / 2) {
                        isCrossing = true;
                    }

                }
                if (Plane::isLineAndPlaneCrossing(ray, p_right)) {
                    point = Plane::crossingOfLineAndPlane(ray, p_right);
                    if (point.x <= cubeSize / 2 && point.y <= cubeSize / 2 && point.z <= cubeSize / 2
                        && point.x >= -cubeSize / 2 && point.y >= -cubeSize / 2 && point.z >= -cubeSize / 2) {
                        isCrossing = true;
                    }
                }
                if (Plane::isLineAndPlaneCrossing(ray, p_up)) {
                    point = Plane::crossingOfLineAndPlane(ray, p_up);
                    if (point.x <= cubeSize / 2 && point.y <= cubeSize / 2 && point.z <= cubeSize / 2
                        && point.x >= -cubeSize / 2 && point.y >= -cubeSize / 2 && point.z >= -cubeSize / 2) {
                        isCrossing = true;
                    }
                }
                if (Plane::isLineAndPlaneCrossing(ray, p_bottom)) {
                    point = Plane::crossingOfLineAndPlane(ray, p_bottom);
                    if (point.x <= cubeSize / 2 && point.y <= cubeSize / 2 && point.z <= cubeSize / 2
                        && point.x >= -cubeSize / 2 && point.y >= -cubeSize / 2 && point.z >= -cubeSize / 2) {
                        isCrossing = true;
                    }
                }
                if (isCrossing) {
                    tab[i][j] = '0';
                }
                else {
                    tab[i][j] = '.';
                }
                isCrossing = false;
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                std::cout << tab[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << "pos: " << cam.position << ", dir: " << cam.direction << ", up: " << cam.up << std::endl;

        while (!_kbhit()) {}
        if (_kbhit()) {
            input = _getch();
            switch (input) {
            case 'a':
                angleY -= 1;
                break;
            case 'd':
                angleY += 1;
                break;
            case 'w':
                angleX -= 1;
                break;
            case 's':
                angleX += 1;
                break;
            case 'q':
                angleZ -= 1;
                break;
            case 'e':
                angleZ += 1;
                break;
            case 'z':
                zoom -= 0.1;
                break;
            case 'x':
                zoom += 0.1;
                break;
            }
        }
        system("CLS");
    } while (input != 'p');
    */
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
