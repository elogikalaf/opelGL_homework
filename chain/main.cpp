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

static float R = 40.0; // Radius of circle.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static int numVertices = 5000; // Number of vertices on circle.

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


      float t = 0;
      int M = 20;
      glColor3f(1.0, 0.0, 0.0);
         // glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
         // t += 2 * PI / numVertices;
      for (int ver = 0; ver < numVertices/2; ++ver) {
      
         glBegin(GL_TRIANGLE_STRIP);
         if (isWire) glPolygonMode(GL_FRONT, GL_LINE);else glPolygonMode(GL_FRONT, GL_FILL);
         float x = X + 1.5*R * cos(t);
         float y = Y + 1.5*R * sin(t);
         glColor3f(0.0, 1.0, 0.0);
         for(i = 0; i <= N; ++i) {
            angle = 2 * PI * i / N; 
            glVertex3f(x + cos(angle) * 15.0, 20 + y + sin(angle) * 15.0, 0.0);
            glVertex3f(x + cos(angle) * 20.0, 20 + y + sin(angle) * 20.0, 0.0);
         }
         glEnd();
         x = X + R * cos(t);
         y = Y + R * sin(t);
         glBegin(GL_TRIANGLE_STRIP);
         glColor3f(1.0, 0.0, 0.0);
         for(i = 0; i <= N; ++i) {
            angle = 2 * PI * i / N; 
            glVertex3f(x + cos(angle) * 15.0, 20 + y + sin(angle) * 15.0, 0.0);
            glVertex3f(x + cos(angle) * 20.0, 20 + y + sin(angle) * 20.0, 0.0);
         }
         glEnd();
         x = X + R/2 * cos(t);
         y = Y + R/2 * sin(t);
         glBegin(GL_TRIANGLE_STRIP);
         glColor3f(0.0, 0.0, 1.0);
         for(i = 0; i <= N; ++i) {
            angle = 2 * PI * i / N; 
            glVertex3f(x + cos(angle) * 15.0, 20 + y + sin(angle) * 15.0, 0.0);
            glVertex3f(x + cos(angle) * 20.0, 20 + y + sin(angle) * 20.0, 0.0);
         }
         t -= 2 * PI / numVertices;
         glEnd();
         glFlush();
         glClear(GL_COLOR_BUFFER_BIT);
         usleep(1000);
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
   glOrtho(-100.0, 200.0, -100.0, 200.0, -1.0, 1.0);
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
   cout <<"hit" << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
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