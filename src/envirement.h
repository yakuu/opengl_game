#include <GL/glut.h>

void createGrid() {
   // Set the material properties for the background
   GLfloat backgroundMaterial[] = {0.0, 0.0, 1.0, 1.0};
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, backgroundMaterial);
   
   // Draw the background grid
   int gridSize = 50;
   glBegin(GL_LINES);
   for (int i = -gridSize; i <= gridSize; i++) {
      glVertex3f(i, -1, -gridSize);
      glVertex3f(i, -1, gridSize);
      glVertex3f(-gridSize, -1, i);
      glVertex3f(gridSize, -1, i);
   }
   glEnd();

   // Set the material properties for the ground
   GLfloat groundMaterial[] = {0.8, 0.8, 0.8, 1.0};
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, groundMaterial);

   // Draw the ground plane
   glBegin(GL_QUADS);
   glVertex3f(-gridSize, -1, -gridSize);
   glVertex3f(-gridSize, -1, gridSize);
   glVertex3f(gridSize, -1, gridSize);
   glVertex3f(gridSize, -1, -gridSize);
   glEnd();
}