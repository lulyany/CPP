#ifndef VEC_H
#define VEC_H
#include "Figures.h"
#include "cars.h"

class Vec {
    private:float x,y;
    public:Vec(float x1=0.0, float y1=0.0);

    float getX();
    float getY();

    Vec operator+ (Vec v); 
    Vec operator- (Vec v);
    Vec operator* (float k);
    float operator* (Vec v);
    Vec operator>> (float degree);
    Vec operator<< (float degree);
    void Print();
};

class Figure {
    protected:Vec anchor;
    public:
    Figure() : anchor(0,0) {}

    Vec getAnchor(){return anchor;};
    void setAnchor(Vec a){anchor=a;};
    virtual void draw()=0;
    virtual void move(Vec dir)=0;
    virtual void rotate(float angle)=0;
    virtual void zoom(float k)=0;

    virtual ~Figure() {}
};

class Car;
class Park;
class Teleporter;
class Group : Figure {
    public:Group(Point pt1={0.0,0.0},double width=1.0,double height=0.2,double d=0.0);
        void draw();
        void move(Vec dir);
        void rotate(float angle);
        void zoom(float k);
        ~Group();
    private:
        Car *van;Park *parking;
        Point p;double w,h,degree;
};

#endif