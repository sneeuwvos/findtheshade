#ifndef INCL_FTS_COLOR_UTILS
#define INCL_FTS_COLOR_UTILS

#include <stdio.h>

#include "shades.h"

/**
 * Color searcher across an array of rgb_shades. It requires
 * the input array, its size, and the string name of the
 * color that is being looked for.
 * */

rgb_shade find_shade_by_name(
    rgb_shade* shade_arr,
    int shade_arr_size,
    const char* shade_name
);

/**
 * Color printers. One for rgb_shade, one for rgb_color.
 * */

void print_rgb_shade(FILE*, rgb_shade);
void print_rgb_color(FILE*, rgb_color);

/**
 * Helper that tells the luminance of a color.
 * */

double luminance(rgb_color col);

/**
 * Helpers that tell whether the color one is 'having' is
 * darker or lighter 'than' the other color they give
 * */

double luminance_cmp(rgb_color, rgb_color);

/**
 * Helpers that help translate colors around in order to
 * compensate for the difference between the picture and
 * the color palette
 * */

void obtain_transformation_linear(rgb_color, rgb_color, double*);
rgb_color apply_transformation_linear(rgb_color, double*);

/**
 * Helpers that tell the distance between two colors. There
 * is the variant that takes rgb_colors and the variant that
 * takes rgb values of both colors.
 *
 * The output value is non-negative, between 0 and ~441.67.
 * */

double color_distance(rgb_color a, rgb_color b);
double color_distance_base(int ar, int ag, int ab, int br, int bg, int bb);

#endif
