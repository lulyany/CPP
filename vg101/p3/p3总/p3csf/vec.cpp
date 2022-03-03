#include <cmath>
#include <iostream>
#include "cars.h"
#include "Figures.h"
#include "vec.h"

Vec::Vec(float x1, float y1) {
    x = x1; 
    y = y1;
}

float Vec::getX() {
    return x;
}
float Vec::getY() {
    return y;
}

Vec Vec::operator+ (Vec v) {
    return Vec(x + v.getX(), y + v.getY());
}
Vec Vec::operator- (Vec v) {
    return Vec(x - v.getX(), y - v.getY());
}
Vec Vec::operator* (float k) {
    return Vec(x *k, y*k);
}
float Vec::operator* (Vec v) {
    return x*v.getX()+y*v.getY();
}
Vec Vec::operator>> (float degree) {
    return Vec((float)(x*cos(degree)+y*sin(degree)),(float)(-x*sin(degree)+y*cos(degree)));
}
Vec Vec::operator<< (float degree) {
    degree*=-1;
    return Vec((float)(x*cos(degree)+y*sin(degree)),(float)(-x*sin(degree)+y*cos(degree)));
}


void Vec::Print() {
    using namespace std;
    cout << "Vector:("<< x << "," << y << ")"<< endl;
}

Group::Group(Point pt1,double width,double height,double d) {
    p=pt1;
    w=width;
    h=height;
    degree=d;
    parking=new Park;
}

Group::~Group() {
    delete van;delete parking;
}

void Group::draw() {
    van->draw();
    parking->draw();
}

void Group::move(Vec dir) {
    using namespace std;
    setAnchor(dir);
    Vec help=getAnchor();
    p.x+=(double)help.getX();
    p.y+=(double)help.getY();
    van=new Car(p,p,w,h,degree);
}

void Group::zoom(float k) {
    w*=(double)k;h*=(double)k;
    van=new Car(p,p,w,h,degree);
}

void Group::rotate(float angle) {
    degree+=angle;
    van=new Car(p,p,w,h,degree);
}