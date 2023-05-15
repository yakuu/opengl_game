#include <GL/glut.h>

// Camera position
float camPosX = 0.0f;
float camPosY = 0.0f;
float camPosZ = 10.0f;

// Camera target
float targetX = 0.0f;
float targetY = 0.0f;
float targetZ = 0.0f;

// Camera up vector
float upX = 0.0f;
float upY = 1.0f;
float upZ = 0.0f;

const int screenWidth = 1920;
const int screenHeight = 1080;
const int gridSize = 50;

float cubeX = 0.0f;
float cubeY = 0.0f;
float cubeZ = 0.0f;

// Set camera position
float camPos[] = {camPosX, camPosY, camPosZ};

// Set camera target
float camTarget[] = {targetX, targetY, targetZ};

// Set camera up vector
float camUp[] = {upX, upY, upZ};

GLfloat backgroundMaterial[] = {0.0, 0.0, 1.0, 1.0};
GLfloat groundMaterial[] = {0.8, 0.8, 0.8, 1.0};

// Camera settings
GLfloat angle = 90.0;

void initCamera() {
    // Set camera position, target, and up vector
    camPosX = 0.0f;
    camPosY = 0.0f;
    camPosZ = 5.0f;

    targetX = 0.0f;
    targetY = 0.0f;
    targetZ = 0.0f;

    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
}

void updateCamera() {
    gluLookAt(camPosX, camPosY, camPosZ, targetX, targetY, targetZ, upX, upY, upZ);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Left mouse button pressed
        // Update target based on mouse position
        targetX = (x - glutGet(GLUT_WINDOW_WIDTH)/2.0f) / 10.0f;
        targetY = (glutGet(GLUT_WINDOW_HEIGHT)/2.0f - y) / 10.0f;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Right mouse button pressed
        // Update camera position based on mouse position
        camPosX = (x - glutGet(GLUT_WINDOW_WIDTH)/2.0f) / 10.0f;
        camPosY = (glutGet(GLUT_WINDOW_HEIGHT)/2.0f - y) / 10.0f + 10.0f;
    }
    updateCamera();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '8':
        // Move camera forward
        camPosZ -= 0.1f;
        break;
    case '5':
        // Move camera backward
        camPosZ += 0.1f;
        break;
    case '4':
        // Strafe camera left
        camPosX -= 0.1f;
        break;
    case '6':
        // Strafe camera right
        camPosX += 0.1f;
        break;
    case '9':
        // Move camera up
        camPosY += 0.1f;
        break;
    case '7':
        // Move camera down
        camPosY -= 0.1f;
        break;
    }
    updateCamera();
}

void special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            // Rotate camera up
            targetY += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            // Rotate camera down
            targetY -= 0.1f;
            break;
        case GLUT_KEY_LEFT:
            // Rotate camera left
            targetX -= 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            // Rotate camera right
            targetX += 0.1f;
            break;
    }
    updateCamera();
}
