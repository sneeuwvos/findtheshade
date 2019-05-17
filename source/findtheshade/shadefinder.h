#ifndef INCL_FTS_SHADE_FINDER
#define INCL_FTS_SHADE_FINDER

#include "shades.h"

/**
 * Type for a search result
 * */

typedef struct {
    double dist;
    double hue_dist;
    rgb_shade* mc;
    double luminance_cmp;
} rgb_shade_search_result;

/**
 * Wrapper for search result array, that also contains its
 * length, and possibly other metadata in future.
 * */

typedef struct {
    rgb_shade_search_result* result_arr;
    int length;
    double wanted_luminance_cmp;
    rgb_color rgb_shade_wanted;
    rgb_shade owned_shade;
} rgb_shade_search_result_with_meta;

/**
 * Helper that determines the closest color matches, given
 * all the colors
 * */

rgb_shade_search_result_with_meta* closest_rgb_shades(
    /**
     * Array of rgb_shades that represent the assortment to
     * choose from. Then also its length.
     * */
    rgb_shade* rgb_shade_arr,
    int rgb_shade_arr_size,

    /**
     * The color one has got on their photo, by applying the
     * make-up shade they have available
     * */
    rgb_color color_having,
    /**
     * Name of the make-up shade applied. This name has to be
     * one of the names in the rgb_shade_arr array
     * */
    const char* color_having_name,
    /**
     * The color the user would like to achieve with a dif-
     * ferent shade.
     * */
    rgb_color color_wanted
);

/**
 * Result comparator by dist
 * */

int compare_temp_results_by_dist(const void *, const void *); /* Wants two of type rgb_shade_search_result */

/**
 * Custom freer for the search result data type
 * */

void free_closest_rgb_shades(rgb_shade_search_result_with_meta*);

#endif
