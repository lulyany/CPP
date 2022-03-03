#ifndef CARS_H
#define CARS_H
#include "Figures.h"
#include "vec.h"

class Car {
    public:
    Car(Point pt1={0.0,0.0}, Point mid={0.0,0.0},double width=1.0,double height=.2,double angle=0.0);
    ~Car();
    void draw();
    void zoom(double *width,double *height,float k);

    private:
    Point p; double w, h, o; Shape *sh[4];

    void paint(float *r, float *g, float *b);

};

class Teleporter : public Rectangle {
    public:
    Teleporter(Point pt1={0.0,0.0},double length=1.0,double width=1.0);
    ~Teleporter();
    void draw();
    void paint(float *r, float *g, float *b);
    
    private:
    Point p1,p2;Rectangle *sh;
};

class Park {
    public:Park(Point pt={-.5,-1.0},double length=0.25,double width=0.01);
    ~Park();
    void draw();

    private:
    Point p1,p2;
    double l,w;Shape *sh[13];
};

class Grouptry {
    public:
    Grouptry(double length=0.25,double width=0.2);
    ~Grouptry();
    void draw();
    void randset();
    private:
    Park *P1;Teleporter *T1,*T2;
    double lx,ly;
};

#endif