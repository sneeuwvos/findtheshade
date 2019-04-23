#include <string.h>
#include <math.h>

#include <shades.h>
#include <colorutils.h>

/**
 * Lookup of a shade by name inside an array. Yeh wish yeh
 * had Perl hashes here.
 * */

rgb_shade find_shade_by_name(
    rgb_shade* shade_arr,
    int shade_arr_size,
    const char* shade_name
) {
    rgb_shade shade_having;
    for(int i=0; i < shade_arr_size; i++) {
        rgb_shade curr_shade = shade_arr[i];
        if(!strcmp(curr_shade.name, shade_name)) {
            shade_having = curr_shade;
            return shade_having;
        }
    }
    return null_shade;
}

/**
 * Color and shade printers.
 * */

void print_rgb_color(FILE* handle, rgb_color col) {
    fprintf(handle, "(%03d, %03d, %03d)", col.r, col.g, col.b);
}

void print_rgb_shade(FILE* handle, rgb_shade col) {
    fprintf(handle, "%s: (%03d, %03d, %03d)", col.name, col.color.r, col.color.g, col.color.b);
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

double sq(double v) { return v*v; } // square doubles

double color_distance_base(int ar, int ag, int ab, int br, int bg, int bb) {
    return sqrt(sq(ar-br) + sq(ag-bg) + sq(ab - bb));
}

double color_distance(rgb_color a, rgb_color b) {
    return color_distance_base(a.r, a.g, a.b, b.r, b.g, b.b);
}
