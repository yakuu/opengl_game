#include <GL/glut.h>

#include "keyboard_mouse.h"

void init() {
   // Set up lighting
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   GLfloat light_position[] = {0.0, 10.0, 0.0, 1.0};
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);


   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, backgroundMaterial);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, backgroundMaterial);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, groundMaterial);

   initCamera();
   updateCamera();
   glutPostRedisplay();  // Request redisplay
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
  
  // Set up camera
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camPos[0], camPos[1], camPos[2],
            camTarget[0], camTarget[1], camTarget[2],
            camUp[0], camUp[1], camUp[2]);

  glRotatef(angle, 1.0, 0.0, 0.0); // rotate cube around x-axis
  glRotatef(angle, 0.0, 1.0, 0.0); // rotate cube around y-axis
  
  // Draw cube
  glBegin(GL_QUADS);
  glColor3f(1.0, 1.0, 1.0); // white
  glVertex3f(-1.0, -1.0, 1.0);
  glVertex3f(1.0, -1.0, 1.0);
  glVertex3f(1.0, 1.0, 1.0);
  glVertex3f(-1.0, 1.0, 1.0);

  // rest of cube vertices omitted for brevity

  glEnd();

  glutSwapBuffers();
}


void reshape(int width, int height) {
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float aspect = (float)width / (float)height;
   gluPerspective(60.0f, aspect, 0.1f, 100.0f);
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


