#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>


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

// Use the STL extension of C++.
using namespace std;

// Globals.
const int numVertices = 50; // Number of vertices on circle.
static int width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int shape = 3;
#define PI 3.14159265358979324


// Point class.
class Point
{
public:
   Point(int x, int y)
   {
	  xVal = x; yVal = y;
   }
   Point(){};
   void setCoords(int x, int y)
   {
	  xVal = x; yVal = y;
   }
   void drawPoint(void); // Function to draw a point.
   int getCoordsX()
   {
      return xVal;
   }
   int getCoordsY()
   {
      return yVal;
   }
private:
   int xVal, yVal; // x and y co-ordinates of point.
   static float size; // Size of point.
};

float Point::size = pointSize; // Set point size.

// Function to draw a point.
void Point::drawPoint(void)
{  
   glPointSize(size);
   glBegin(GL_POINTS);
   glVertex3f(xVal, yVal, 0.0);
   glEnd();   
}
// Line class
class Line
{
   public:
      Line(Point p1, Point p2) 
      {
         this->p1 = p1;
         this->p2 = p2;
      }
      void setPoints(Point p1, Point p2){
         this->p1 = p1;
         this->p2 = p2;
      }
      void drawLine(void) {
         glBegin(GL_LINES);
         glVertex2f(p1.getCoordsX(), p1.getCoordsY());
         glVertex2f(p2.getCoordsX(), p2.getCoordsY());   
         glEnd();
         glFlush();
      }
   private:
      Point p1;
      Point p2;
};
class Circle 
{
   public:
      Circle(Point p1, Point p2)
      {
         this->p1 = p1;
         this->p2 = p2;
      }

      void setPoints(Point p1, Point p2){
         this->p1 = p1;
         this->p2 = p2;
      }
      void drawCircle(void)
      {
         float t = 0;
         glBegin(GL_LINE_LOOP);
         // R = distance between p1 and p2
         float R = sqrt(pow(p2.getCoordsX() - p1.getCoordsX(), 2) + pow(p2.getCoordsY() - p1.getCoordsY(), 2));
         glBegin(GL_LINE_LOOP);
         for (int i = 0; i < numVertices; ++i)
         {
            glVertex3f(p1.getCoordsX() + R * cos(t), p1.getCoordsY() + R * sin(t), 0.0);
            t += 2 * PI / numVertices;
         }
         glEnd();
         glFlush();
      }

   private:
      Point p1;
      Point p2;
};
class Square
{
public:
   Square(Point p1, Point p2)
   {
      this->p1 = p1;
      this->p2 = p2;
   }

   void setPoints(Point p1, Point p2)
   {
      this->p1 = p1;
      this->p2 = p2;
   }
   void drawSquare(void)
   {
      glBegin(GL_LINE_LOOP);
      glVertex2f(p1.getCoordsX(), p1.getCoordsY());
      glVertex2f(p1.getCoordsX(), p2.getCoordsY());
      glVertex2f(p2.getCoordsX(), p2.getCoordsY());
      glVertex2f(p2.getCoordsX(), p1.getCoordsY());
      glEnd();
      glFlush();
   }

private:
   Point p1;
   Point p2;
};
// Vector of points.
vector<Point> points;

// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator;

// Currently clicked point.
Point currentPoint;

// Last Time a Point was clicked.
Point lastClickedPoint;

// a vector to store all lines
vector<Line> lines;

// Iterator to traverse a Line array.
vector<Line>::iterator linesIterator;

/// a vector to hold all circles
vector<Circle> circles;

// Iterator oto traverse a Circle array.
vector<Circle>::iterator circleIterator;

// a vector to hold all squares
vector<Square> squares;

// Iterator to traverse a Sqare array
vector<Square>::iterator squareIterator;

// Drawing routine.
void drawScene(void)
{
   glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);

   glFlush();

   // lines
   linesIterator = lines.begin();
   while (linesIterator != lines.end())
   {
      linesIterator->drawLine();
      linesIterator++;
   }
   // points
   pointsIterator = points.begin();
   while (pointsIterator != points.end())
   {
      pointsIterator->drawPoint();
      pointsIterator++;
   }

   // circle
   circleIterator = circles.begin();
   while (circleIterator != circles.end())
   {
      circleIterator->drawCircle();
      circleIterator++;
   }
   // square
   squareIterator = squares.begin();
   while (squareIterator != squares.end())
   {
      squareIterator->drawSquare();
      squareIterator++;
   }

   lastClickedPoint.drawPoint();
   currentPoint.drawPoint();

   switch (shape)
   {
   case 0:
   {
      if (lines.size() >= 1)
      {
         Line currentLine(lastClickedPoint, currentPoint);
         currentLine.drawLine();
      }
      break;
   }

   case 2:
   {
      if (circles.size() >= 1)
      {
         Circle currentCircle(lastClickedPoint, currentPoint);
         currentCircle.drawCircle();
      }
      break;
   }

   case 3:
   {
      if (squares.size() >= 1)
      {
         Square currentSquare(lastClickedPoint, currentPoint);
         currentSquare.drawSquare();
      }
      break;
   }
   }

   glFlush();
}

void keyInput(unsigned char key, int x, int y)
{
   switch (key) 
   {
      case 27:
         exit(0);
         break;
      case '1':
         shape = 0;
         glutPostRedisplay();
         break;
      case '2':
         shape = 2;
         glutPostRedisplay();
         break;
      case '3':
         shape = 3;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}


// Mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
   // Store the clicked point in the currentPoint variable when left button is pressed.
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      lastClickedPoint.setCoords(x, height - y);
      currentPoint = Point(x, height - y); 
      switch (shape) {
         case 0: {
            Line line(lastClickedPoint, currentPoint);  
            lines.push_back(line);
            break;
         }
         case 1: {
            points.push_back(currentPoint);
            break;
         }
         case 2: {
            Circle circle(lastClickedPoint, currentPoint);
            circles.push_back(circle);
            break;
         }
         case 3: {
            Square square(lastClickedPoint, currentPoint);
            squares.push_back(square);
            break;
         }
         glutPostRedisplay();
      }

   }

   // Store the currentPoint in the points vector when left button is released.
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      switch (shape)
      {
      case 0:
      {
         Line line(lastClickedPoint, currentPoint);
         lines.push_back(line);
         break;
      }
      case 1:
      {
         points.push_back(currentPoint);
         break;
      }
      case 2:
      {
         Circle circle(lastClickedPoint, currentPoint);
         circles.push_back(circle);
         break;
      }
      case 3:
      {
         Square square(lastClickedPoint, currentPoint);
         squares.push_back(square);
         break;
      }
         glutPostRedisplay();
      }

         if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
            exit(0);

         glutPostRedisplay();
      }
}

// Mouse motion callback routine.
void mouseMotion(int x, int y)
{
   // Update the location of the current point as the mouse moves with button pressed.
   currentPoint.setCoords(x, height - y);   
   Line line(lastClickedPoint, currentPoint);


   glutPostRedisplay();
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport (0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Set viewing box dimensions equal to window dimensions.
   glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

   // Pass the size of the OpenGL window to globals.
   width = w; 
   height = h; 

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Left mouse click to draw a square point, keep left button pressed to drag point," << endl 
        << "right mouse click to exit." << endl;
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
   glutCreateWindow("mouseMotion.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);

   // Register the mouse callback function.
   glutMouseFunc(mouseControl); 

   // Register the mouse motion callback function.
   glutMotionFunc(mouseMotion);

   glewExperimental = GL_TRUE; 
   glewInit(); 
   
   setup(); 

   glutMainLoop(); 
}
