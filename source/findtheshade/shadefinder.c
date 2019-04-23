#include <stdlib.h>

#include <shadefinder.h>

int compare_temp_results_by_dist(const void *a, const void *b) {
    return (int)(1000*((const rgb_shade_search_result*)a)->dist) - (int)(1000*((const rgb_shade_search_result*)b)->dist);
}

rgb_shade_search_result_with_meta closest_rgb_shades(
    rgb_shade* rgb_shade_arr,
    int rgb_shade_arr_size,

    rgb_color color_having,
    const char* color_having_name,
    rgb_color color_wanted
) {
    // First obtain the color that we are having by name
    rgb_shade rgb_shade_having = find_shade_by_name(
        rgb_shade_arr,
        rgb_shade_arr_size,
        color_having_name
    );

    if(is_null_shade(rgb_shade_having)) {
        rgb_shade_search_result_with_meta null_result;
        return null_result;
    } // TODO: any error message?

    /**
     * Now, obtain the transformation from the ideal color
     * palette item to the color that is stated as 'having'.
     *
     * This will allow to translate the wanted color to the
     * palette that this code knows about.
     * */
    double transf[3];
    obtain_transformation_linear(
        color_having, // source
        rgb_shade_having.color, // target,
        transf
    );

    /** Here it is. The wanted color */
    rgb_color rgb_shade_wanted = apply_transformation_linear(color_wanted, transf);

    // Compute its luminance diff ftr
    double wanted_luminance_cmp = luminance_cmp(rgb_shade_wanted, rgb_shade_having.color);

    /**
     * This will now walk through all possible shades in
     * search for best matches to achieve the wanted color.
     * */
    rgb_shade_search_result* search_results = calloc(rgb_shade_arr_size, sizeof(rgb_shade_search_result));

    /**
     * Prepare the result array. (fill it with the data)
     * */
    for(int i=0; i<rgb_shade_arr_size; i++) {
        double dist = color_distance(rgb_shade_arr[i].color, rgb_shade_wanted);
        int luminance_cmp_res = luminance_cmp(rgb_shade_arr[i].color, rgb_shade_wanted);
        search_results[i].dist = dist;
        search_results[i].mc = &rgb_shade_arr[i];
        search_results[i].luminance_cmp = luminance_cmp_res;
    }

    /**
     * Sort the result array
     * */
    qsort(search_results, rgb_shade_arr_size, sizeof(rgb_shade_search_result), compare_temp_results_by_dist);

    /**
     * Prepare the result
     * */
    rgb_shade_search_result_with_meta search_results_with_meta;

    /* Better do it one by one than worry whether the order may
     * get altered in the future
     * */
    search_results_with_meta.result_arr = search_results;
    search_results_with_meta.length = rgb_shade_arr_size;
    search_results_with_meta.wanted_luminance_cmp = wanted_luminance_cmp;
    search_results_with_meta.rgb_shade_wanted = rgb_shade_wanted;
    search_results_with_meta.owned_shade = rgb_shade_having;

    return search_results_with_meta;
}

