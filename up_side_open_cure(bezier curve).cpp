#include<GL/glut.h>
#include<math.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

class Point
{
 public:
  float x, y;
  void setxy(float x2, float y2)
  {
    x = x2;
    y = y2;
  }
  const Point & operator=(const Point &rPoint)
  {
    x = rPoint.x;
    y = rPoint.y;
    return *this;
  }

};

Point abc[4];

void myInit() {
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,0.0,0.0);
  glPointSize(8.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,64.0,0.0,48.0);
}

void drawDot(int x, int y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
  glFlush();
}

void drawLine(Point p1, Point p2) {
  glLineWidth(5);
  glBegin(GL_LINES);
  glVertex2f(p1.x, p1.y);
  glVertex2f(p2.x, p2.y);
  glEnd();
  glFlush();
}

Point drawBezier(Point A, Point B, Point C, Point D, double t) {
  Point P;
  P.x = pow((1 - t), 3) * A.x + 3 * t * pow((1 -t), 2) * B.x + 3 * (1-t) * pow(t, 2)* C.x + pow (t, 3)* D.x;
  P.y = pow((1 - t), 3) * A.y + 3 * t * pow((1 -t), 2) * B.y + 3 * (1-t) * pow(t, 2)* C.y + pow (t, 3)* D.y;
  return P;
}



void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);
  Point POld=abc[0];
 
  //up open
  abc[0].x=12,abc[0].y=40;
  abc[1].x=25,abc[1].y=12;
  abc[2].x=38,abc[2].y=12;
  abc[3].x=50,abc[3].y=40;
    
  
  
  glColor3f(1.0,0.0,0.0);//red color
 for(int i=0;i<4;i++)
    drawDot(abc[i].x, abc[i].y);
  glColor3f(1.0,1.0,1.0);//white

  for(double t = 0.0;t <= 1.0; t += 0.1) {
    Point P = drawBezier(abc[0], abc[1], abc[2], abc[3],  t);
    drawLine(POld, P);
    POld = P;
  }
  
  glFlush();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100,150);
  glutCreateWindow("Up open Bezier Curve");
  glutDisplayFunc(myDisplay);
  myInit();
  glutMainLoop();
  return 0;
}
