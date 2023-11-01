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

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

#define PI 3.14159265358979324

using namespace std;

// Globals.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static int numVertices = 4; // Number of vertices on circle.

// Drawing routine.
void drawScene(void)
{  
   float t = 0; // Angle parameter.
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(0.0, 0.0, 0.0);

   // Draw a line loop with vertices at equal angles apart on a circle
   // with center at (X, Y) and radius R, The vertices are colored randomly.
   glBegin(GL_TRIANGLE_STRIP);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(20.0 , 80.0 , 0.0);
         glVertex3f(20.0, 70.0, 0.0);
         glVertex3f(30.0, 70.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(20.0, 80.0, 0.0);
         glVertex3f(30.0, 80.0, 0.0);
         glVertex3f(30.0, 70.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(40.0, 80.0, 0.0);
         glVertex3f(30.0, 70.0, 0.0);
         glVertex3f(30.0, 30.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(40.0, 80.0, 0.0);
         glVertex3f(30.0, 30.0, 0.0);
         glVertex3f(40.0, 40.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(30.0, 30.0, 0.0);
         glVertex3f(40.0, 40.0, 0.0);
         glVertex3f(40.0, 30.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(40.0, 40.0, 0.0);
         glVertex3f(40.0, 30.0, 0.0);
         glVertex3f(50.0, 40.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(40.0, 30.0, 0.0);
         glVertex3f(50.0, 40.0, 0.0);
         glVertex3f(50.0, 30.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(50.0, 30.0, 0.0);
         glVertex3f(50.0, 40.0, 0.0);
         glVertex3f(60.0, 30.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(50.0, 80.0, 0.0);
         glVertex3f(50.0, 30.0, 0.0);
         glVertex3f(60.0, 30.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(50.0, 80.0, 0.0);
         glVertex3f(60.0, 30.0, 0.0);
         glVertex3f(60.0, 70.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(50.0, 80.0, 0.0);
         glVertex3f(60.0, 70.0, 0.0);
         glVertex3f(70.0, 80.0, 0.0);

         glColor3f(1.0, 0.0, 0.0); // red
         glVertex3f(60.0, 70.0, 0.0);
         glVertex3f(70.0, 80.0, 0.0);
         glVertex3f(70.0, 70.0, 0.0);
        
        

   glEnd();

   glFlush();
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 
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
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      case '+':
         numVertices++;
         glutPostRedisplay();
         break;
      case '-':
         if (numVertices > 3) numVertices--;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press +/- to increase/decrease the number of vertices on the circle." << endl;  
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("livan.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}