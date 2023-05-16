#include <GL/glut.h>
#include <vector>

class Grid {
public:
    Grid(int numRows, int numCols, float cellSize, const std::vector<std::vector<int>>& materials)
        : rows(numRows), cols(numCols), size(cellSize), material(materials) {}

    void draw() {
        // Adjust the grid size based on the scale
        float scaledSize = size * scale;

        // Draw the grid
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Set the material color
                int mat = material[i][j];
                glColor3f(mat / 255.0f, mat / 255.0f, mat / 255.0f);

                // Draw a square for each cell
                glBegin(GL_QUADS);
                glVertex2f(j * scaledSize, i * scaledSize);
                glVertex2f(j * scaledSize, (i + 1) * scaledSize);
                glVertex2f((j + 1) * scaledSize, (i + 1) * scaledSize);
                glVertex2f((j + 1) * scaledSize, i * scaledSize);
                glEnd();
            }
        }
    }

    int getNumRows() const { return rows; }
    int getNumCols() const { return cols; }
    float getCellSize() const { return size; }
    float getScale() const { return scale; }
    void setScale(float newScale) { scale = newScale; }

private:
    int rows;
    int cols;
    float size;
    float scale = 1.0f;
    std::vector<std::vector<int>> material;  // Material value for each grid cell
};
