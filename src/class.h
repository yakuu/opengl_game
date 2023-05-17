#ifndef CLASS_H
#define CLASS_H

#include <GL/glut.h>
#include <vector>

class SceneCamera {
    // Implementation of SceneCamera
};

class CubeCamera {
    // Implementation of CubeCamera
};


class Grid {
public:
    Grid() = default; // Default constructor

    void setGridSize(int numRows, int numCols, float cellSize) {
        rows = numRows;
        cols = numCols;
        size = cellSize;
    }

    void setMaterials(const std::vector<std::vector<int>>& materials) {
        material = materials;
    }

    void draw() {
        // Adjust the grid size based on the scale
        float scaledSize = size * scale;

        // Draw the grid
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Set the material color
                int mat = material[i][j];
                glColor3f(mat / 255.0f, mat / 255.0f, mat / 255.0f);

                // Calculate the position of the grid cell
                float posX = j * scaledSize;
                float posY = i * scaledSize;

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

    // Getter and setter functions for other member variables as needed

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

private:
    int rows;
    int cols;
    float size;
    float scale = 1.0f;
    std::vector<std::vector<int>> material; // Material value for each grid cell
};


struct Cube {
    int x;
    int y;
    Grid& grid; // Reference to the Grid object

    Cube(Grid& gridObj) : grid(gridObj) {}

    void moveUp() {
        if (y < grid.getRows() - 1) { // Check if not at the top boundary
            y++;
        }
    }

    void moveDown() {
        if (y > 0) { // Check if not at the bottom boundary
            y--;
        }
    }

    void moveLeft() {
        if (x > 0) { // Check if not at the left boundary
            x--;
        }
    }

    void moveRight() {
        if (x < grid.getCols() - 1) { // Check if not at the right boundary
            x++;
        }
    }

    void draw() {
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0); // white
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

public:
    Game(Grid& gridObj) : cube(gridObj) {} // Constructor that takes a Grid object

    void keyboard(unsigned char key, int x, int y) {
        switch (key) {
            case 'w':
                cube.moveUp();
                break;
            case 's':
                cube.moveDown();
                break;
            case 'a':
                cube.moveLeft();
                break;
            case 'd':
                cube.moveRight();
                break;
        }
    }
};

#endif // CLASS_H
