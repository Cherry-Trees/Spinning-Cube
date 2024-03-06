#pragma once
#include "globals.h"
#include "Vec3.h"
#include "Mat44.h"

struct Vec3 vec3_x_mat44(struct Vec3 v, struct Mat44 m) 
{
    struct Vec3 out;
    out.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
    out.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
    out.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
    float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f)
    {
        out.x /= w;
        out.y /= w;
        out.z /= w;
    }

    return out;
}

struct Vec3 rotateX(struct Vec3 v, float delta)
{
    struct Mat44 Rx;
    Rx.m[0][0] = 1.f;             Rx.m[0][1] = 0.f;             Rx.m[0][2] = 0.f;             Rx.m[0][3] = 0.f;
    Rx.m[1][0] = 0.f;             Rx.m[1][1] = cosf(delta);     Rx.m[1][2] = sinf(delta);     Rx.m[1][3] = 0.f;
    Rx.m[2][0] = 0.f;             Rx.m[2][1] = -sinf(delta);    Rx.m[2][2] = cosf(delta);     Rx.m[2][3] = 0.f;
    Rx.m[3][0] = 0.f;             Rx.m[3][1] = 0.f;             Rx.m[3][2] = 0.f;             Rx.m[3][3] = 1.f;

    return vec3_x_mat44(v, Rx);
}

struct Vec3 rotateY(struct Vec3 v, float delta)
{
    struct Mat44 Ry;
    Ry.m[0][0] = cosf(delta);     Ry.m[0][1] = 0.f;             Ry.m[0][2] = -sinf(delta);    Ry.m[0][3] = 0.f;
    Ry.m[1][0] = 0.f;             Ry.m[1][1] = 1.f;             Ry.m[1][2] = 0.f;             Ry.m[1][3] = 0.f;
    Ry.m[2][0] = sinf(delta);     Ry.m[2][1] = 0.f;             Ry.m[2][2] = cosf(delta);     Ry.m[2][3] = 0.f;         
    Ry.m[3][0] = 0.f;             Ry.m[3][1] = 0.f;             Ry.m[3][2] = 0.f;             Ry.m[3][3] = 1.f;
    
    return vec3_x_mat44(v, Ry);
}

struct Vec3 rotateZ(struct Vec3 v, float delta)
{
    struct Mat44 Rz;
    Rz.m[0][0] = cosf(delta);     Rz.m[0][1] = -sinf(delta);    Rz.m[0][2] = 0.f;             Rz.m[0][3] = 0.f;
    Rz.m[1][0] = sinf(delta);     Rz.m[1][1] = cosf(delta);     Rz.m[1][2] = 0.f;             Rz.m[1][3] = 0.f;
    Rz.m[2][0] = 0.f;             Rz.m[2][1] = 0.f;             Rz.m[2][2] = 1.f;             Rz.m[2][3] = 0.f;         
    Rz.m[3][0] = 0.f;             Rz.m[3][1] = 0.f;             Rz.m[3][2] = 0.f;             Rz.m[3][3] = 1.f;
    
    return vec3_x_mat44(v, Rz);
}

// f(x)
float f(const int x, const struct Vec3 v1, const struct Vec3 v2) {
    const float m = (float)(v2.y - v1.y) / (float)(v2.x - v1.x);
    return (m * (x - v1.x)) + v1.y;
}

// g(y)
float g(const int y, const struct Vec3 v1, const struct Vec3 v2) {
    const float m = (float)(v2.y - v1.y) / (float)(v2.x - v1.x);
    return ((float)(y - v1.y) / m) + v1.x;
}

float max(const float a, const float b) {if (a > b) {return a;} else {return b;}}
float min(const float a, const float b) {if (a < b) {return a;} else {return b;}}

float norm(const struct Vec3 v) {return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);}
struct Vec3 unit(struct Vec3 v) {
    const float norm_v = norm(v);
    v.x /= norm_v;
    v.y /= norm_v;
    v.z /= norm_v;
    return v;
}

float dot(const struct Vec3 v1, const struct Vec3 v2) {return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}
struct Vec3 cross(const struct Vec3 v1, const struct Vec3 v2) {
    struct Vec3 cross_v1v2 = {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    }; return cross_v1v2;
}
