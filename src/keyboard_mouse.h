#ifndef KEYBOARD_MOUSE_H
#define KEYBOARD_MOUSE_H

#include <GL/glut.h>
#include "materials.h"
#include "class.h"

// Global variables
static int windowWidth = 800;
static int windowHeight = 600;
static Grid* grid;
static Cube* cube;
static Game* game;

// Mouse function
void mouse(int button, int state, int x, int y) {
    // Handle mouse events here
    // ...
    // Implementation for mouse handling
}

// Reshape function
void reshape(int width, int height) {
    // Update the window width and height
    windowWidth = width;
    windowHeight = height;

    // Set the viewport and projection matrix
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Display function
void display() {
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Materials::applyDefaultMaterial();

    grid->draw();
    cube->draw();

    // Swap buffers
    glutSwapBuffers();
    glutPostRedisplay();
}

// Keyboard function
void keyboard(unsigned char key, int x, int y) {
    game->keyboard(key, x, y);

    // Redraw the scene
    glutPostRedisplay();
}

// Initialize function
void initialize(Grid& gridObj, Cube& cubeObj) {
    grid = &gridObj;
    cube = &cubeObj;
    game = new Game(gridObj);

    // Set the grid size
    int numRows = 10;
    int numCols = 10;
    float cellSize = 50.0f;
    grid->setGridSize(numRows, numCols, cellSize);

    // Create and apply the default material
    Materials materials;
    materials.applyDefaultMaterial();
    grid->setMaterials(materials);

    // Set the cube position
    cube->x = 0;
    cube->y = 0;

    // Set up the display mode and window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100); // sets the window position
    glutCreateWindow("Keyboard and Mouse Example");

    // Set the callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    // Set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

#endif // KEYBOARD_MOUSE_H
