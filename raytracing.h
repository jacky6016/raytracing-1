#ifndef __RAYTRACING_H
#define __RAYTRACING_H

#include "objects.h"
#include <stdint.h>

typedef struct __RAY {
    uint8_t *pixels;
    double * background_color;
    rectangular_node rectangulars;
    sphere_node spheres;
    light_node lights;
    const viewpoint *view;
    int width;
    int height;
    int job_num;
    int total_jobs;
} ray_param;

void raytracing(void *rp);

ray_param* pack_param(uint8_t *pixels, color background_color,
                      rectangular_node rectangulars, sphere_node spheres,
                      light_node lights, const viewpoint *view,
                      int width, int height, int job_num, int total_jobs);
#endif
