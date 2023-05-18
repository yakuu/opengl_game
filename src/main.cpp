#include <GL/glut.h>
#include "class.h"
#include "keyboard_mouse.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // Create a grid
    int numRows = 10;
    int numCols = 10;
    float cellSize = 50.0f;
    Grid grid;
    grid.setGridSize(numRows, numCols, cellSize);

    Cube cube(grid);
    initialize(grid, cube);

    glutMainLoop();

    return 0;
}
