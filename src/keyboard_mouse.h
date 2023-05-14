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
