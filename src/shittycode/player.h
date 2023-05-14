#include <GL/glut.h>
#include <stdio.h>

// Variables to store cube position
float cubeX = 0.0f;
float cubeY = 0.0f;
float cubeZ = 0.0f;
float scaleFactor = 10.0f;

// Variable to keep track of whether space is being held down
bool spacePressed = false;
bool exitGame = false;


// Function to draw the cube
void drawCube() {
    GLfloat vertices[] = {
        // front face
        -0.5, -0.5, 0.5,
        0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        // right face
        0.5, -0.5, 0.5,
        0.5, -0.5, -0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5,
        // back face
        0.5, -0.5, -0.5,
        -0.5, -0.5, -0.5,
        0.5, 0.5, -0.5,
        -0.5, 0.5, -0.5,
        // left face
        -0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, -0.5,
        -0.5, 0.5, 0.5,
        // top face
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        // bottom face
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        0.5, -0.5, 0.5
    };

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i < 24; i += 4) {
        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
        glVertex3f(vertices[i + 4], vertices[i + 5], vertices[i + 6]);
        glVertex3f(vertices[i + 2], vertices[i + 3], vertices[i + 4]);
        glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
        glVertex3f(vertices[i + 4], vertices[i + 5], vertices[i + 6]);
        glVertex3f(vertices[i + 8], vertices[i + 9], vertices[i + 10]);
        glVertex3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
        glVertex3f(vertices[i + 10], vertices[i + 11], vertices[i + 12]);
        glVertex3f(vertices[i + 8], vertices[i + 9], vertices[i + 10]);
        glVertex3f(vertices[i + 12], vertices[i + 13], vertices[i + 14]);
        glVertex3f(vertices[i + 10], vertices[i + 11], vertices[i + 12]);
        glVertex3f(vertices[i + 14], vertices[i + 15], vertices[i + 16]);
        glVertex3f(vertices[i + 12], vertices[i + 13], vertices[i + 14]);
        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
        glVertex3f(vertices[i + 2], vertices[i + 3], vertices[i + 4]);
        glVertex3f(vertices[i + 4], vertices[i + 5], vertices[i + 6]);
    }
}

// Function to handle keyboard input
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            cubeY += 1.1f;
            break;
        case 'a':
            cubeX -= 1.1f;
            break;
        case 's':
            cubeY -= 1.1f;
            break;
        case 'd':
            cubeX += 1.1f;
            break;
        case ' ':
            spacePressed = true;
            break;
        case 27: // Escape key
            exitGame = true;
            exit(0);
            break;
    }
    printf("Cube position: x=%.2f, y=%.2f, z=%.2f\n", cubeX, cubeY, cubeZ);
    glutPostRedisplay(); // request a screen refresh
}

// Function to handle releasing space key
void handleKeyUp(unsigned char key, int x, int y) {
    if (key == ' ') {
        spacePressed = false;
    }
}