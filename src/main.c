#include <stdio.h>

#include "globals.h"
#include "functions.h"
#include "Mat44.h"
#include "Vec3.h"

int main() {

    struct Mat44 PROJECTION_MATRIX;
    
    PROJECTION_MATRIX.m[0][0] = ASPECT_RATIO * FOCAL_LENGTH * X_SCALE;    
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
    struct Vec3 light = {0.f, 0.f, -1.f};
    const char GRADIENT[6] = {' ', '.', '~', '+', '$', '#'};
    const int N_GRADIENT_VALUES = sizeof(GRADIENT) / sizeof(char);
    
    printf("\x1b[H");
    printf("\x1b[2J");
    
    for (int n = 0; n < 200; n++)
    {

        // 12 triangles, 3 vectors each
        struct Vec3 triCollection[12][3];

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
        
        float t = n * 0.1f;
        for (unsigned char tri = 0; tri < 12; tri++)
        {

            // SPIN
            triCollection[tri][0] = rotateX(triCollection[tri][0], t);
            triCollection[tri][1] = rotateX(triCollection[tri][1], t);
            triCollection[tri][2] = rotateX(triCollection[tri][2], t);

            triCollection[tri][0] = rotateY(triCollection[tri][0], t / 2.5f);
            triCollection[tri][1] = rotateY(triCollection[tri][1], t / 2.5f);
            triCollection[tri][2] = rotateY(triCollection[tri][2], t / 2.5f);

            triCollection[tri][0] = rotateZ(triCollection[tri][0], t / 2.f);
            triCollection[tri][1] = rotateZ(triCollection[tri][1], t / 2.f);
            triCollection[tri][2] = rotateZ(triCollection[tri][2], t / 2.f);

            // TRANSLATE Z
            triCollection[tri][0].z += DISTANCE_FROM_CAMERA;
            triCollection[tri][1].z += DISTANCE_FROM_CAMERA;
            triCollection[tri][2].z += DISTANCE_FROM_CAMERA;

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

            triCollection[tri][0].x += sinf(t / 1.f) / 2.f;
            triCollection[tri][1].x += sinf(t / 1.f) / 2.f;
            triCollection[tri][2].x += sinf(t / 1.f) / 2.f;

            triCollection[tri][0].y += cosf(t / 1.f) / 2.f;
            triCollection[tri][1].y += cosf(t / 1.f) / 2.f;
            triCollection[tri][2].y += cosf(t / 1.f) / 2.f;

            triCollection[tri][0].x *= 0.5f * W; 
            triCollection[tri][0].y *= 0.5f * H;     
            triCollection[tri][1].x *= 0.5f * W; 
            triCollection[tri][1].y *= 0.5f * H; 
            triCollection[tri][2].x *= 0.5f * W; 
            triCollection[tri][2].y *= 0.5f * H;  
        }

        unsigned short hit = 0;
        unsigned short hit_keys[H][W];
        unsigned short brightness_keys[H][W];

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                hit_keys[i][j] = 0; 
                brightness_keys[i][j] = 0;

                for (int tri = 0; tri < 12; tri++) {

                    // TODO: Calculating brightness needs to come before projection

                    const struct Vec3 l1 = {
                        triCollection[tri][1].x - triCollection[tri][0].x,
                        triCollection[tri][1].y - triCollection[tri][0].y,
                        triCollection[tri][1].z - triCollection[tri][0].z,
                    };
                    const struct Vec3 l2 = {
                        triCollection[tri][2].x - triCollection[tri][1].x,
                        triCollection[tri][2].y - triCollection[tri][1].y,
                        triCollection[tri][2].z - triCollection[tri][1].z,
                    };
                    const struct Vec3 surfaceNormal = unit(cross(l1, l2));
                    const struct Vec3 lToCamera = {
                        triCollection[tri][0].x - camera.x,
                        triCollection[tri][0].y - camera.y,
                        triCollection[tri][0].z - camera.z,
                    };

                    if (dot(surfaceNormal, lToCamera) < 0.f && 
                        triCollection[tri][0].z > 0.f &&
                        triCollection[tri][1].z > 0.f && 
                        triCollection[tri][2].z > 0.f) {
                        
                        // These need to come before projection
                        const float intensity = dot(surfaceNormal, light);
                        const int brightnessIndex = max(min(roundf(intensity * N_GRADIENT_VALUES), N_GRADIENT_VALUES - 1), 0);

                        for (int side = 0; side < 3; side++) {

                            const float m = (float)(triCollection[tri][(side + 1) % 3].y - triCollection[tri][side].y) / 
                                        (float)(triCollection[tri][(side + 1) % 3].x - triCollection[tri][side].x);

                            if (fabs(m) <= 1) {
                                const int y = roundf(f(j, triCollection[tri][side], triCollection[tri][(side + 1) % 3]));
                                const int x_max = (int)max(triCollection[tri][side].x, triCollection[tri][(side + 1) % 3].x);
                                const int x_min = (int)min(triCollection[tri][side].x, triCollection[tri][(side + 1) % 3].x);

                                if (i == y && j >= x_min && j <= x_max) {
                                    hit = 1; 
                                    hit_keys[i][j] = 1;
                                    brightness_keys[i][j] = brightnessIndex;
                                } else {hit = 0;}
                            }

                            else {
                                const int x = roundf(g(i, triCollection[tri][side], triCollection[tri][(side + 1) % 3]));
                                const int y_max = (int)max(triCollection[tri][side].y, triCollection[tri][(side + 1) % 3].y);
                                const int y_min = (int)min(triCollection[tri][side].y, triCollection[tri][(side + 1) % 3].y);

                                if (j == x && i >= y_min && i <= y_max) {
                                    hit = 1; 
                                    hit_keys[i][j] = 1;
                                    brightness_keys[i][j] = brightnessIndex;
                                } else {hit = 0;}
                            }
                        }
                    }
                }
            }
        }

        for (int i=0; i<H; i++) {
            for (int j=0; j<W; j++) {

                // Fix fill

                // Fill (Check if borders at least 2 hits)
                // if (i != 0 && i != H - 1 && j != 0 && j != W - 1) {
                //     if (hit_keys[i+1][j] + hit_keys[i-1][j] + hit_keys[i][j+1] + hit_keys[i][j-1] >= 2 && !hit_keys[i][j]) {
                //         hit_keys[i][j] = 1;
                //     }
                // }

                if (hit_keys[i][j]) {
                    //putchar(GRADIENT[brightness_keys[i][j]]);
                    putchar('+');
                } else {putchar(' ');}
            }
            putchar('\n');
        }
        printf("\x1b[H");
     
    }

    return 0;
}
