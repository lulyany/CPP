#include <iostream>
#include <cmath>
#include<GL/glut.h>
#include <ctime>
#include <cstdlib>
#include <map>
#include <vector>
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
            glVertex2f((GLfloat)(pc.x+ra*cos(2*PI*i/n)),(GLfloat)(pc.y+ra*sin(2*PI*i/n)));   //定义顶点
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
            glVertex2f((GLfloat)(ra*cos(2*PI*i/n+arg)+pc.x),(GLfloat)(ra*sin(2*PI*i/n+arg)+pc.y));   //定义顶点
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
        glVertex2f((GLfloat)p1.x, (GLfloat)p1.y); glVertex2f((GLfloat)p2.x, (GLfloat)p1.y);
        glVertex2f((GLfloat)p2.x, (GLfloat)p2.y); glVertex2f((GLfloat)p1.x, (GLfloat)p2.y); glEnd();
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
        glVertex2f((GLfloat)p1.x, (GLfloat)p1.y); glVertex2f((GLfloat)p2.x, (GLfloat)p2.y); glVertex2f((GLfloat)p3.x, (GLfloat)p3.y);
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
        glVertex2f((GLfloat)p1.x,(GLfloat)p1.y);glVertex2f((GLfloat)p2.x,(GLfloat)p2.y);
        glVertex2f((GLfloat)(2*pc.x-p1.x),(GLfloat)(2*pc.y-p1.y));glVertex2f((GLfloat)(2*pc.x-p2.x),(GLfloat)(2*pc.y-p2.y));
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
        glVertex2f((GLfloat)p1.x,(GLfloat)p1.y);glVertex2f((GLfloat)p2.x,(GLfloat)p2.y);glVertex2f((GLfloat)p3.x,(GLfloat)p3.y);glVertex2f((GLfloat)p4.x,(GLfloat)p4.y);
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
    void move(point* ppp,double delta_x,double delta_y){
        ppp->x+=delta_x;ppp->y+=delta_y;
        //centerpoint.x+=delta_x;centerpoint.y+=delta_y;ppp->x=centerpoint.x;ppp->y=centerpoint.y;
    }
    void spin(double* argg,double delta_arg){
        //double static delratheta=0.1;
        //if(arg>2||arg<0){delratheta=-delratheta;arg+=2*delratheta;*argg=arg;}
        //else{arg+=delratheta;*argg=arg;}
        *argg+=delta_arg;
    }
    void zoom(double* len,double* hei,double k){
        *len*=k;
        *hei*=k;
    }
    int check(point pt,point* ptt){
        if(abs(pt.x-ptt->x)<2&&abs(ptt->y-pt.y)<2){return 1;}
        else return 0;
    }
    virtual void move1(point* ppp,double* argg,double* l,double* h,point pt1,point pt2)=0;

    void spinn(double* argg){
        double static delratheta=0.1;
        if(arg>2||arg<0){delratheta=-delratheta;arg+=2*delratheta;*argg=arg;}
        else{arg+=delratheta;*argg=arg;}
    }
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
    void draw(){
        for(int i=0;i<4;i++){
            sh[i]->draw();
        }

    }
    void move1(point* ppp,double* argg,double* len,double* hei,point pt1,point pt2){//pt1 represent
        double static deltax=1,deltay=1;
        int flaggg=1;
        *len+=1;*len-=1;*hei-=1;*hei+=1;
        if(pt1.y<40){
            if(abs(centerpoint.x+10)<1&&centerpoint.y<30){flaggg=1;}
            else if(abs(centerpoint.y-30)<1&&centerpoint.x<pt1.x){flaggg=0;}
            else if(abs(centerpoint.x-pt1.x)<5&&centerpoint.y>=pt2.y){flaggg=3;}
            else{flaggg=5;}
            if(abs(centerpoint.x+10)<1&&abs(centerpoint.y-30)<1){spin(argg,-PI/2);}
            if(abs(centerpoint.x-pt1.x)<5&&abs(centerpoint.y-pt1.y)<=5.0){spin(argg,PI/2);}
        }else{
            if(abs(centerpoint.x+10)<1&&centerpoint.y<30){flaggg=1;}
            else if(abs(centerpoint.y-30)<1&&centerpoint.x<50){flaggg=0;}
            else if(abs(centerpoint.x-50)<1&&centerpoint.y<pt1.y){flaggg=1;}
            else if(abs(centerpoint.y-pt1.y)<5&&centerpoint.x>=pt1.x){flaggg=2;}
            else if(centerpoint.y<pt2.y){flaggg=1;}
            else{flaggg=5;}
            if(centerpoint.x==-10&&centerpoint.y==30){spin(argg,-PI/2);}
            if(centerpoint.x==50&&centerpoint.y==30){spin(argg,PI/2);}
            if(centerpoint.x==50&&abs(centerpoint.y-pt1.y)<5){spin(argg,PI/2);}
            if(centerpoint.x==pt1.x&&centerpoint.y==pt1.y){spin(argg,PI/2);}
        }

        switch (flaggg) {
            case 0:
                move(ppp,deltax,0);
                break;
            case 1:
                move(ppp,0,deltay);
                break;
            case 2:
                move(ppp,-deltax,0);
                break;
            case 3:
                move(ppp,0,-deltay);
                break;
            default:
                break;
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
    void spin1(double* argg){
        double static deltatheta=0.05;
        int static flag=1;
        if(*argg<-PI/6){flag=1;}
        if(*argg>PI/6){flag=0;}
        if(flag==1){*argg+=deltatheta;}
        if(flag==0){*argg-=deltatheta;}
    }
    void move1(point* ppp,double* argg,double* len,double* hei,point pt1,point pt2){//pt1 represent
        double static deltax=1,deltay=1;
        int flaggg=1;
        *len+=1;*len-=1;*hei+=1;*hei-=1;
        if(pt1.y<40){
            if(abs(centerpoint.x+10)<1&&centerpoint.y<30){flaggg=1;}
            else if(abs(centerpoint.y-30)<1&&centerpoint.x<pt1.x){flaggg=0;}
            else if(abs(centerpoint.x-pt1.x)<5&&centerpoint.y>=pt2.y){flaggg=3;}
            else{flaggg=5;}
        }else{
            if(abs(centerpoint.x+10)<1&&centerpoint.y<30){flaggg=1;}
            else if(abs(centerpoint.y-30)<1&&centerpoint.x<50){flaggg=0;}
            else if(abs(centerpoint.x-50)<1&&centerpoint.y<pt1.y){flaggg=1;}
            else if(abs(centerpoint.y-pt1.y)<5&&centerpoint.x>=pt1.x){flaggg=2;}
            else if(centerpoint.y<pt2.y){flaggg=1;}
            else{flaggg=5;}
        }

        switch (flaggg) {
            case 0:
                move(ppp,deltax,0);
                break;
            case 1:
                move(ppp,0,deltay);
                break;
            case 2:
                move(ppp,-deltax,0);
                break;
            case 3:
                move(ppp,0,-deltay);
                break;
            default:
                break;
        }
        spin1(argg);
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
    void paint(float* r,float* g,float* b){
        *r=(float)rand()/RAND_MAX;
        *g=(float)rand()/RAND_MAX;
        *b=(float)rand()/RAND_MAX;
    }
    void move1(point* ppp,double* argg,double* len,double* hei,point pt1,point pt2){//pt1 represent
        double static deltax=1,deltay=1;
        int flaggg=1;
        *len+=1;*len-=1;*hei+=1;*hei-=1;*argg+=1;*argg-=1;
        if(pt1.y<40){
            if(abs(centerpoint.x+10)<1&&centerpoint.y<30){flaggg=1;}
            else if(abs(centerpoint.y-30)<1&&centerpoint.x<pt1.x){flaggg=0;}
            else if(abs(centerpoint.x-pt1.x)<5&&centerpoint.y>=pt2.y){flaggg=3;}
            else{flaggg=5;}
        }else{
            if(abs(centerpoint.x+10)<1&&centerpoint.y<30){flaggg=1;}
            else if(abs(centerpoint.y-30)<1&&centerpoint.x<50){flaggg=0;}
            else if(abs(centerpoint.x-50)<1&&centerpoint.y<pt1.y){flaggg=1;}
            else if(abs(centerpoint.y-pt1.y)<5&&centerpoint.x>=pt1.x){flaggg=2;}
            else if(centerpoint.y<pt2.y){flaggg=1;}
            else{flaggg=5;}
        }

        switch (flaggg) {
            case 0:
                move(ppp,deltax,0);
                break;
            case 1:
                move(ppp,0,deltay);
                break;
            case 2:
                move(ppp,-deltax,0);
                break;
            case 3:
                move(ppp,0,-deltay);
                break;
            default:
                break;
        }
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
    void zoom1(double* h,double* l){
        int static flagg=0;
        if(*l>=14){flagg=1;}
        if(*l<=5){flagg=0;}
        if(flagg==0){zoom(l,h,1.01);}
        if(flagg==1){zoom(l,h,0.99);}
    }
    void move1(point* ppp,double* argg,double* len,double* hei,point pt1,point pt2){//pt1 represent
        double static deltax=1,deltay=1;
        int flaggg=1;

        if(pt1.y<40){
            if(abs(centerpoint.x+10)<1&&centerpoint.y<30){flaggg=1;}
            else if(abs(centerpoint.y-30)<1&&centerpoint.x<pt1.x){flaggg=0;}
            else if(abs(centerpoint.x-pt1.x)<5&&centerpoint.y>=pt2.y){flaggg=3;}
            else{flaggg=5;}
            if(abs(centerpoint.x+10)<1&&abs(centerpoint.y-30)<1){spin(argg,-PI/2);}
            if(abs(centerpoint.x-pt1.x)<5&&abs(centerpoint.y-pt1.y)<=5.0){spin(argg,PI/2);}
        }else{
            if(abs(centerpoint.x+10)<1&&centerpoint.y<30){flaggg=1;}
            else if(abs(centerpoint.y-30)<1&&centerpoint.x<50){flaggg=0;}
            else if(abs(centerpoint.x-50)<1&&centerpoint.y<pt1.y){flaggg=1;}
            else if(abs(centerpoint.y-pt1.y)<5&&centerpoint.x>=pt1.x){flaggg=2;}
            else if(centerpoint.y<pt2.y){flaggg=1;}
            else{flaggg=5;}
            if(centerpoint.x==-10&&centerpoint.y==30){spin(argg,-PI/2);}
            if(centerpoint.x==50&&centerpoint.y==30){spin(argg,PI/2);}
            if(centerpoint.x==50&&abs(centerpoint.y-pt1.y)<5){spin(argg,PI/2);}
            if(centerpoint.x==pt1.x&&centerpoint.y==pt1.y){spin(argg,PI/2);}
        }

        switch (flaggg) {
            case 0:
                move(ppp,deltax,0);
                break;
            case 1:
                move(ppp,0,deltay);
                break;
            case 2:
                move(ppp,-deltax,0);
                break;
            case 3:
                move(ppp,0,-deltay);
                break;
            default:
                zoom1(hei,len);
                break;
        }
    }
};
void draw_shape()
{
    //static Car a;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //a.draw();
    //a.move();
    glColor3f(0.0f,0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);        //直线起始坐标
    glVertex2f(60.0f, 0.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);        //直线起始坐标
    glVertex2f(60.0f, 0.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-15.0f, 80.0f);        //直线起始坐标
    glVertex2f(-15.0f, -5.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-15.0f, -5.0f);        //直线起始坐标
    glVertex2f(0.0f, -5.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -5.0f);        //直线起始坐标
    glVertex2f(0.0f, 20.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(10.0f, 0.0f);        //直线起始坐标
    glVertex2f(10.0f, 20.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(20.0f, 0.0f);        //直线起始坐标
    glVertex2f(20.0f, 20.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(30.0f, 0.0f);        //直线起始坐标
    glVertex2f(30.0f, 20.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(40.0f, 0.0f);        //直线起始坐标
    glVertex2f(40.0f, 20.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(50.0f, 0.0f);        //直线起始坐标
    glVertex2f(50.0f, 20.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(60.0f, 0.0f);        //直线起始坐标
    glVertex2f(60.0f, 80.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(60.0f, 80.0f);        //直线起始坐标
    glVertex2f(-15.0f, 80.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, 60.0f);        //直线起始坐标
    glVertex2f(0.0f, 80.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(10.0f, 60.0f);        //直线起始坐标
    glVertex2f(10.0f, 80.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(20.0f, 60.0f);        //直线起始坐标
    glVertex2f(20.0f, 80.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(30.0f, 60.0f);        //直线起始坐标
    glVertex2f(30.0f, 80.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(40.0f, 60.0f);        //直线起始坐标
    glVertex2f(40.0f, 80.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(50.0f, 60.0f);        //直线起始坐标
    glVertex2f(50.0f, 80.0f);         //直线结束坐标
    glEnd();

    glColor3f(100.0f,100.0f, 0.0f);

    glRectf(0.0f, 45.0f, 38.0f, 42.0f);

    glFlush();
}

void glDraw(){
    point static p00={-10,-10};
    point static p11={-10,-10};
    double static le=8;
    double static he=16;
    double static arggg=0;
    double static lee=8;
    double static hee=16;
    double static argggg=0;
    point pp1[13];
    point pp2[13];
    for(unsigned int i=1;i<=6;i++){pp1[i]={static_cast<double>(10*i-5),30};pp2[i]={static_cast<double>(10*i-5),10};}
    for(unsigned int i=7;i<=12;i++){pp1[i]={static_cast<double>(65-10*(i-6)),50};pp2[i]={static_cast<double>(65-10*(i-6)),70};}
    point ppt1,ppt2,ppt3,ppt4;
    ppt1={25,35};ppt2={25,10};
    ppt3={35,50};ppt4={35,71};
    // *For 1-6, point1 for move1 is {10*n-5,30} point2 is {10*n-5,10};
    // For 7-12 point 1 for move1 is {65-10*(n-6),50} point2 is {65-10*(n-6),70}
    Spacecraft aa(p00,le,he,arggg);
    Spacecraft bb(p11,lee,hee,argggg);
    //aa.zoom(&le,&he,k);
    aa.move1(&p00,&arggg,&le,&he,pp1[9],pp2[9]);
    //bb.move1(&p11,&argggg,&lee,&hee,ppt1,ppt2);
    if(aa.check(pp2[9],&p00)==1){bb.move1(&p11,&argggg,&lee,&hee,ppt1,ppt2);}
    //aa.spinn(&arggg);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_shape();
    aa.draw();
    //if(aa.check(pp2[9],&p00)==1){bb.move1(&p11,&argggg,&lee,&hee,ppt1,ppt2);bb.draw();}
    if(aa.check(pp2[9],&p00)){bb.draw();}
    glutSwapBuffers(); glFlush();
}

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    // glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Home sweet home");
    gluOrtho2D(-20, 70, -30, 85);
    glClearColor(1.0, 1.0, 1.0, 0.0); glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw); glutTimerFunc(25, TimeStep, 25);
    glutMainLoop();
    return 0;
}
