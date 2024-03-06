#include <stdio.h>

#include "globals.h"
#include "functions.h"
#include "Mat44.h"
#include "Vec3.h"

char screen[H * W];

int main() {

    struct Mat44 PROJECTION_MATRIX;
    
    PROJECTION_MATRIX.m[0][0] = ASPECT_RATIO * FOCAL_LENGTH;    
    PROJECTION_MATRIX.m[0][1] = 0.f;            
    PROJECTION_MATRIX.m[0][2] = 0.f;            
    PROJECTION_MATRIX.m[0][3] = 0.f;    

    PROJECTION_MATRIX.m[1][0] = 0.f;    
    PROJECTION_MATRIX.m[1][1] = FOCAL_LENGTH;            
    PROJECTION_MATRIX.m[1][2] = 0.f;            
    PROJECTION_MATRIX.m[1][3] = 0.f;   

    PROJECTION_MATRIX.m[2][0] = 0.f;    
    PROJECTION_MATRIX.m[2][1] = 0.f;            
    PROJECTION_MATRIX.m[2][2] = Z_FAR / (Z_FAR - Z_NEAR);            
    PROJECTION_MATRIX.m[2][3] = 1.f;   

    PROJECTION_MATRIX.m[3][0] = 0.f;    
    PROJECTION_MATRIX.m[3][1] = 0.f;            
    PROJECTION_MATRIX.m[3][2] = (-Z_FAR * Z_NEAR) / (Z_FAR - Z_NEAR);            
    PROJECTION_MATRIX.m[3][3] = 0.f;  

    printf("\x1b[H");
    printf("\x1b[2J");
    for (int n = 0; n < 150; n++)
    {
        // Bottom
        struct Vec3 v1 = {-0.5f, -0.5f, -0.5f};
        struct Vec3 v2 = {0.5f, -0.5f, -0.5f};
        struct Vec3 v3 = {0.5f, -0.5f, 0.5f};
        struct Vec3 v4 = {-0.5f, -0.5f, 0.5f};

        // Top
        struct Vec3 v5 = {-0.5f, 0.5f, -0.5f};
        struct Vec3 v6 = {0.5f, 0.5f, -0.5f};
        struct Vec3 v7 = {-0.5f, 0.5f, 0.5f};
        struct Vec3 v8 = {0.5f, 0.5f, 0.5f};

        float t = n * 0.15f;
        v1 = rotateX(v1, t);
        v2 = rotateX(v2, t);
        v3 = rotateX(v3, t);
        v4 = rotateX(v4, t);
        v5 = rotateX(v5, t);
        v6 = rotateX(v6, t);
        v7 = rotateX(v7, t);
        v8 = rotateX(v8, t);

        v1 = rotateY(v1, t / 2.5f);
        v2 = rotateY(v2, t / 2.5f);
        v3 = rotateY(v3, t / 2.5f);
        v4 = rotateY(v4, t / 2.5f);
        v5 = rotateY(v5, t / 2.5f);
        v6 = rotateY(v6, t / 2.5f);
        v7 = rotateY(v7, t / 2.5f);
        v8 = rotateY(v8, t / 2.5f);

        v1 = rotateZ(v1, t / 2.f);
        v2 = rotateZ(v2, t / 2.f);
        v3 = rotateZ(v3, t / 2.f);
        v4 = rotateZ(v4, t / 2.f);
        v5 = rotateZ(v5, t / 2.f);
        v6 = rotateZ(v6, t / 2.f);
        v7 = rotateZ(v7, t / 2.f);
        v8 = rotateZ(v8, t / 2.f);

        v1.z += DISTANCE_FROM_CAMERA;
        v2.z += DISTANCE_FROM_CAMERA;
        v3.z += DISTANCE_FROM_CAMERA;
        v4.z += DISTANCE_FROM_CAMERA;
        v5.z += DISTANCE_FROM_CAMERA;
        v6.z += DISTANCE_FROM_CAMERA;
        v7.z += DISTANCE_FROM_CAMERA;
        v8.z += DISTANCE_FROM_CAMERA;

        struct Vec3 v1Proj = vec3_x_mat44(v1, PROJECTION_MATRIX);
        struct Vec3 v2Proj = vec3_x_mat44(v2, PROJECTION_MATRIX);
        struct Vec3 v3Proj = vec3_x_mat44(v3, PROJECTION_MATRIX);
        struct Vec3 v4Proj = vec3_x_mat44(v4, PROJECTION_MATRIX);
        struct Vec3 v5Proj = vec3_x_mat44(v5, PROJECTION_MATRIX);
        struct Vec3 v6Proj = vec3_x_mat44(v6, PROJECTION_MATRIX);
        struct Vec3 v7Proj = vec3_x_mat44(v7, PROJECTION_MATRIX);
        struct Vec3 v8Proj = vec3_x_mat44(v8, PROJECTION_MATRIX);

        v1Proj.x += INIT_TRANSLATION;
        v1Proj.y += INIT_TRANSLATION;
        v2Proj.x += INIT_TRANSLATION;
        v2Proj.y += INIT_TRANSLATION;
        v3Proj.x += INIT_TRANSLATION;
        v3Proj.y += INIT_TRANSLATION;
        v4Proj.x += INIT_TRANSLATION;
        v4Proj.y += INIT_TRANSLATION;
        v5Proj.x += INIT_TRANSLATION;
        v5Proj.y += INIT_TRANSLATION;
        v6Proj.x += INIT_TRANSLATION;
        v6Proj.y += INIT_TRANSLATION;
        v7Proj.x += INIT_TRANSLATION;
        v7Proj.y += INIT_TRANSLATION;
        v8Proj.x += INIT_TRANSLATION;
        v8Proj.y += INIT_TRANSLATION;

        v1Proj.x *= 0.5f * W;
        v1Proj.y *= 0.5f * H;
        v2Proj.x *= 0.5f * W;
        v2Proj.y *= 0.5f * H;
        v3Proj.x *= 0.5f * W;
        v3Proj.y *= 0.5f * H;
        v4Proj.x *= 0.5f * W;
        v4Proj.y *= 0.5f * H;
        v5Proj.x *= 0.5f * W;
        v5Proj.y *= 0.5f * H;
        v6Proj.x *= 0.5f * W;
        v6Proj.y *= 0.5f * H;
        v7Proj.x *= 0.5f * W;
        v7Proj.y *= 0.5f * H;
        v8Proj.x *= 0.5f * W;
        v8Proj.y *= 0.5f * H;
        
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                unsigned short projected_char_index = 0;

                if (
                    (i == (int)v1Proj.y && j == (int)v1Proj.x) ||
                    (i == (int)v2Proj.y && j == (int)v2Proj.x) ||
                    (i == (int)v3Proj.y && j == (int)v3Proj.x) ||
                    (i == (int)v4Proj.y && j == (int)v4Proj.x) ||
                    (i == (int)v5Proj.y && j == (int)v5Proj.x) ||
                    (i == (int)v6Proj.y && j == (int)v6Proj.x) ||
                    (i == (int)v7Proj.y && j == (int)v7Proj.x) ||
                    (i == (int)v8Proj.y && j == (int)v8Proj.x)
                ) {projected_char_index = 5;}
                    // screen[i * W + j] = '#';}
                

            //     if (
            //         (i == (int)v1Proj.y) ||
            //         (i == (int)v2Proj.y) ||
            //         (i == (int)v3Proj.y) ||
            //         (i == (int)v4Proj.y) ||
            //         (i == (int)v5Proj.y) ||
            //         (i == (int)v6Proj.y) ||
            //         (i == (int)v7Proj.y) ||
            //         (i == (int)v8Proj.y)
            //     ) {
            //         isDrawing = 1;
            //         if (
            //         (i == (int)v1Proj.y && j == (int)v1Proj.x) ||
            //         (i == (int)v2Proj.y && j == (int)v2Proj.x) ||
            //         (i == (int)v3Proj.y && j == (int)v3Proj.x) ||
            //         (i == (int)v4Proj.y && j == (int)v4Proj.x) ||
            //         (i == (int)v5Proj.y && j == (int)v5Proj.x) ||
            //         (i == (int)v6Proj.y && j == (int)v6Proj.x) ||
            //         (i == (int)v7Proj.y && j == (int)v7Proj.x) ||
            //         (i == (int)v8Proj.y && j == (int)v8Proj.x)
            //         ) {
            //             putchar('#');
            //         }

            //         else {putchar(' ');}

            //         if (j == W - 1) {putchar('\n');}
            //     }
            //     else {isDrawing = 0;}//putchar('\n');}

            //     // else if (j != W-1) {screen[i * W + j] = ' ';}
            //     // else {screen[i * W + j] = '\n';}
                putchar(PROJECTED_CHAR[projected_char_index]);
            // }
            // if (!isDrawing) {putchar('\n');}
                // putchar(' '); putchar(' '); putchar(' ');
                // putchar('\n');}
            // putchar('\n');
            }
            putchar('\n');
        }
        printf("\x1b[H");
    }



    return 0;
}