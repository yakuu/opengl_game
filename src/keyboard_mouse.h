// keyboard_mouse.h
#ifndef KEYBOARD_MOUSE_H
#define KEYBOARD_MOUSE_H

#include <GL/glut.h>
#include "materials.h"
#include "class.h"

extern Game* game;
extern Grid* grid;
extern Camera* camera;
extern int windowWidth;
extern int windowHeight;

// Mouse function
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Get the normalized device coordinates
        float normalizedX = static_cast<float>(x) / windowWidth;
        float normalizedY = static_cast<float>(y) / windowHeight;

        // Convert the normalized device coordinates to world coordinates
        float worldX = (normalizedX - 0.5f) * grid->cols * grid->size;
        float worldY = (1.0f - normalizedY - 0.5f) * grid->rows * grid->size;

        // Update the camera target position
        camera->targetX = worldX;
        camera->targetY = worldY;
    }

    // Redraw the scene
    glutPostRedisplay();
}

// Keyboard function
void keyboard(unsigned char key, int x, int y) {
    // Update the key pressed
    game->keyboard(key, x, y);

    // Handle camera input
    if (camera != nullptr) {
        camera->handleKeyboardInput(key, x, y);
    }

    // Redraw the scene
    glutPostRedisplay();
}

#endif // KEYBOARD_MOUSE_H
