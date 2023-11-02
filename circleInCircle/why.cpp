#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <unistd.h>


static float R = 40.0; // Radius of circle.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static int numVertices = 5000; // Number of vertices on circle.
#define PI 3.14159265358979324

// Drawing routine.
void drawScene(void)
{  
   float t = 0; // Angle parameter.
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(0.0, 0.0, 0.0);

   for (; R > 10 && R <= 40; R--)
   {
      glBegin(GL_LINE_LOOP);
      glColor3f(1.0, 0.0, 0.0);
      for(i = 0; i < numVertices; ++i)
      {
         glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
         t += 2 * PI / numVertices;
      }
      glEnd();
      glFlush();
      usleep(100000);
   }

   // Clear the color buffer
   glClear(GL_COLOR_BUFFER_BIT);
   glFlush();
   R = 10;
   for (; R < 40 && R <= 40; R++)
   {
      glBegin(GL_LINE_LOOP);
      glColor3f(1.0, 0.0, 0.0);
      for(i = 0; i < numVertices; ++i)
      {
         glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
         t += 2 * PI / numVertices;
      }
      glEnd();
      glFlush();
      usleep(100000);
   }

}
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-10.0, 100.0, 0.0, 100.0, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("OpenGL Window");
    glutReshapeFunc(resize);  
    glutDisplayFunc(drawScene);
    glutMainLoop();

    return 0;
}