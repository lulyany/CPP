#include <iostream>
#include <cmath>
#include<GL/glut.h>
#include <ctime>
#include <cstdlib>
#define PI 3.14159265358979323
typedef struct _point{
    double x,y;
}point;

point spinng(point spct,point tosp,double arg){
    point pp;
    pp.x=spct.x+(tosp.x-spct.x)*cos(arg)-(tosp.y-spct.y)*sin(arg);
    pp.y=spct.y+(tosp.x-spct.x)*sin(arg)+(tosp.y-spct.y)*cos(arg);
    return pp;
}

void TimeStep(int n) {
    glutTimerFunc(n, TimeStep, n); glutPostRedisplay();
}

class Shape {
protected:
    float r,g,b;
public:
    virtual void draw()=0;
    virtual ~Shape()=default;
};

class Circle: public Shape{
private:
    point pc; double ra;
public:
    Circle(point ptc,double radius,float red,float green,float blue){
        pc=ptc;
        ra=radius;
        r=red;
        g=green;
        b=blue;
    }
    void draw(){
        int n=3600;
        //glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(0,0,0,0);
        glColor3f(r,g,b);
        glBegin(GL_POLYGON);
        for(int i=0;i<n;i++)
        {
            glVertex2f(pc.x+ra*cos(2*PI*i/n),pc.y+ra*sin(2*PI*i/n));   //定义顶点
        }
        glEnd();

    }
    //~Circle(){};
};

class Halfcircle: public Shape{
private:
    point pc;double arg; double ra;
public:
    Halfcircle(point ptc,double radius,double argz,float red,float green,float blue){
        pc=ptc;arg=argz;r=red;g=green;b=blue;ra=radius;
    }
    void draw(){
        int n=3600;
        //glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(0,0,0,0);
        glColor3f(r,g,b);
        glBegin(GL_POLYGON);
        for(int i=0;i<n/2;i++)
        {
            glVertex2f(ra*cos(2*PI*i/n+arg)+pc.x,ra*sin(2*PI*i/n+arg)+pc.y);   //定义顶点
        }
        glEnd();

    }
};

class Rectangle: public Shape{
private:
    point p1,p2;
public:
    void draw(){
        glColor3f(r, g, b); glBegin(GL_QUADS);
        glVertex2f(p1.x, p1.y); glVertex2f(p2.x, p1.y);
        glVertex2f(p2.x, p2.y); glVertex2f(p1.x, p2.y); glEnd();
    }
    Rectangle(point pt1,point pt2,float red,float green,float blue){
        p1=pt1;p2=pt2;r=red;g=green;b=blue;
    }
    //~Rectangle(){};

};

class Triangle: public Shape{
private:
    point p1,p2,p3;
public:
    Triangle(point pt1,point pt2,point pt3,float red,float green,float blue){
        p1=pt1;
        p2=pt2;
        p3=pt3;
        r=red;
        b=blue;
        g=green;
    }
    void draw(){
        glColor3f(r, g, b); glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(p1.x, p1.y); glVertex2f(p2.x, p2.y); glVertex2f(p3.x, p3.y);
        glEnd();
    }
    //~Triangle(){};
};
class Parallelogram: public Shape{
private:
    point p1,p2,pc;
public:
    Parallelogram(point pt1,point pt2,point ptc,float red,float green,float blue){
        r=red;
        g=green;
        b=blue;
        p1=pt1;
        p2=pt2;
        pc=ptc;
    }
    void draw(){
        glColor3f(r,g,b);glBegin(GL_QUADS);
        glVertex2f(p1.x,p1.y);glVertex2f(p2.x,p2.y);
        glVertex2f(2*pc.x-p1.x,2*pc.y-p1.y);glVertex2f(2*pc.x-p2.x,2*pc.y-p2.y);
        glEnd();
    }
};

