#include <string.h>
#include <math.h>

#include "colorutils.h"

#define EPSILON 0.00001

/** Printer for rgb_color */

void print_rgb_color(FILE* handle, rgb_color col) {
    fprintf(handle, "(%03d, %03d, %03d)", col.r, col.g, col.b);
}

/**
 * Simple transformation helpers. In order to translate the
 * real world colors into ideal palettes, some transforming
 * is be needed over the input colors.
 *
 * Below are very simple (and fragile mind ya) operators
 * that simply scale the three RGB channels by some coef-
 * ficient and back on this purpose.
 *
 * This bit can be upgraded big time.
 * */

void obtain_transformation_linear(rgb_color source, rgb_color target, double* transformation) {
    transformation[0] = (double)target.r / source.r;
    transformation[1] = (double)target.g / source.g;
    transformation[2] = (double)target.b / source.b;
}

rgb_color apply_transformation_linear(rgb_color source, double* transformation) {
    rgb_color target = source;
    target.r = (int)(target.r * transformation[0]);
    target.g = (int)(target.g * transformation[1]);
    target.b = (int)(target.b * transformation[2]);
    return target;
}

/**
 * Luminance helpers. The first one computes luminance of the
 * given rgb_color. The second one is comparator for lumi-
 * nances of the two given colors.
 * */

double luminance(rgb_color col) {
    return
        0.2126 * col.r
        + 0.7152 * col.g
        + 0.0722 * col.b
    ;
}

double luminance_cmp(rgb_color having, rgb_color than) {
    double l_having = luminance(having);
    double l_than = luminance(than);
    return l_having - l_than;
}

/**
 * The two following helpers deal with euclidean color dis-
 * tance. Here, the colors are treated as 3D coordiantes and
 * their distance is computed as the one betwen the coord-
 * inates.
 *
 * The small helper sq(...) should probably be elsewhere.
 * */

double sq(double v) { return v*v; } /* square doubles */

double color_distance_base(int ar, int ag, int ab, int br, int bg, int bb) {
    return sqrt(sq(ar-br) + sq(ag-bg) + sq(ab - bb));
}

double color_distance(rgb_color a, rgb_color b) {
    return color_distance_base(a.r, a.g, a.b, b.r, b.g, b.b);
}

/** Helper that tells hue distance between two colors */

double hue_distance(rgb_color a, rgb_color b) {
    norm_col na = rgb_norm(a);
    norm_col nb = rgb_norm(b);

    /* Get hue from the a */
    norm_col hsva = rgb_to_hsv(na);

    /* Get hue from the b */
    norm_col hsvb = rgb_to_hsv(nb);

    return fabs(hsva.r - hsvb.r);
}

/** Normalizer for 0-255 RGBs into [0-1] RGBs */
norm_col rgb_norm(rgb_color rgb) {
    norm_col nc = {rgb.r / 255.0, rgb.g / 255.0, rgb.b / 255.0};
    return nc;
}

/** Unnormalizer from [0-1] RGBs to 0-255 RGBs */
rgb_color rgb_unnorm(norm_col nc) {
    rgb_color rgb = {(int)(255.0 * nc.r), (int)(255.0 * nc.g), (int)(255.0 * nc.b)};
    return rgb;
}

/** Multiplier for a color and a transformation matrix */
norm_col col_matmult(norm_col col, double* mat) {
    norm_col res = {
        col.r * mat[0] + col.g * mat[1] + col.b * mat[2],
        col.r * mat[3] + col.g * mat[4] + col.b * mat[5],
        col.r * mat[6] + col.g * mat[7] + col.b * mat[8]
    };
    return res;
}

/** Converter from normalized RGB to YIQ */
double rgb_to_yiq_arr[] = {0.299, 0.587, 0.114, 0.596, -0.274, -0.321, 0.211, -0.523, 0.311};
norm_col rgb_to_yiq(norm_col rgb) {
    return col_matmult(rgb, rgb_to_yiq_arr);
}

/** Converter from YIQ to normalized RGB */
double yiq_to_rgb_arr[] = {0.999664, 0.956541, 0.620862, 0.999625, -0.272275, -0.647451, 1.00281, -1.10685, 1.70541};
norm_col yiq_to_rgb(norm_col yiq) {
    return col_matmult(yiq, yiq_to_rgb_arr);
}

/** Converted from RGB to HSV */
norm_col rgb_to_hsv(norm_col col) {
    double maxval = fmax(fmax(col.r, col.b), col.b);
    double minval = fmin(fmin(col.r, col.b), col.b);

    double h;
    double s;
    double v;

    /** Hue */
    if(fabs(maxval - minval) < EPSILON) {
        h = 0;
    }
    else if(col.r > col.b && col.r > col.g) {
        h = 60.0 * (0 + (col.g - col.b) / (maxval - minval));
    }
    else if(col.g > col.r && col.g > col.b) {
        h = 60.0 * (2 + (col.b - col.r) / (maxval - minval));
    }
    else {
        h = 60.0 * (4 + (col.r - col.g) / (maxval - minval));
    }

    if(h < 0) { h += 360.0; }

    /** Saturation */
    if(fabs(maxval) < EPSILON) {
        s = 0;
    }
    else {
        s = (maxval - minval) / maxval;
    }

    /** Value */
    v = maxval;

    norm_col hsv = {h, s, v};
    return hsv;
}
