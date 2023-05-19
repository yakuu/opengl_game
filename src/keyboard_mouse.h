#ifndef KEYBOARD_MOUSE_H
#define KEYBOARD_MOUSE_H

#include <GL/glut.h>
#include "materials.h"
#include "class.h"

extern Game* game;

// Mouse function
void mouse(int button, int state, int x, int y) {
    // Handle mouse events here
    

    // Redraw the scene
    glutPostRedisplay();
}

// Keyboard function
void keyboard(unsigned char key, int x, int y) {
    if (game != nullptr) {
        game->keyboard(key, x, y);
    }
    glutPostRedisplay();
}

#endif // KEYBOARD_MOUSE_H
