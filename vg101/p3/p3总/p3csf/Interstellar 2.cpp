#include <GL/glut.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "Figures.h"
#include "cars.h"
#include "vec.h"
#include "Space.h"
#define PI acos(-1)
using namespace std;

void TimeStep(int n) {
    glutTimerFunc((unsigned)n, TimeStep, n);
    glutPostRedisplay();
}

void glDraw1() {
    int static initial[12]={5};double temp1;int i,flag_space=0;
    srand((unsigned int)time(nullptr));
    if(initial[0]==5){
        for(i=0;i<11;i++){
            temp1=(rand()+0.0)/RAND_MAX;
            if(temp1>0.6){
                initial[i]=rand()%4+1;
            }
            else initial[i]=0;
        }
        initial[11]=0;
    }
    Point static point={-.8,-1.0};
    double static width=0.25,height=0.05,angle=PI/2,u_angle=0.0,ship_w=0.05,ship_h=0.1;
    int static count=0;
    Group all(point,width,height,angle);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(i=0;i<6;i++){
        if(initial[i]>0){
            switch(initial[i]){
                case 1: {
                    Car tmp({-0.375+0.25*i,-0.875},{-0.375+0.25*i,-0.875},0.25,0.05,0.0);
                    tmp.draw();break;
                }
                case 2:{Teleporter tmp({-0.375+0.25*i,-0.875},0.25,0.2);tmp.draw();break;}
                case 3:{UFO tmp({-0.375+0.25*i,-0.875},0.2,u_angle);tmp.draw();break;}
                default:{
                    Spacecraft tmp({-0.375+0.25*i,-0.875},ship_w,ship_h);tmp.draw();
                    if(flag_space==0){tmp.zoom(&ship_w,&ship_h);flag_space++;}break;
                }
            }
        }
    }
    for(i=0;i<5;i++){
        if(initial[i+6]>0){
            switch(initial[i+6]){
                case 1: {
                    Car tmp({-0.375+0.25*i,0.875},{-0.375+0.25*i,0.875},0.25,0.05,0.0);
                    tmp.draw();break;
                }
                case 2:{Teleporter tmp({-0.375+0.25*i,0.875},0.25,0.2);tmp.draw();break;}
                case 3:{UFO tmp({-0.375+0.25*i,0.875},0.2,u_angle);tmp.draw();break;}
                default:{
                    Spacecraft tmp({-0.375+0.25*i,0.875},ship_w,ship_h);tmp.draw();
                    if(flag_space==0){tmp.zoom(&ship_w,&ship_h);flag_space++;}break;
                }
            }
        }
    }
    u_angle+=PI/360;
    int static target=0;int temp_count1=1,temp_count2,temp_count3=1;
    if(target==0){
        for(i=0;i<11;i++){if(initial[i]==0)temp_count1++;}
        temp_count2=rand()%temp_count1+1;
        for(i=0;i<12;i++){
            if(initial[i]==0){
                if(temp_count3==temp_count2){target=i+1;}
                temp_count3++;
            }
        }
    }
    if (count<=37){
        Vec v1(0,(float)0.01);
        all.move(v1);all.draw();
        point.x+=v1.getX();point.y+=v1.getY();
    }
    else if (count>37&&count<=127) {
        Vec v2((float)(point.x+0.55),(float)(point.y+0.63));
        v2=(v2>>(float)PI/180)-v2;all.move(v2);point.x+=v2.getX();point.y+=v2.getY();
        all.rotate((float)(-PI/180));all.draw();angle-=PI/180;
    }
    else {
        Vec v0(0.0,0.0);
        all.move(v0);all.draw();
        point.x+=v0.getX();point.y+=v0.getY();
    }
    if(target<6){
        if(count>127&&count<=145+target*25){
            Vec v3((float)0.01,0);
            all.move(v3);all.draw();
            point.x+=v3.getX();point.y+=v3.getY();
        }
        else if(count>145+target*25&&count<=235+target*25){
            Vec v4((float)(point.x+0.37-target*0.25),(float)(point.y+0.63));
            v4=(v4<<(float)PI/180)-v4;all.move(v4);point.x+=v4.getX();point.y+=v4.getY();
            all.rotate((float)(PI/180));all.draw();angle+=PI/180;
        }
        else if(count>235+target*25&&count<=260+target*25){
            Vec v5(0,(float)-0.01);
            all.move(v5);all.draw();
            point.x+=v5.getX();point.y+=v5.getY();
        }
    }
    else{
        if(count>127&&count<=244){
            Vec v3((float)0.01,0);
            all.move(v3);all.draw();
            point.x+=v3.getX();point.y+=v3.getY();
        }
        else if(count>244&&count<=334){
            Vec v4((float)(point.x-0.62),(float)(point.y+0.13));
            v4=(v4<<(float)PI/180)-v4;all.move(v4);point.x+=v4.getX();point.y+=v4.getY();
            all.rotate((float)(PI/180));all.draw();angle+=PI/180;
        }
        if(target==6){
            if(count>334&&count<=409){
                Vec v5(0,(float)-0.01);
                all.move(v5);all.draw();
                point.x+=v5.getX();point.y+=v5.getY();
            }
        }
        else{
            if(count>334&&count<=360){
                Vec v1(0,(float)0.01);
                all.move(v1);all.draw();
                point.x+=v1.getX();point.y+=v1.getY();
            }
            else if(count>360&&count<=450){
                Vec v4((float)(point.x-0.62),(float)(point.y-0.13));
                v4=(v4<<(float)PI/180)-v4;all.move(v4);point.x+=v4.getX();point.y+=v4.getY();
                all.rotate((float)(PI/180));all.draw();angle+=PI/180;
            }
            else if(count>450&&count<=450+25*(12-target)){
                Vec v3((float)-0.01,0);
                all.move(v3);all.draw();
                point.x+=v3.getX();point.y+=v3.getY();
            }
            else if(count>450+25*(12-target)&&count<=540+25*(12-target)){
                Vec v4((float)(point.x-0.62+0.25*(12-target)),(float)(point.y-0.63));
                v4=(v4<<(float)PI/180)-v4;all.move(v4);point.x+=v4.getX();point.y+=v4.getY();
                all.rotate((float)(PI/180));all.draw();angle+=PI/180;
            }
            else if(count>540+25*(12-target)&&count<=565+25*(12-target)){
                Vec v1(0,(float)0.01);
                all.move(v1);all.draw();
                point.x+=v1.getX();point.y+=v1.getY();
            }
        }
    }
    count++;
    glutSwapBuffers(); glFlush();
}

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(700,700);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Interstellar Parking Lot!");
    glClearColor(1.0, 1.0, 1.0, 0.0); glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw1); glutTimerFunc(25, TimeStep, 25);
    glutDisplayFunc(glDraw1);
    glutMainLoop();
}
