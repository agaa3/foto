// project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

#include "Vector.h"
#include "Quaternion.h"
#include "Line.h"
#include "Plane.h"
#include "Camera.h"

const int SIZE = 60;

int main()
{

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

    int input = ' ';
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
