#include <GL/glut.h>

int g_wheelDelta = 0;

void mouseWheelFunc(int wheel, int direction, int x, int y) {
    g_wheelDelta += direction;
}

float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
float cameraDistance = 50.0f;

// Variables to store camera position
float camX = 0.0f;
float camY = 0.0f;
float camZ = 5.0f;

// Function to update the camera position
void updateCamera(int y) {
    cameraDistance += y;
    if (cameraDistance < 5.0f) {
        cameraDistance = 5.0f;
    } else if (cameraDistance > 100.0f) {
        cameraDistance = 100.0f;
    }

    if (spacePressed) {
        camX = cubeX;
        camY = cubeY;
        camZ = cubeZ + cameraDistance;
    } else {
        camX = 0.0f;
        camY = 0.0f;
        camZ = cameraDistance;
    }

    // Update camera distance based on mouse wheel
    cameraDistance += g_wheelDelta * 0.1f;
    g_wheelDelta = 0;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cubeX - 2.0f, cubeY + 2.0f, cubeZ + 2.0f, cubeX, cubeY, cubeZ, 0.0f, 1.0f, 0.0f);
}



