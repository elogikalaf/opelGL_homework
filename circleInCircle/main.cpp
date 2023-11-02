/////////////////////////////////////////////////////////////////////         
// circle.cpp
//
// This program draws a line loop with vertices equally apart on 
// a fixed circle. The larger the number of vertices the better
// the loop approximates the circle.
//
// Interaction:
// Press +/- to increase/decrease the number of vertices of the loop. 
//
// Sumanta Guha.
///////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <unistd.h>          


#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <thread>
#pragma comment(lib, "glew32.lib") 
#endif

#define PI 3.14159265358979324

using namespace std;

// Globals.
static float R = 40.0; // Radius of circle.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static int numVertices = 5000; // Number of vertices on circle.


// Drawing routine.
void drawScene(void)
{  
   float t = 0; // Angle parameter.
   int i;

   glClear(GL_COLOR_BUFFER_BIT);


   for (R; R >= 0; R--) {
      glBegin(GL_LINE_LOOP);
      glColor3f(1.0, 0.0, 0.0);
      for(i = 0; i < numVertices; ++i) {
         glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
         t += 2 * PI / numVertices;
      }
      glEnd();
      glFlush();
      usleep(100000);
   }
   glFlush();
   for (R = 0; R <= 40; R++) {
      glBegin(GL_LINE_LOOP);
      glColor3f(0.0, 0.0, 0.0);
      for(i = 0; i < numVertices; ++i) {
         glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
         t += 2 * PI / numVertices;
      }
      glEnd();
      glFlush();
      usleep(100000);
   }


}

// Initialization routine.
void setup(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.


int main(int argc, char **argv) 
{
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("circle.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}
 