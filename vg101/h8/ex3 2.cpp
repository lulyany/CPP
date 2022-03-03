#include "assignment.h"
#include <math.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
static const float PI = 3.14159265; 
class Point
{
public:
    Point(double _x = 0, double _y = 0)
    {
        x = (float)_x;
        y = (float)_y;
    }
    Point operator+(const Point &p)
    {
        return Point(x + p.x, y + p.y);
    }
    Point operator-(const Point &p)
    {
        return Point(x - p.x, y - p.y);
    }
    float getx() { return x; }
    float gety() { return y; }
    void draw()
    {
        glVertex3f(x, y, 0);
    }

private:
    float x, y;
};

class Shape
{
public:
    virtual void draw() = 0;
    virtual ~Shape() = 0;

protected:
    Point anchor;
};
Shape::~Shape() {}

class Color_shape : public Shape
{
public:
    void move()
    {
        anchor = anchor + v;
    };

protected:
    float r, g, b;
    Point v;
};

class Quadrilateral : public Color_shape
{
public:
    Quadrilateral(Point pt1 = {-0.4, 0.1}, Point pt2 = {0.3, 0.1},
                  Point pt3 = {0.1, 0.3}, Point pt4 = {-0.3, -0.3}, float rr = 0, float gg = 1, float bb = 0)
    {
        p1 = pt1;
        p2 = pt2;
        p3 = pt3;
        p4 = pt4;
        r = rr;
        b = bb;
        g = gg;
    };
    void draw();

protected:
    Point p1, p2, p3, p4;
};

void Quadrilateral::draw()
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    (p1 + anchor).draw();
    (p2 + anchor).draw();
    (p3 + anchor).draw();
    (p4 + anchor).draw();
    glEnd();
}

class rectangle : public Quadrilateral
{
public:
    rectangle(Point pt1 = {-0.5, 0}, Point pt3 = {0.5, 0.5},
              float rr = 1, float gg = 0, float bb = 0, Point a = {0, 0}, Point vv = {0.01, 0})
    {
        anchor = a;
        p1 = pt1;
        p2 = {pt3.getx(), pt1.gety()};
        p3 = pt3;
        p4 = {pt1.getx(), pt3.gety()};
        r = rr;
        g = gg;
        b = bb;
        v = vv;
    };
};

class circle : public Color_shape
{
public:
    circle(Point pt1 = {0, 0}, float ra = 0.5, Point a = {0, 0}, Point vv = {0.01, 0})
    {
        p1 = pt1;
        radius = ra;
        anchor = a;
        v = vv;
    };
    void draw();

private:
    Point p1;
    float radius;
};

void circle::draw()
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; ++i)
    {
        Point temp((anchor).getx() + radius * cos(2 * PI / 100 * i),
                   (anchor).getx() + radius * sin(2 * PI / 100 * i));
        temp.draw();
    }
    glEnd();
}

class Group : public Shape
{
public:
    virtual ~Group() = 0;

    void move()
    {
        for (int i = 0; i < 4; ++i)
        {
            com[i]->move();
        }
    }
    void draw()
    {
        for (int i = 0; i < 4; ++i)
        {
            com[i]->draw();
        }
    }

protected:
    Color_shape *com[4];
    Point v;
};

Group::~Group()
{
    for (int i = 0; i < 4; ++i)
    {
        delete com[i];
    }
}

class Car : public Group
{
public:
    Car()
    {
        Point p1 = {-0.4, -0.1};
        Point p3 = {0.5, 0.1};
        v = {0.01, 0};
        com[0] = new rectangle(p1, p3, 1, 0, 0, {0, 0});
        com[1] = new Quadrilateral;
        com[2] = new circle({-0.2, -0.1}, (float)0.1, {0, 0}, v);
        com[3] = new circle({0.2, -0.1}, (float)0.1, {0, 0}, v);
    }
};

void draw_shape()
{
    static Car a;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    a.draw();
    a.move();
    glFlush();
}

void timestep(int n)
{
    glutTimerFunc((unsigned)n, timestep, n);
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("ex3");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(-1, 5, -3, 3);
    glutDisplayFunc(draw_shape);
    glutTimerFunc(25, timestep, 25);
    glutMainLoop();
}