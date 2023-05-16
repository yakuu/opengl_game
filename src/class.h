#include <GL/glut.h>

// Cube object
struct Cube {
    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 0.0f;

    void draw() const {
        // Set the cube position
        glTranslatef(posX, posY, posZ);

        // Draw cube
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0); // white
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glEnd();
    }

    void move(float deltaX, float deltaY, float deltaZ) {
        posX += deltaX;
        posY += deltaY;
        posZ += deltaZ;
    }
};

// Camera object
class Camera {
public:
    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 5.0f;

    void move(float deltaX, float deltaY, float deltaZ)
    {
        posX += deltaX;
        posY += deltaY;
        posZ += deltaZ;
    }

    void lookAt(float targetX, float targetY, float targetZ)
    {
        gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0.0f, 1.0f, 0.0f);
    }
};
