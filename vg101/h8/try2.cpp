#include "assignment.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
//g++ -Wall -Wextra -Wpedantic -Werror -std=c++14 -o MyProg ex2.cpp -lglu32 -lfreeglut -lopengl32
void ex2()
{
    //Write code for exercise 2
}

typedef struct _Point
{
    float x, y;
} Point;
class Shape
{
public:
    virtual void draw() = 0;
    virtual ~Shape() = 0;

protected:
    float r, g, b;
};
Shape::~Shape() {}

class Triangle : public Shape
{
public:
    Triangle(Point pt1 = {-5, -5}, Point pt2 = {5, 5},
             Point pt3 = {0, 5}, float r = 1, float g = 0, float b = 0);
    void draw();

protected:
    Point p1, p2, p3;
};

Triangle::Triangle(Point pt1, Point pt2, Point pt3, float rr, float gg, float bb)
{
    p1 = pt1;
    p2 = pt2;
    p3 = pt3;
    r = rr;
    g = gg;
    b = bb;
}

void Triangle::draw()
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glEnd();
}

class Parallelogram : public Shape
{
public:
    Parallelogram(Point pt1 = {-0.5, 0.5}, Point pt2 = {0.5, 0.5},
                  Point pt3 = {0, 0}, float r = 0, float g = 0, float b = 0);
    void draw();

private:
    Point p1, p2, p3, p4;
};

Parallelogram::Parallelogram(Point pt1, Point pt2, Point pt3, float rr, float gg, float bb)
{
    p1 = pt1;
    p2 = pt2;
    p3 = pt3;
    p4.x = p2.x - p1.x + p3.x;
    p4.y = p2.y - p1.y + p3.y;
    r = rr;
    g = gg;
    b = bb;
}
void Parallelogram::draw()
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glVertex2f(p4.x, p4.y);
    glEnd();
}

class Quadrilateral : public Shape
{
public:
    Quadrilateral(Point pt1 = {-0.5, 0.5}, Point pt2 = {0.5, 0.5},
                  Point pt3 = {-0.5, 0}, Point pt4 = {1, 0}, float r = 0, float g = 0, float b = 0);
    void draw();

protected:
    Point p1, p2, p3, p4;
};

Quadrilateral::Quadrilateral(Point pt1, Point pt2, Point pt3, Point pt4, float rr, float gg, float bb)
{
    p1 = pt1;
    p2 = pt2;
    p3 = pt3;
    p4 = pt4;
    r = rr;
    g = gg;
    b = bb;
}
void Quadrilateral::draw()
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glVertex2f(p4.x, p4.y);
    glEnd();
}

class Rectangle1 : public Quadrilateral
{
public:
    Rectangle1(Point pt1 = {-0.5, -1}, Point pt4 = {0.5, 1}, float rr = 0, float gg = 0, float bb = 0);
    void draw();
};

Rectangle1::Rectangle1(Point pt1, Point pt4, float rr, float gg, float bb)
{
    p1 = pt1;
    p4 = pt4;
    p2.x = p4.x;
    p2.y = p1.y;
    p3.x = p1.x;
    p3.y = p4.y;
    r = rr;
    g = gg;
    b = bb;
}

void Rectangle1::draw()
{
    Quadrilateral::draw();
}

class Trapezium : public Quadrilateral
{
public:
    Trapezium(Point pt1 = {-0.5, 0}, Point pt2 = {1, 0},
              Point pt3 = {0.5, 1}, Point pt4 = {0, 1}, float r = 0, float g = 0, float b = 0);

private:
    Point p1, p2, p3, p4;
};

Trapezium::Trapezium(Point pt1, Point pt2, Point pt3, Point pt4, float rr, float gg, float bb)
{
    p1 = pt1;
    p2 = pt2;
    p3 = pt3;
    p4 = pt4;
    r = rr;
    g = gg;
    b = bb;
}

void TimeStep(int n)
{
    glutTimerFunc((unsigned int)n, TimeStep, n);
    glutPostRedisplay();
}

void draw_shape()
{
    Triangle a = Triangle();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    a.draw();
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("ex2");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(draw_shape);
    /* tell GLUT to wait for events */
    glutTimerFunc(25, TimeStep, 1);
    glutMainLoop();
}