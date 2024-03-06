#pragma once
#include <math.h>
#include "Mat44.h"

const int W = 40;
const int H = 20;
const float ASPECT_RATIO = (float)H / (float)W;

const float Z_NEAR = 0.1f;
const float Z_FAR = 100.f;
const float FOV = 3.1415926535897932f / 2.f;
const float FOCAL_LENGTH = 1.f / tan(FOV / 2.f);
const float DISTANCE_FROM_CAMERA = 1.5f;
const float INIT_TRANSLATION = 1.f;

const char PROJECTED_CHAR[6] = {' ', '.', '~', '+', '$', '#'};