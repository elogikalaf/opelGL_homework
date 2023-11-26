///////////////////////////////////////////////////////////////////////////////////////////        
// circularAnnuluses.cpp
//
// This program draws three identical-looking circular annuluses in three different ways - 
// see comments below.
//
// Interaction:
// Press the space bar to toggle between wirefrime and filled for the lower annulus.
// 
// Sumanta Guha.
/////////////////////////////////////////////////////////////////////////////////////////// 

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
#pragma comment(lib, "glew32.lib") 
#endif 

#define PI 3.14159265
#define N 40.0 // Number of vertices on the boundary of the disc.

using namespace std;

// Globals.
static int isWire = 0; // Is wireframe?
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, const char *string)
{  
   const char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
} 

// Function to draw a disc with center at (X, Y, Z), radius R, parallel to the xy-plane.
void drawDisc(float R, float X, float Y, float Z)
{
   float t;
   int i;

   glBegin(GL_TRIANGLE_FAN);
      glVertex3f( X, Y, Z);
      for(i = 0; i <= N; ++i)
	  {
         t = 2 * PI * i / N; 
         glVertex3f(X + cos(t) * R, Y + sin(t) * R, Z);
	  }
   glEnd();
}

// Drawing routine.
void drawScene(void)
{  
   float angle;
   int i;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers including 
                                                       // the depth buffer.

   glPolygonMode(GL_FRONT, GL_FILL);

   // Upper left circular annulus: the white disc overwrites the red disc.
   // for (int i = 20; i <=80; i= i+10) {
   //    glColor3f(1.0, 0.0, 0.0);
   //    drawDisc(20.0, i, 75.0, 0.0);
   //    glColor3f(1, 1, 1.0);
   //    drawDisc(15.0, i, 75.0, 0.0);
   //    glColor3f(0.0, 0.0, 1.0);
   //    drawDisc(20.0, i, 50.0, 0.0);
   //    glColor3f(1, 1, 1.0);
   //    drawDisc(15.0, i, 50.0, 0.0);
   //    glFlush();
   //    glClear(GL_COLOR_BUFFER_BIT);
   //    usleep(100000);
   // }
      // Lower circular annulus: with a true hole.

   for (int markaz = 20; markaz <=80; markaz = markaz+10) {
      if (isWire) glPolygonMode(GL_FRONT, GL_LINE);else glPolygonMode(GL_FRONT, GL_FILL);
      glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= N; ++i) {
         angle = 2 * PI * i / N; 
         glVertex3f(markaz + cos(angle) * 15.0, 30 + sin(angle) * 15.0, 0.0);
         glVertex3f(markaz + cos(angle) * 20.0, 30 + sin(angle) * 20.0, 0.0);
      }
      glColor3f(0.0, 0.0, 1.0);
      for(i = 0; i <= N; ++i) {
         angle = 2 * PI * i / N; 
         glVertex3f(markaz + cos(angle) * 15.0, 50 + sin(angle) * 15.0, 0.0);
         glVertex3f(markaz + cos(angle) * 20.0, 50 + sin(angle) * 20.0, 0.0);
      }
      glColor3f(0.0, 1.0, 0.0);
      for(i = 0; i <= N; ++i) {
         angle = 2 * PI * i / N; 
         glVertex3f(markaz + cos(angle) * 15.0, 70 + sin(angle) * 15.0, 0.0);
         glVertex3f(markaz + cos(angle) * 20.0, 70 + sin(angle) * 20.0, 0.0);
      }
      glEnd();
      glFlush();
      glClear(GL_COLOR_BUFFER_BIT);
      usleep(100000);
   }
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
      case ' ':
         if (isWire == 0) isWire = 1;
         else isWire = 0;
         glutPostRedisplay();
         break;	  
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press the space bar to toggle between wirefrime and filled for the lower annulus." << endl;  
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("circularAnnuluses.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop();  
}