#include <GL/glut.h>
#include <ctime>
#include <cstdlib>
#include <cmath>

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
};

Vec::Vec(float x1, float y1) {x = x1; y = y1;}

float Vec::getX() {return x;}
float Vec::getY() {return y;}

Vec Vec::operator+ (Vec v) {return Vec(x + v.getX(), y + v.getY());}
Vec Vec::operator- (Vec v) {return Vec(x - v.getX(), y - v.getY());}
Vec Vec::operator* (float k) {return Vec(x *k, y*k);}
float Vec::operator* (Vec v) {return x*v.getX()+y*v.getY();}
Vec Vec::operator>> (float degree) {
    return Vec((float)(x*cos(degree)+y*sin(degree)),(float)(-x*sin(degree)+y*cos(degree)));
}
Vec Vec::operator<< (float degree) {
    degree*=-1;
    return Vec((float)(x*cos(degree)+y*sin(degree)),(float)(-x*sin(degree)+y*cos(degree)));
}

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

class Rectangles : public Shape {
    public: Rectangles(Point pt1={-.5,-.5}, Point pt2={.5,.5},
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

Shape::~Shape(){}

Circle::Circle(Point pt,Point mid,float r1,float red, float green, float blue,double degree) {
    p=pt;radius=r1;r=red;g=green;b=blue;center=mid;angle=degree;
}

class Vec;
void Circle::draw() {
    int times=50;
    glColor3f(r,g,b);glBegin(GL_POLYGON);
    Vec dot((float)(p.x-center.x),(float)(p.y-center.y));
    dot=dot<<(float)angle;
    p.x=center.x+dot.getX();p.y=center.y+dot.getY();
    float degree=(float)(2*acos(-1)/times);
    for (int i=0;i<=times-1;i++) {
        glVertex2f((GLfloat)(p.x+radius*cos((float)i*degree)),(GLfloat)(p.y+radius*sin((float)i*degree)));
    }
    glEnd();
}

Rectangles::Rectangles(Point pt1, Point pt2,Point mid,float red, float green, float blue,double degree) {
    p1=pt1; p2=pt2; r=red; g=green; b=blue;angle=degree;center=mid;
}

class Vec;
void Rectangles::draw() {
    glColor3f(r, g, b); glBegin(GL_QUADS);
    Vec v1((float)(p1.x-center.x),(float)(p1.y-center.y));
    Vec v2((float)(p1.x-center.x),(float)(p2.y-center.y));
    Vec v3((float)(p2.x-center.x),(float)(p2.y-center.y));
    Vec v4((float)(p2.x-center.x),(float)(p1.y-center.y));
    v1=v1<<(float)angle;v2=v2<<(float)angle;v3=v3<<(float)angle;v4=v4<<(float)angle;
    
    glVertex2f((GLfloat)(center.x+v1.getX()), (GLfloat)(center.y+v1.getY())); 
    glVertex2f((GLfloat)(center.x+v2.getX()), (GLfloat)(center.y+v2.getY()));
    glVertex2f((GLfloat)(center.x+v3.getX()), (GLfloat)(center.y+v3.getY()));
    glVertex2f((GLfloat)(center.x+v4.getX()), (GLfloat)(center.y+v4.getY()));
    glEnd();
}

Triangle::Triangle(Point pt1, Point pt2, Point pt3,float red, float green, float blue) {
p1=pt1; p2=pt2; p3=pt3; r=red; g=green; b=blue;
}

void Triangle::draw() {
glColor3f(r, g, b); glBegin(GL_TRIANGLE_STRIP);
glVertex2f((GLfloat)p1.x, (GLfloat)p1.y); glVertex2f((GLfloat)p2.x, (GLfloat)p2.y); 
glVertex2f((GLfloat)p3.x, (GLfloat)p3.y);
glEnd();
}

Trapezium::Trapezium(Point pt1, Point pt2,Point pt3,Point pt4,
Point mid,float red, float green, float blue,double degree) {
    p1=pt1;p2=pt2;p3=pt3;p4=pt4;
    r=red;g=green;b=blue;
    angle=degree;center=mid;
}

class Vec;
void Trapezium::draw() {
    glColor3f(r,g,b);glBegin(GL_QUADS);
    Vec v1((float)(p1.x-center.x),(float)(p1.y-center.y));
    Vec v2((float)(p2.x-center.x),(float)(p2.y-center.y));
    Vec v3((float)(p3.x-center.x),(float)(p3.y-center.y));
    Vec v4((float)(p4.x-center.x),(float)(p4.y-center.y));
    v1=v1<<(float)angle;v2=v2<<(float)angle;v3=v3<<(float)angle;v4=v4<<(float)angle;

    glVertex2f((GLfloat)(center.x+v1.getX()), (GLfloat)(center.y+v1.getY())); 
    glVertex2f((GLfloat)(center.x+v2.getX()), (GLfloat)(center.y+v2.getY()));
    glVertex2f((GLfloat)(center.x+v3.getX()), (GLfloat)(center.y+v3.getY()));
    glVertex2f((GLfloat)(center.x+v4.getX()), (GLfloat)(center.y+v4.getY()));

    glEnd();
}

class Vec;
class Car {
    public:
    Car(Point pt1={0.0,0.0}, Point mid={0.0,0.0},double width=1.0,double height=.2,double angle=0.0);
    ~Car();
    void draw();
    void zoom(double *width,double *height,float k);
    void move(Vec v);

    private:
    Point p; double w, h; Shape *sh[4];

    void paint(float *r, float *g, float *b);

};

class Rectangles;
Car::Car(Point pt1, Point mid,double width, double height,double angle) {
    float r=0.0,g=0.0,b=1.0;
    float radius=(float)(width/16);
    Point p1,p2,p3,p4;p=pt1;
    w=width; h=height;
    srand((unsigned int)time(0));
    p1={p.x-w/2,p.y-h/2}; p2={p.x+w/2,p.y+h/2};
    paint(&r,&g,&b);sh[0]=new Rectangles(p1,p2,mid,r,g,b,angle);
    p1.x=p.x-w/4;
    paint(&r,&g,&b);sh[1]=new Circle(p1,mid,radius,r,g,b,angle);
    p1.x=p.x+w/4;
    sh[2]=new Circle(p1,mid,radius,r,g,b,angle);
    p1={p.x-w/2,p.y+h/2};p2={p.x+w/4,p.y+h/2};
    p3={p.x+w/8,p.y+h*1.5};p4={p.x-w/4-w/8,p.y+h*1.5};
    paint(&r,&g,&b);sh[3]=new Trapezium(p1,p2,p3,p4,mid,r,g,b,angle);
}

Car::~Car(){ for(int i=0;i<4;i++) delete sh[i]; }

void Car::draw() {
    for(int i=0;i<4;i++) sh[i]->draw();
}

void Car::zoom(double *width,double *height,float k) {
    using namespace std;
    w *= k;h *=k;*width=w;*height=h;
}

void Car::paint(float *r, float *g, float *b) {
    *r=(float)rand()/RAND_MAX;
    *g=(float)rand()/RAND_MAX;
    *b=(float)rand()/RAND_MAX;
}

void Car::move(Vec v) {
    p.x+=v.getX();p.y+=v.getY();
}

void TimeStep(int n) {
glutTimerFunc((unsigned int)n, TimeStep, n); glutPostRedisplay();
}

void glDraw() {
    double static width=1.0,height=0.2,angle=0.0;Point static point={0.0,0.0};
    int static cnt=0;
    Car zh(point,point,width,height,angle);
    Vec v1((float)0.01,0);Vec v2((float)-0.01,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if ((cnt%50+1)<=25) {zh.move(v1);point.x+=v1.getX();point.y+=v1.getY();}
    else  {zh.move(v2);point.x+=v2.getX();point.y+=v2.getY();}
    zh.draw();
    cnt++;
    glutSwapBuffers(); glFlush();
}


int main (int argc, char *argv[]) { 
    glutInit(&argc, argv);
    glutInitWindowSize(750,750);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Cars here!");
    glClearColor(1.0, 1.0, 1.0, 0.0); glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw); glutTimerFunc(25, TimeStep, 25);
    glutDisplayFunc(glDraw);
    glutMainLoop();
}