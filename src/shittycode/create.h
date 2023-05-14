#include <GL/glut.h>

// Light properties
float lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // white light
float lightPosition[] = {0.0f, 5.0f, 5.0f, 1.0f}; // position of the light source

void createLight() {
   // Set up lighting
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
   glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
   glEnable(GL_COLOR_MATERIAL);

   glClearColor(0.5f, 0.2f, 1.0f, 0.0f); // background color
   glEnable(GL_DEPTH_TEST);
}

void createGrid() {
   // Set up material properties for the grid lines
   GLfloat lineColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lineColor);

   // Enable lighting for the grid lines
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

   // Draw the grid lines
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glBegin(GL_LINES);
   for (int i = -10; i <= 10; i++) {
      glVertex3f(i, -10, 0);
      glVertex3f(i, 10, 0);
      glVertex3f(-10, i, 0);
      glVertex3f(10, i, 0);
   }
   glEnd();
   glPopMatrix();
}

void CreateLogText(int height, int width, float cubeZ, float cubeX, float cubeY) {
   // Render cube
   glPushMatrix();
   glTranslatef(cubeX, cubeY, cubeZ);
   glutSolidCube(1.0f);
   glPopMatrix();

   // Render cube position using glutBitmapCharacter
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, height, 0.0, width);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glColor3f(1.0f, 1.0f, 1.0f);
   glRasterPos2f(10.0f, 10.0f);
   std::string positionStr = "Cube position: x=" + std::to_string(cubeX) + ", y=" + std::to_string(cubeY) + ", z=" + std::to_string(cubeZ);
   for (const auto& c : positionStr) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
   }

   // Draw the grid
   glColor3f(0.5f, 0.5f, 0.5f); // set the color of the grid
   glBegin(GL_LINES);
   for (float i = -10.0f; i <= 10.0f; i += 1.0f) {
      glVertex3f(i, 0.0f, -10.0f);
      glVertex3f(i, 0.0f, 10.0f);
      glVertex3f(-10.0f, 0.0f, i);
      glVertex3f(10.0f, 0.0f, i);
   }
   glEnd();
}