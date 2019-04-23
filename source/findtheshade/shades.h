#ifndef INCL_FTS_SHADES
#define INCL_FTS_SHADES

// Name tag for the null color
#define NO_COLOR_TAG "NOCOLOR"

/**
 * Hereby defining the data types that will be used further
 * in the code.
 *
 * The first type is rgb_color, that contains plain LDR r,
 * g, b values with range 0-255.
 *
 * The second type is rgb_shade, that also contains pointer
 * to static string name of the foundation.
 * */

typedef struct {
    unsigned char r, g, b;
} rgb_color;

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

rgb_shade null_shade; // Declaration of the null color

int is_null_shade(rgb_shade);

/**
 * These are function that return static arrays of colors.
 * So far, only foundation array is there.
 * */

rgb_shade* all_foundation_colors();
int all_foundation_colors_size();

#endif
