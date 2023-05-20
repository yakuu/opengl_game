#include <iostream>
#include <GL/glut.h>
#include "class.h"
#include "keyboard_mouse.h"

// Grid object
Grid grid;

// Cube object
Cube cube;

// Camera object
Camera camera;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply camera transformations
    camera.applyTransformations();

    // Draw the grid
    grid.draw();

    // Draw the cube
    cube.draw();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL GLUT Scene");

    // Initialize grid
    grid.init();

    // Initialize cube
    cube.init(0.50f);

    // Initialize camera
    camera.init(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 5.0f); 

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(handleSpecialKeypress);
    glutKeyboardFunc(handleKeypress);

    glutMainLoop();

    return 0;
}