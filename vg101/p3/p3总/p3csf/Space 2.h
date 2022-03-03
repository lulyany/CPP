#ifndef UFO_H
#define UFO_H
#include "Figures.h"
#include "vec.h"
class UFO {
    public:
    UFO(Point pt1={0.0,0.0}, double width=1.0,double degree=0.0);
    ~UFO();
    void draw();

    private:
    Point p; double w; Shape *sh[2];double angle;
    Circle *c[3];
};

class Spacecraft {
    public:
    Spacecraft(Point pt1={0.0,0.0}, double width=0.2,double height=0.4);
    ~Spacecraft();
    void draw();
    void zoom(double *width,double *height);

    private:
    double w,h;Shape *sh[9];Point p;
    void zoomin(double *width,double *height);
    void zoomout(double *width,double *height);
};



#endif