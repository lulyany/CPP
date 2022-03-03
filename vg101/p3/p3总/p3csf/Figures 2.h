#ifndef FIGURES_H
#define FIGURES_H
static const double PI=3.1415926535897932;

typedef struct _Point {double x,y;} Point;
class Shape {
    public: virtual void draw()=0;virtual ~Shape()=0;
    protected: float r,g,b;double angle;Point center;
};

class Circle : public Shape {
    public: Circle(Point pt={0.0,0.0},Point mid={0.0,0.0},
    float r1=1.0,float r=0, float g=0, float b=0,double degree=0.0);
    void draw();
    private:Point p;float radius;
};

class Halfcircle: public Shape{
private:
    Point pc;double arg; double ra;
public:
    Halfcircle(Point ptc,double radius,double argz,float red,float green,float blue);
    void draw();
};
class Rectangle : public Shape {
    public: Rectangle(Point pt1={-.5,-.5}, Point pt2={.5,.5},
    Point mid={0.0,0.0},float r=0, float g=0, float b=0,double degree=0.0);

    void draw();
    private: Point p1,p2;
};

class Triangle : public Shape {
    public: Triangle(Point pt1={-.5,-.5}, Point pt2={.5,-.5}, Point pt3={0,.5}, float r=0, float g=0, float b=0); 
    void draw();
    private: Point p1,p2,p3;
};

class Trapezium : public Shape {
    public: Trapezium(Point pt1={-1.0,-1.0}, Point pt2={1.0,-1.0}, Point pt3={0.5,0.5},
    Point pt4={-0.5,0.5},Point mid={0.0,0.0},float r=0, float g=0, float b=0,double degree=0.0);
    void draw();
    private: Point p1,p2,p3,p4;
};

#endif