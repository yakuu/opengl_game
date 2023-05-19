#ifndef CLASS_H
#define CLASS_H

#include <GL/glut.h>
#include <vector>
#include <conio.h>
#include "materials.h"

class Grid {
public:
    int rows;
    int cols;
    float size;
    float scale = 1.0f;
    Materials materials; // Instance of Materials class

    Grid() = default; // Default constructor

    void setGridSize(int numRows, int numCols, float cellSize) {
        rows = numRows;
        cols = numCols;
        size = cellSize;
    }

void draw() {
    // Adjust the grid size based on the scale
    float scaledSize = size * scale;

    // Calculate the starting position of the grid
    float startX = -cols * scaledSize * 0.5f;
    float startY = -rows * scaledSize * 0.5f;

    // Draw the grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Calculate the position of the grid cell
            float posX = startX + j * scaledSize;
            float posY = startY + i * scaledSize;

            // Set the material properties
            materials.applyDefaultMaterial();

            // Determine the color based on the cell index
            if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 0.7f, 0.3f); // color for even cells
            } else {
                glColor3f(0.3f, 0.2f, 1.0f); // color for odd cells
            }

            // Draw a square for each cell
            glBegin(GL_QUADS);
            glVertex2f(posX, posY);
            glVertex2f(posX, posY + scaledSize);
            glVertex2f(posX + scaledSize, posY + scaledSize);
            glVertex2f(posX + scaledSize, posY);
            glEnd();
        }
    }
}

};

struct Cube {
    int x;
    int y;
    Grid& grid; // Reference to the Grid object

    Cube(Grid& gridObj) : grid(gridObj) {}

    void draw() {
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glEnd();
    }
};
struct Camera {
    // Variables for camera position and rotation
    float camPosX;
    float camPosY;
    float camPosZ;
    float targetX;
    float targetY;
    float targetZ;
    float angleX;
    float angleY;

    // Constructor to initialize the camera variables
    Camera()
        : camPosX(0.0f), camPosY(0.0f), camPosZ(0.0f), targetX(0.0f),
          targetY(0.0f), targetZ(0.0f), angleX(0.0f), angleY(0.0f) {}

    // Function to handle keyboard input
    void handleKeyboardInput(unsigned char key, int x, int y) {
        // Update camera variables based on the key
        switch (key) {
            case '8':  // Move camera forward
                camPosZ -= 0.1f;
                break;
            case '2':  // Move camera backward
                camPosZ += 0.1f;
                break;
            case '4':  // Move camera left
                camPosX -= 0.1f;
                break;
            case '6':  // Move camera right
                camPosX += 0.1f;
                break;
            case '7':  // Move camera up
                camPosY += 0.1f;
                break;
            case '9':  // Move camera down
                camPosY -= 0.1f;
                break;
            case '1':  // Rotate camera around X-axis (increase angleX)
                angleX += 1.0f;
                break;
            case '3':  // Rotate camera around X-axis (decrease angleX)
                angleX -= 1.0f;
                break;
            case '+':  // Rotate camera around Y-axis (increase angleY)
                angleY += 1.0f;
                break;
            case '-':  // Rotate camera around Y-axis (decrease angleY)
                angleY -= 1.0f;
                break;
        }
    }

    // Function to update the camera position and rotation
    void update() {
        // Perform any necessary calculations or operations based on the updated variables
        camPosZ -= 50;
    }

    // Function to apply camera transformations
    void applyTransformations() {
        // Apply camera transformations using the camera variables
        gluLookAt(camPosX, camPosY, camPosZ, targetX, targetY, targetZ, 0.0f, 0.0f, 1.0f);
    }
};

class Game {
private:
    Cube cube;
    Grid& grid;

public:
    Game(Grid& gridObj) : cube(gridObj), grid(gridObj) {} // Constructor that takes a Grid object

    void keyboard(unsigned char key, int x, int y) {
        switch (key) {
            case 'w':
                cube.y++;
                break;
            case 's':
                cube.y--;
                break;
            case 'a':
                cube.x--;
                break;
            case 'd':
                cube.x++;
                break;
        }
    }
};

#endif // CLASS_H
