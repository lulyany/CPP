#ifndef _EX2_H_
#define _EX2_H_
#include "assignment.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
//struct point

typedef struct _Point
{
    float x, y;
} Point;

//Class Shape

class Shape
{
public:
    virtual void draw() = 0;
    virtual ~Shape() = 0;

protected:
    float r, g, b;
};
Shape::~Shape() {}
//Class Triangle

class Triangle : public Shape
{
public:
    Triangle(Point pt1, Point pt2, Point pt3, float red, float green, float blue); 
    void draw();

protected:
    Point p1, p2, p3;
};

Triangle::Triangle(Point pt1, Point pt2, Point pt3, float red, float green, float blue)
{
    p1 = pt1;
    p2 = pt2;
    p3 = pt3;
    r = red;
    g = green;
    b = blue;
}

void Triangle::draw()
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glEnd(); 
}

#endif