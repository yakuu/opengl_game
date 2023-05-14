#include <windows.h>
#include <iostream>
#include <sstream>
#include <GL/glut.h>
#include <math.h>

const int screenWidth = 1920;
const int screenHeight = 1080;
const int gridSize = 50;

float cubeX = 0.0f;
float cubeY = 0.0f;
float cubeZ = 0.0f;

GLfloat backgroundMaterial[] = {0.0, 0.0, 1.0, 1.0};
GLfloat groundMaterial[] = {0.8, 0.8, 0.8, 1.0};

void init() {
   // Set up lighting
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   float light_pos[] = {1.0f, 1.0f, 1.0f, 0.0f};
   glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, backgroundMaterial);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, backgroundMaterial);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, groundMaterial);
}

void generateScene() {
   // Set the material properties for the background
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, backgroundMaterial);
   
   // Draw the background grid
   glBegin(GL_LINES);
   for (int i = -gridSize; i <= gridSize; i++) {
      glVertex3f(i, -1, -gridSize);
      glVertex3f(i, -1, gridSize);
      glVertex3f(-gridSize, -1, i);
      glVertex3f(gridSize, -1, i);
   }
   glEnd();

   // Set the material properties for the ground
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, groundMaterial);

   // Draw the ground plane
   glBegin(GL_QUADS);
   glVertex3f(-gridSize, -1, -gridSize);
   glVertex3f(-gridSize, -1, gridSize);
   glVertex3f(gridSize, -1, gridSize);
   glVertex3f(gridSize, -1, -gridSize);
   glEnd();
}

void renderScene() {
   glPushMatrix();
   glTranslatef(cubeX, cubeY, cubeZ);
   glutSolidCube(1.0);
   glPopMatrix();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Draw the grid and ground plane
   generateScene();

   // Draw the cube
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, groundMaterial);
   renderScene();
   glPopMatrix();

   glutSwapBuffers();
}

void reshape(int width, int height) {
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float aspect = (float)width / (float)height;
   gluPerspective(60.0f, aspect, 0.1f, 100.0f);
}

void keyboard(unsigned char key, int x, int y) {
   switch(key) {
      case 'w':
         cubeY += 0.1f;
         break;
      case 'a':
         cubeX -= 0.1f;
         break;
      case 's':
         cubeY -= 0.1f;
         break;
      case 'd':
         cubeX += 0.1f;
         break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(screenWidth * 0.8, screenHeight * 0.8);
   glutCreateWindow("Cube Example");

   init();
   
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);

   glutMainLoop();

   return 0;
}