class Traoezium: public Shape{
private:
    point p1,p2,p3,p4;
public:
    Traoezium(point pt1,point pt2,point pt3,point pt4,float red,float green,float blue){
        p1=pt1;
        p2=pt2;
        p3=pt3;
        p4=pt4;
        r=red;
        g=green;
        b=blue;
    }
    void draw(){
        glColor3f(r,g,b);
        glBegin(GL_QUADS);
        glVertex2f(p1.x,p1.y);glVertex2f(p2.x,p2.y);glVertex2f(p3.x,p3.y);glVertex2f(p4.x,p4.y);
        glEnd();
    }
    //~Traoezium(){};
};


class Veh{
protected:
    point centerpoint;
    double length,height,arg;
public:
    virtual void draw()=0;
    virtual ~Veh(){};
    virtual void move(point* ppp,double* le,double* he)=0;
    virtual void spin(double* argg)=0;
    virtual void zoom(double* len,double* hei,double k)=0;
};

class Car: public Veh{
private:
    Shape *sh[5];
public:
    ~Car(){
        for(int i=0;i<4;i++){ delete sh[i];}
    }
    Car(point pc,double l,double h,double argz){
        centerpoint=pc;
        length=l;
        height=h;
        arg=argz;
        point pp1,pp2,pp3,pp4,pp5,pp6,pp7,pp8,pp9,pp10;
        pp1={centerpoint.x-length/2,centerpoint.y-height/4};pp2={centerpoint.x-length/2,centerpoint.y+height/4};
        pp3={centerpoint.x+length/2,centerpoint.y+height/4};pp4={centerpoint.x+length/2,centerpoint.y-height/4};
        pp5={centerpoint.x-length/4,centerpoint.y-height/4};pp6={centerpoint.x+length/4,centerpoint.y-height/4};
        pp7={centerpoint.x-3*length/8,centerpoint.y};pp10={centerpoint.x+3*length/8,centerpoint.y};
        pp8={centerpoint.x-length/8,centerpoint.y+3*height/4};pp9={centerpoint.x+length/8,centerpoint.y+3*height/4};

        pp1=spinng(centerpoint,pp1,arg);pp2=spinng(centerpoint,pp2,arg);pp3=spinng(centerpoint,pp3,arg);
        pp4=spinng(centerpoint,pp4,arg);pp5=spinng(centerpoint,pp5,arg);pp6=spinng(centerpoint,pp6,arg);
        pp7=spinng(centerpoint,pp7,arg);pp8=spinng(centerpoint,pp8,arg);pp9=spinng(centerpoint,pp9,arg);
        pp10=spinng(centerpoint,pp10,arg);
        sh[0]=new class Circle(pp5,length/8,1,0,0);
        sh[1]=new class Circle(pp6,length/8,1,0,0);
        sh[2]=new class Traoezium(pp7,pp8,pp9,pp10,0,1,0);
        sh[3]=new class Traoezium(pp1,pp2,pp3,pp4,0,1,1);
    }
    void move(point* ppp,double* le,double* he){
        double static delta=0.05;
        if(centerpoint.x>0.5||centerpoint.x<-0.5){delta=-delta;centerpoint.x+=2*delta;ppp->x=centerpoint.x;}
        else{centerpoint.x+=delta;ppp->x=centerpoint.x;}
    }
    void spin(double* argg){
        double static delratheta=0.1;
        if(arg>2||arg<0){delratheta=-delratheta;arg+=2*delratheta;*argg=arg;}
        else{arg+=delratheta;*argg=arg;}
    }
    void zoom(double* len,double* hei,double k){
        length*=k;
        height*=k;
        *len=length;
        *hei=height;
    }
    void draw(){
        for(int i=0;i<4;i++){
            sh[i]->draw();
        }

    }
};


