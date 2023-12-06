#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;


int currentPolygon = 0;

void drawPolygon1() {
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex3f(70.0, 80.0, 0.0);
   glVertex3f(80.0, 80.0, 0.0);
   glVertex3f(80.0, 90.0, 0.0);
   glVertex3f(70.0, 90.0, 0.0);
   glEnd();
}

void drawPolygon2() {
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex3f(10.0, 70.0, 0.0);
   glVertex3f(30.0, 70.0, 0.0);
   glVertex3f(30.0, 90.0, 0.0);
   glVertex3f(10.0, 90.0, 0.0);
   glEnd();
}

void drawPolygon3() {
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
   glVertex3f(40.0, 40.0, 0.0);
   glVertex3f(50.0, 40.0, 0.0);
   glVertex3f(50.0, 50.0, 0.0);
   glVertex3f(40.0, 50.0, 0.0);
   glEnd();
}

void drawPolygon4() {
   glColor3f(1.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
   glVertex3f(50.0, 50.0, 0.0);
   glVertex3f(70.0, 50.0, 0.0);
   glVertex3f(70.0, 70.0, 0.0);
   glVertex3f(50.0, 70.0, 0.0);
   glEnd();
}

void drawPolygon5() {
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
   glVertex3f(00.0, 30.0, 0.0);
   glVertex3f(15.0, 30.0, 0.0);
   glVertex3f(15.0, 45.0, 0.0);
   glVertex3f(00.0, 45.0, 0.0);
   glEnd();
}

void drawScene() {
   glClear(GL_COLOR_BUFFER_BIT);

   if (currentPolygon == 0) {
      drawPolygon1();
   } else if (currentPolygon == 1) {
      drawPolygon2();
   } else if (currentPolygon == 2) {
      drawPolygon3();
   } else if (currentPolygon == 3) {
      drawPolygon4();
   } else if (currentPolygon == 4) {
      drawPolygon5();
   }

   currentPolygon++;

   if (currentPolygon >= 5) {
      currentPolygon = 0;  // Reset to the first polygon
   }

   glFlush();
   glutSwapBuffers();
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
   glOrtho(-10.0, 100.0, 0.0, 100.0, -10.0, 10.0);
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
      default:
         break;
   }
}
// void updateScene(void) {
//     srand(time(NULL));
//     currentShape = rand() % 5;
//     glutPostRedisplay();
// }
void timer(int value) {
    glutPostRedisplay(); // Request a redisplay
    glutTimerFunc(1000, timer, 0); // Set the timer for the next polygon
}

// Main routine.
int main(int argc, char **argv) 
{
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("experimentTriangles.cpp");
   glutDisplayFunc(drawScene); 
   glutTimerFunc(0, timer, 0);  
   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}
