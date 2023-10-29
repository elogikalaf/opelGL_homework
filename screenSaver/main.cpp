#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;


int currentShape = 0;
int shapeDisplayTime = 100; // Reduced to 100 milliseconds for more frequent updates



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

void drawScene(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   // Based on the currentShape, call the corresponding draw function
   switch (currentShape) {
   case 0:
      drawPolygon1();
      break;
   case 1:
      drawPolygon2();
      break;
   case 2:
      drawPolygon3();
      break;
   case 3:
      drawPolygon4();
      break;
   case 4:
      drawPolygon5();
   default:
      break;
   }

   glFlush();
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
void updateScene(void) {
    srand(time(NULL));
    currentShape = rand() % 5;
    glutPostRedisplay();
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
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutIdleFunc(updateScene);

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}