class UFO: public Veh{
private:
    Shape *sh[3];
public:
    ~UFO(){
        for(unsigned int i=0;i<3;i++){
            delete sh[i];
        }
    }
    UFO(point pc,double l,double h,double argz){
        centerpoint=pc;length=l;height=h;arg=argz;
        point pp1,pp2,pp3,pp4,pp5,pp6,pp7,pp8;
        pp1={centerpoint.x-5*length/12,centerpoint.y-2*height/7};pp4={centerpoint.x-length/12,centerpoint.y-2*height/7};
        pp2={centerpoint.x-5*length/12,centerpoint.y};pp3={centerpoint.x-length/12,centerpoint.y};
        pp5={centerpoint.x+length/12,centerpoint.y-2*height/7};pp8={centerpoint.x+5*length/12,centerpoint.y-2*height/7};
        pp6={centerpoint.x+length/12,centerpoint.y};pp7={centerpoint.x+5*length/12,centerpoint.y};

        pp1=spinng(centerpoint,pp1,arg);pp2=spinng(centerpoint,pp2,arg);pp3=spinng(centerpoint,pp3,arg);
        pp4=spinng(centerpoint,pp4,arg);pp5=spinng(centerpoint,pp5,arg);pp6=spinng(centerpoint,pp6,arg);
        pp7=spinng(centerpoint,pp7,arg);pp8=spinng(centerpoint,pp8,arg);
        sh[0]=new class Halfcircle(centerpoint,length/2,arg,0,0,1);
        sh[1]=new class Traoezium(pp1,pp2,pp3,pp4,0,1,0);
        sh[2]=new class Traoezium(pp5,pp6,pp7,pp8,0,1,0);
    }
    void draw(){
        for(int i=0;i<3;i++){
            sh[i]->draw();
        }
    }
    void spin(double* argg){
        double static delratheta=0.1;
        if(arg>2||arg<0){delratheta=-delratheta;arg+=2*delratheta;*argg=arg;}
        else{arg+=delratheta;*argg=arg;}
    }
    void move(point* ppp,double* le,double* he){
        double static delta=0.05;
        if(centerpoint.x>0.5||centerpoint.x<-0.5){delta=-delta;centerpoint.x+=2*delta;ppp->x=centerpoint.x;}
        else{centerpoint.x+=delta;ppp->x=centerpoint.x;}
    }
    void zoom(double* len,double* hei,double k){
        length*=k;
        height*=k;
        *len=length;
        *hei=height;
    }
};

class Teleported: public Veh{
private:
    Shape *sh;
public:
    ~Teleported(){
        delete sh;
    }
    Teleported(point pc,double l,double h,double argz){
        centerpoint=pc;length=l;height=h;arg=argz;
        point pp1,pp2,pp3,pp4;
        float r,g,b;
        paint(&r,&g,&b);
        pp1={centerpoint.x-length/2,centerpoint.y-height/2};pp2={centerpoint.x-length/2,centerpoint.y+height/2};
        pp3={centerpoint.x+length/2,centerpoint.y+height/2};pp4={centerpoint.x+length/2,centerpoint.y-height/2};
        sh=new class Traoezium(pp1,pp2,pp3,pp4,r,g,b);
    }
    void draw(){
        sh->draw();
    }
    void spin(double* argg){
        double static delratheta=0.1;
        if(arg>2||arg<0){delratheta=-delratheta;arg+=2*delratheta;*argg=arg;}
        else{arg+=delratheta;*argg=arg;}
    }
    void move(point* ppp,double* le,double* he){
        double static delta=0.05;
        if(centerpoint.x>0.5||centerpoint.x<-0.5){delta=-delta;centerpoint.x+=2*delta;ppp->x=centerpoint.x;}
        else{centerpoint.x+=delta;ppp->x=centerpoint.x;}
    }
    void zoom(double* len,double* hei,double k){
        length*=k;
        height*=k;
        *len=length;
        *hei=height;
    }
    void paint(float* r,float* g,float* b){
        *r=(float)rand()/RAND_MAX;
        *g=(float)rand()/RAND_MAX;
        *b=(float)rand()/RAND_MAX;
    }
};

