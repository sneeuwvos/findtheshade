#ifndef INCL_FTS_COLOR_UTILS
#define INCL_FTS_COLOR_UTILS

#include <stdio.h>

/** Name tag for the null color */
#define NO_COLOR_TAG "NOCOLOR"

/** Data type for a LDR (integer-valued) RGB color */

typedef struct {
    unsigned char r, g, b;
} rgb_color;

/** Data type for universal colors with three components */

typedef struct {
    double r, g, b;
} norm_col;

/**
 * Color printers. One for rgb_shade, one for rgb_color.
 * */

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

/** Normalizer for 0-255 RGBs into [0-1] RGBs */

norm_col rgb_norm(rgb_color rgb);

/** Unnormalizer from [0-1] RGBs to 0-255 RGBs */

rgb_color rgb_unnorm(norm_col nc);

/** Multiplier for a color and a transformation matrix */

norm_col col_matmult(norm_col col, double* mat);

/** Converter from normalized RGB to YIQ */

norm_col rgb_to_yiq(norm_col rgb);

/** Converter from YIQ to normalized RGB */

norm_col yiq_to_rgb(norm_col yiq);

/** Converted from RGB to HSV */

norm_col rgb_to_hsv(norm_col col);

#endif
