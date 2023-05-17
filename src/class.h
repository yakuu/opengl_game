#ifndef CLASS_H
#define CLASS_H

#include <GL/glut.h>
#include <vector>

class Materials {
public:
    int getMaterial(int i, int j) const {
        // Implementation to retrieve material information for a given grid cell
        // Replace with your actual implementation
        return 0;
    }
};

class Grid {
public:
    int rows;
    int cols;
    float size;
    float scale = 1.0f;

    Grid() = default; // Default constructor

    void setGridSize(int numRows, int numCols, float cellSize) {
        rows = numRows;
        cols = numCols;
        size = cellSize;
    }

    void setMaterials(const Materials& materials) {
        // Set the materials for the grid
        // You can implement the logic here to store the materials in the grid
        // Replace this placeholder implementation with your actual logic
    }

    void draw() {
        // Adjust the grid size based on the scale
        float scaledSize = size * scale;

        // Draw the grid
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Calculate the position of the grid cell
                float posX = j * scaledSize;
                float posY = i * scaledSize;

                // Draw a square for each cell
                glBegin(GL_QUADS);
                glColor3f(1.0f, 1.0f, 1.0f); // Set the material color
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
        glColor3f(1.0, 0.20, 1.0); // Magenta
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glEnd();
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