class Spacecraft: public Veh{
private:
    Shape *sh[7];
public:
    ~Spacecraft(){
        for(unsigned int i=0;i<6;i++){
            delete sh[i];
        }
    }
    Spacecraft(point pc,double l,double h,double argz){
        centerpoint=pc;length=l;height=h;arg=argz;
        point pp1,pp2,pp3,pp4,pp5,pp6,pp7,pp8,pp9,pp10,pp11,pp12,pp13,pp14,pp15,pp16,pp17;
        pp1={centerpoint.x-length/4,centerpoint.y-height/4};pp4={centerpoint.x+length/4,centerpoint.y-height/4};
        pp2={centerpoint.x-length/8,centerpoint.y-height/6};pp3={centerpoint.x+length/8,centerpoint.y-height/6};
        pp5={centerpoint.x-length/2,centerpoint.y-height/6};pp10={centerpoint.x+length/2,centerpoint.y-height/6};
        pp7={centerpoint.x-length/4,centerpoint.y-height/6};pp8={centerpoint.x+length/4,centerpoint.y-height/6};
        pp6={centerpoint.x-length/4,centerpoint.y+height/6};pp9={centerpoint.x+length/4,centerpoint.y+height/6};
        pp11={centerpoint.x-length/4,centerpoint.y+height/2};pp12={centerpoint.x+length/4,centerpoint.y+height/2};
        pp13={centerpoint.x,centerpoint.y+3*height/4};
        pp14={centerpoint.x-length/8,centerpoint.y+height/4};pp17={centerpoint.x+length/8,centerpoint.y+height/4};
        pp15={centerpoint.x-length/8,centerpoint.y+5*height/12};pp16={centerpoint.x+length/8,centerpoint.y+5*height/12};

        pp1=spinng(centerpoint,pp1,arg);pp2=spinng(centerpoint,pp2,arg);pp3=spinng(centerpoint,pp3,arg);
        pp4=spinng(centerpoint,pp4,arg);
        pp5=spinng(centerpoint,pp5,arg);pp6=spinng(centerpoint,pp6,arg);pp7=spinng(centerpoint,pp7,arg);
        pp8=spinng(centerpoint,pp8,arg);pp9=spinng(centerpoint,pp9,arg);pp10=spinng(centerpoint,pp10,arg);
        pp11=spinng(centerpoint,pp11,arg);pp12=spinng(centerpoint,pp12,arg);pp13=spinng(centerpoint,pp13,arg);
        pp14=spinng(centerpoint,pp14,arg);pp15=spinng(centerpoint,pp15,arg);pp16=spinng(centerpoint,pp16,arg);
        pp17=spinng(centerpoint,pp17,arg);

        sh[0]=new Traoezium(pp1,pp2,pp3,pp4,0,1,1);
        sh[1]=new Triangle(pp5,pp6,pp7,1,0,1);
        sh[2]=new Triangle(pp8,pp9,pp10,1,0,1);
        sh[3]=new Triangle(pp11,pp12,pp13,1,0,0);
        sh[4]=new Traoezium(pp7,pp11,pp12,pp8,0,1,0);
        sh[5]=new Traoezium(pp14,pp15,pp16,pp17,0,0,1);
    }
    void draw(){
        for(int i=0;i<6;i++){
           sh[i]->draw();
       }
    }
    void spin(double* argg){
        double static delratheta=0.1;
        if(arg>2||arg<0){delratheta=-delratheta;arg+=2*delratheta;*argg=arg;}
        else{arg+=delratheta;*argg=arg;}
    }
    void move(point* ppp,double* le,double* he){
        double static delta=0.05;
        if(centerpoint.x>0.5||centerpoint.x<-0.5){delta=-delta;centerpoint.x+=2*delta;ppp->x=centerpoint.x;}
        else{centerpoint.x+=delta;ppp->x=centerpoint.x;}
    }
    void zoom(double* len,double* hei,double k){
        length*=k;
        height*=k;
        *len=length;
        *hei=height;
    }
};

void glDraw(){
    point static p00={0,0};
    double static le=0.4;
    double static he=0.6;
    double static arggg=0;
    double static k=1.01;
    Spacecraft aa(p00,le,he,arggg);
    //if(le>=1){k=0.99;}
    //else if(le<=0.6){k=1.01;}
    //aa.zoom(&le,&he,k);
    //aa.move(&p00,&le,&he);
    aa.spin(&arggg);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    aa.draw();glutSwapBuffers(); glFlush();
}

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    // glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Home sweet home");
    glClearColor(1.0, 1.0, 1.0, 0.0); glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw); glutTimerFunc(25, TimeStep, 25);
    glutMainLoop();
    return 0;
}
