//
// Created by alexc on 2020/12/4.
//
#ifndef PROJECT_3_FIGURE_H
#define PROJECT_3_FIGURE_H
#include "vector.h"


class Figure {
protected:
     Vec anchor;
     public:
     Figure() : anchor(0, 0) {}
     Vec getAnchor() {return anchor;}
     void setAnchor(Vec a) {anchor = a;}
     virtual void draw() = 0;
     virtual void move(Vec dir) = 0;
     virtual void rotate(float angle) = 0;
     virtual void zoom(float k) = 0;
     virtual ~Figure() {}
     };

 class Group : Figure {
     protected:
     Vec anchor;
     float r, g, b;
     public:
    Group() : anchor(0, 0) {}
    Vec getAnchor() {return anchor;}
    void setAnchor(Vec a) {anchor = a;}
    virtual void draw(); // Draw out all its figures
    virtual void move(Vec dir); // Move all its figures
    virtual void rotate(float angle); // Rotate the group as a whole.
    virtual void zoom(float k); // Zoom the group as a whole.
     virtual ~Group() {}
     };

class Teleported : public Group {
private:
    Vec anchor;
public:
    Teleported(Vec anchor, float r = 0, float g = 0, float b = 0);

    void draw();

    void move(Vec dir);

    void rotate(float angle);

    void zoom(float k);
};

class  UFO: public Group {
private:
    Vec anchor;
public:
    UFO(Vec anchor, float r = 0, float g = 0, float b = 0);

    void draw();

    void move(Vec dir);

    void rotate(float angle);

    void zoom(float k);

};

class  Spacecraft: public Group {
private:
    Vec anchor;
public:
    Spacecraft(Vec anchor, float r = 0, float g = 0, float b = 0);

    void draw();

    void move(Vec dir);

    void rotate(float angle);

    void zoom(float k);

};

class  Car: public Group {
private:
    Vec anchor;
public:
    Car(Vec anchor, float r = 0, float g = 0, float b = 0);

    void draw();

    void move(Vec dir);

    void rotate(float angle);

    void zoom(float k);

};

#endif //PROJECT_3_FIGURE_H
