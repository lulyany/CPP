//
// Created by alexc on 2020/12/4.
//

#ifndef PROJECT_3_VECTOR_H
#define PROJECT_3_VECTOR_H
#include <cmath>
class Vec {
private:
    float x, y;
public:
    Vec(float _x, float _y) {
        x = _x;
        y = _y;
    }

    float getX() const { return x; }

    float getY() const { return y; }


    Vec operator+(Vec v) {
        return {x + v.getX(), y + v.getY()};
    }

    Vec operator*(float k){
        return {x*k, y*k};
    }
    Vec operator-(Vec v) {
        return {x - v.getX(), y - v.getY()};
    }
    Vec operator>>(float angle) {
        return { x=sin(angle)*y+cos(angle)*x,y=cos(angle)*y-sin(angle)*x};
    }
    Vec operator<<(float angle) {
        return { x=cos(angle)*x-sin(angle)*y,y=cos(angle)*y+sin(angle)*x};
    }
};
#endif //PROJECT_3_VECTOR_H
