#include <GL/glut.h>
#include "class.h"
#include "keyboard_mouse.h"

SceneCamera sceneCamera; // instance of the SceneCamera object
CubeCamera cubeCamera;   // instance of the CubeCamera object

void init() {
    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 0.0, 10.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    initialize();
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    // Create a grid
    int numRows = 10; // Set the number of rows according to your needs
    int numCols = 10; // Set the number of columns according to your needs
    float cellSize = 1.0f; // Set the cell size according to your needs

    std::vector<std::vector<int>> materials(numRows, std::vector<int>(numCols, 0)); // Set the materials for each cell in the grid

    grid.setGridSize(numRows, numCols, cellSize);
    grid.setMaterials(materials);

    glutMainLoop();

    return 0;
}
