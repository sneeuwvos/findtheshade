#ifndef INCL_FTS_SHADES
#define INCL_FTS_SHADES

#include "colorutils.h"

/** Data type for a RGB shade */

typedef struct {
    rgb_color color;
    char* name;
} rgb_shade;

/**
 * This is null-object for colors. If at some point this was
 * returned instead of a color, then there is no color that
 * matches the set requirements.
 *
 * The following helper tells whether the color given is a
 * null color or not.
 * */

rgb_shade null_shade; /* Declaration of the null shade */
int is_null_shade(rgb_shade);

/**
 * These are function that return static arrays of colors.
 * So far, only foundation array is there.
 * */

rgb_shade* all_foundation_colors();
int all_foundation_colors_size();

/** Printer for a RGB shade */

void print_rgb_shade(FILE*, rgb_shade);

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

#endif
