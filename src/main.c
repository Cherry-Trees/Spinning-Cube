#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "functions.h"
#include "Mat44.h"
#include "Vec3.h"

int main() {

    struct Mat44 PROJECTION_MATRIX;
    
    PROJECTION_MATRIX.m[0][0] = ((FOCAL_LENGTH) * X_SCALE) / (ASPECT_RATIO);    
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

    
    char screen[H * W];
    struct Vec3 camera = {0.f, 0.f, 0.f};
    struct Vec3 light = {0.f, -4.f, -1.f};
    const char GRADIENT[91] = "`.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
    const int N_GRADIENT_VALUES = sizeof(GRADIENT) / sizeof(char);

    struct Vec3 l1, l2;
    struct Vec3 surfaceNormals[N_TRIS], lsToCamera[N_TRIS];
    float values[N_TRIS];
    int value_indices[N_TRIS];

    
    printf("\x1b[H");
    printf("\x1b[2J");
    for (int n = 0; n < FRAMES; n++)
    {
        const float t = n * 0.1f;

        // Triangle primitive collection
        // Example cube: 12 triangles, 3 vectors each
        struct Vec3 triCollection[N_TRIS][3];

        // SOUTH
        triCollection[0][0].x = -0.5f;  triCollection[0][0].y = -0.5f;  triCollection[0][0].z = -0.5f;
        triCollection[0][1].x = -0.5f;  triCollection[0][1].y = 0.5f;   triCollection[0][1].z = -0.5f;
        triCollection[0][2].x = 0.5f;   triCollection[0][2].y = 0.5f;   triCollection[0][2].z = -0.5f;

        triCollection[1][0].x = -0.5f;  triCollection[1][0].y = -0.5f;  triCollection[1][0].z = -0.5f;
        triCollection[1][1].x = 0.5f;   triCollection[1][1].y = 0.5f;   triCollection[1][1].z = -0.5f;
        triCollection[1][2].x = 0.5f;   triCollection[1][2].y = -0.5f;  triCollection[1][2].z = -0.5f;

        // EAST
        triCollection[2][0].x = 0.5f;   triCollection[2][0].y = -0.5f;  triCollection[2][0].z = -0.5f;
        triCollection[2][1].x = 0.5f;   triCollection[2][1].y = 0.5f;   triCollection[2][1].z = -0.5f;
        triCollection[2][2].x = 0.5f;   triCollection[2][2].y = 0.5f;   triCollection[2][2].z = 0.5f;
        
        triCollection[3][0].x = 0.5f;   triCollection[3][0].y = -0.5f;  triCollection[3][0].z = -0.5f;
        triCollection[3][1].x = 0.5f;   triCollection[3][1].y = 0.5f;   triCollection[3][1].z = 0.5f;
        triCollection[3][2].x = 0.5f;   triCollection[3][2].y = -0.5f;  triCollection[3][2].z = 0.5f;

        // NORTH
        triCollection[4][0].x = 0.5f;   triCollection[4][0].y = -0.5f;  triCollection[4][0].z = 0.5f;
        triCollection[4][1].x = 0.5f;   triCollection[4][1].y = 0.5f;   triCollection[4][1].z = 0.5f;
        triCollection[4][2].x = -0.5f;  triCollection[4][2].y = 0.5f;   triCollection[4][2].z = 0.5f;

        triCollection[5][0].x = 0.5f;   triCollection[5][0].y = -0.5f;  triCollection[5][0].z = 0.5f;
        triCollection[5][1].x = -0.5f;  triCollection[5][1].y = 0.5f;   triCollection[5][1].z = 0.5f;
        triCollection[5][2].x = -0.5f;  triCollection[5][2].y = -0.5f;  triCollection[5][2].z = 0.5f;

        // WEST   
        triCollection[6][0].x = -0.5f;  triCollection[6][0].y = -0.5f;  triCollection[6][0].z = 0.5f;
        triCollection[6][1].x = -0.5f;  triCollection[6][1].y = 0.5f;   triCollection[6][1].z = 0.5f;
        triCollection[6][2].x = -0.5f;  triCollection[6][2].y = 0.5f;   triCollection[6][2].z = -0.5f;

        triCollection[7][0].x = -0.5f;  triCollection[7][0].y = -0.5f;  triCollection[7][0].z = 0.5f;
        triCollection[7][1].x = -0.5f;  triCollection[7][1].y = 0.5f;   triCollection[7][1].z = -0.5f;
        triCollection[7][2].x = -0.5f;  triCollection[7][2].y = -0.5f;  triCollection[7][2].z = -0.5f;

        // TOP
        triCollection[8][0].x = -0.5f;  triCollection[8][0].y = 0.5f;   triCollection[8][0].z = -0.5f;
        triCollection[8][1].x = -0.5f;  triCollection[8][1].y = 0.5f;   triCollection[8][1].z = 0.5f;
        triCollection[8][2].x = 0.5f;   triCollection[8][2].y = 0.5f;   triCollection[8][2].z = 0.5f;
        
        triCollection[9][0].x = -0.5f;  triCollection[9][0].y = 0.5f;   triCollection[9][0].z = -0.5f;
        triCollection[9][1].x = 0.5f;   triCollection[9][1].y = 0.5f;   triCollection[9][1].z = 0.5f;
        triCollection[9][2].x = 0.5f;   triCollection[9][2].y = 0.5f;   triCollection[9][2].z = -0.5f;
        
        // BOTTOM
        triCollection[10][0].x = 0.5f;  triCollection[10][0].y = -0.5f; triCollection[10][0].z = 0.5f;
        triCollection[10][1].x = -0.5f; triCollection[10][1].y = -0.5f; triCollection[10][1].z = 0.5f;
        triCollection[10][2].x = -0.5f; triCollection[10][2].y = -0.5f; triCollection[10][2].z = -0.5f;

        triCollection[11][0].x = 0.5f;  triCollection[11][0].y = -0.5f; triCollection[11][0].z = 0.5f;
        triCollection[11][1].x = -0.5f; triCollection[11][1].y = -0.5f; triCollection[11][1].z = -0.5f;
        triCollection[11][2].x = 0.5f;  triCollection[11][2].y = -0.5f; triCollection[11][2].z = -0.5f;
        
        
        for (int tri = 0; tri < N_TRIS; tri++)
        {
            // // SPIN
            triCollection[tri][0] = rotateX(triCollection[tri][0], t / 3.1f);
            triCollection[tri][1] = rotateX(triCollection[tri][1], t / 3.1f);
            triCollection[tri][2] = rotateX(triCollection[tri][2], t / 3.1f);

            triCollection[tri][0] = rotateY(triCollection[tri][0], t / 1.f);
            triCollection[tri][1] = rotateY(triCollection[tri][1], t / 1.f);
            triCollection[tri][2] = rotateY(triCollection[tri][2], t / 1.f);

            triCollection[tri][0] = rotateZ(triCollection[tri][0], t / 2.2f);
            triCollection[tri][1] = rotateZ(triCollection[tri][1], t / 2.2f);
            triCollection[tri][2] = rotateZ(triCollection[tri][2], t / 2.2f);

            // TRANSLATE Z
            triCollection[tri][0].z += DISTANCE_FROM_CAMERA;
            triCollection[tri][1].z += DISTANCE_FROM_CAMERA;
            triCollection[tri][2].z += DISTANCE_FROM_CAMERA;

            triCollection[tri][0].z += cosf(t / 3.3f) / 2.5f;
            triCollection[tri][1].z += cosf(t / 3.3f) / 2.5f;
            triCollection[tri][2].z += cosf(t / 3.3f) / 2.5f;

            // RENDER
            l1.x = triCollection[tri][1].x - triCollection[tri][0].x;
            l1.y = triCollection[tri][1].y - triCollection[tri][0].y;
            l1.z = triCollection[tri][1].z - triCollection[tri][0].z;

            l2.x = triCollection[tri][2].x - triCollection[tri][1].x;
            l2.y = triCollection[tri][2].y - triCollection[tri][1].y;
            l2.z = triCollection[tri][2].z - triCollection[tri][1].z;

            surfaceNormals[tri] = unit(cross(l1, l2));
            lsToCamera[tri].x = triCollection[tri][0].x - camera.x;
            lsToCamera[tri].y = triCollection[tri][0].y - camera.y;
            lsToCamera[tri].z = triCollection[tri][0].z - camera.z;

            values[tri] = dot(surfaceNormals[tri], light);
            value_indices[tri] = max(min(roundf(values[tri] * N_GRADIENT_VALUES * VALUE_INTENSITY), N_GRADIENT_VALUES - 1), 0);

            // PROJECT
            triCollection[tri][0] = vec3_x_mat44(triCollection[tri][0], PROJECTION_MATRIX);
            triCollection[tri][1] = vec3_x_mat44(triCollection[tri][1], PROJECTION_MATRIX);
            triCollection[tri][2] = vec3_x_mat44(triCollection[tri][2], PROJECTION_MATRIX);

            // CENTER
            triCollection[tri][0].x += INIT_TRANSLATION; 
            triCollection[tri][0].y += INIT_TRANSLATION;
            triCollection[tri][1].x += INIT_TRANSLATION; 
            triCollection[tri][1].y += INIT_TRANSLATION;
            triCollection[tri][2].x += INIT_TRANSLATION; 
            triCollection[tri][2].y += INIT_TRANSLATION;

            // REVOLVE
            triCollection[tri][0].x += sinf(t / 3.3f) / 2.5f;
            triCollection[tri][1].x += sinf(t / 3.3f) / 2.5f;
            triCollection[tri][2].x += sinf(t / 3.3f) / 2.5f;

            // SCALE
            triCollection[tri][0].x *= 0.5f * W; 
            triCollection[tri][0].y *= 0.5f * H;     
            triCollection[tri][1].x *= 0.5f * W; 
            triCollection[tri][1].y *= 0.5f * H; 
            triCollection[tri][2].x *= 0.5f * W; 
            triCollection[tri][2].y *= 0.5f * H;  
        }

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {

                unsigned char hit = 0;
                int value_key = 0;

                for (int tri = 0; tri < N_TRIS; tri++) {

                    if (dot(surfaceNormals[tri], lsToCamera[tri]) < 0.f && 
                        triCollection[tri][0].z > 0.f &&
                        triCollection[tri][1].z > 0.f && 
                        triCollection[tri][2].z > 0.f) {

                            unsigned char switch_gate = 0;
                            for (unsigned char side = 0; side < 3; side++) {
                                
                                signed char flip;
                                const float slope = (float)(triCollection[tri][(side + 1) % 3].y - triCollection[tri][side].y) / 
                                                (float)(triCollection[tri][(side + 1) % 3].x - triCollection[tri][side].x);

                                // y(j)
                                if (fabs(slope) <= 1) {
                                    flip = (triCollection[tri][(side + 1) % 3].x < triCollection[tri][side].x) ? -1 : 1;
                                    const int y = (int)(slope * (j - triCollection[tri][side].x) + triCollection[tri][side].y);

                                    const int x_min = (int)min(triCollection[tri][side].x, triCollection[tri][(side + 1) % 3].x);
                                    const int x_max = (int)max(triCollection[tri][side].x, triCollection[tri][(side + 1) % 3].x);

                                    // Fill
                                    if (flip * i < flip * y) {switch_gate++;}

                                    // Draw wireframe
                                    if (i == y && j >= x_min && j <= x_max) {
                                        hit = 1;
                                        value_key = value_indices[tri];
                                    }
                                }

                                // x(i)
                                else {
                                    flip = (triCollection[tri][(side + 1) % 3].y < triCollection[tri][side].y) ? -1 : 1;
                                    const int x = (int)((i - triCollection[tri][side].y) / slope + triCollection[tri][side].x);

                                    const int y_min = (int)min(triCollection[tri][side].y, triCollection[tri][(side + 1) % 3].y);
                                    const int y_max = (int)max(triCollection[tri][side].y, triCollection[tri][(side + 1) % 3].y);

                                    // Fill
                                    if (flip * j > flip * x) {switch_gate++;}

                                    // Draw wireframe
                                    if (j == x && i >= y_min && i <= y_max) {
                                        hit = 1;
                                        value_key = value_indices[tri];
                                    }
                                }
                            }

                            if (switch_gate == 3) {
                                hit = 1;
                                value_key = value_indices[tri];
                            }
                        }       
                }

                if (hit) {putchar(GRADIENT[value_key]);} 
                else {putchar(' ');}
            }
            putchar('\n');
        }
        printf("\x1b[H");
    }
    
    return 0;
}
