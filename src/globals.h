#pragma once
#include <math.h>
#include "Mat44.h"

#define W 40
#define H 20
#define ASPECT_RATIO (float)H / (float)W

#define Z_NEAR 0.1f
#define Z_FAR 100.f
#define FOV 3.1415926535897932f / 2.f
#define HALF_FOV FOV / 2.f
#define FOCAL_LENGTH 1.f / tanf(HALF_FOV)
#define DISTANCE_FROM_CAMERA 1.f
#define INIT_TRANSLATION 1.f
#define N_TRIS 12
