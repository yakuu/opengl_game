#include <GL/glut.h>
#include <iostream>
#include "class.h"
#include "keyboard_mouse.h"

// Global variables
int windowWidth = 1500;
int windowHeight = 900;

Grid* grid;
Cube* cube;
Game* game = nullptr;
Camera* camera = nullptr;
char keyPressed = '\0';

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

// Declaration of your idle function
void idle();

// Display function
void display() {
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set up camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the grid
    if (grid != nullptr) {
        grid->draw();
    }

    // Draw the cube
    if (cube != nullptr) {
        cube->draw();
    }

    // Swap buffers
    glutSwapBuffers();
}

void updateCamera() {
    camera->update();
}

// Initialize function
void initialize(Grid& gridObj, Cube& cubeObj) {

    // Convert the window title to a C-style string
    const char* windowTitle = "OpenGL Scene";

    // Set up the display mode and window
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(windowTitle);
    glutInitWindowPosition(100, 100);

    // Set the callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    // Set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    grid = &gridObj;
    cube = &cubeObj;
    game = new Game(gridObj);

    // Set the grid size
    int numRows = 200;
    int numCols = 100;
    float cellSize = 10.0f;
    grid->setGridSize(numRows, numCols, cellSize);

    // Set the position of the cube to the center of the grid
    cubeObj.x = numCols / 2;
    cubeObj.y = numRows / 2;

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // Create an instance of the Camera class
    Camera cam;
    camera = &cam;

    // Create a grid
    int numRows = 10;
    int numCols = 10;
    float cellSize = 50.0f;
    Grid grid;
    grid.setGridSize(numRows, numCols, cellSize);

    Cube cube(grid);
   
    initialize(grid, cube);

    // Register idle function
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}

void idle() {
    // Perform additional tasks or updates here
    // Apply camera transformations before drawing
    camera->applyTransformations();
    cube->draw();
    glutPostRedisplay();
}