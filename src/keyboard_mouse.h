#ifndef KEYBOARD_MOUSE_H
#define KEYBOARD_MOUSE_H

#include <GL/glut.h>
#include "class.h"
#include <iostream>

extern Camera camera;
extern Cube cube;

void handleSpecialKeypress(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            camera.moveForward();
            break;
        case GLUT_KEY_DOWN:
            camera.moveBackward();
            break;
        case GLUT_KEY_LEFT:
            camera.moveLeft();
            break;
        case GLUT_KEY_RIGHT:
            camera.moveRight();
            break;
    }
    glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            cube.moveForward();
            break;
        case 's':
        case 'S':
            cube.moveBackward();
            break;
        case 'a':
        case 'A':
            cube.moveLeft();
            break;
        case 'd':
        case 'D':
            cube.moveRight();
            break;
        case ' ':
            // Print camera and cube position information
            std::cout << "Camera position: (" << camera.getPositionX() << ", " << camera.getPositionY() << ", " << camera.getPositionZ() << ")" << std::endl;
            std::cout << "Cube position: (" << cube.getPositionX() << ", " << cube.getPositionY() << ", " << cube.getPositionZ() << ")" << std::endl;
            break;
    }

    glutPostRedisplay();
}

#endif // KEYBOARD_MOUSE_H
