#include <stdlib.h>

#include "shadefinder.h"

int main(void) {
    // Obtain the shade palette
    rgb_shade* foundation_colors = all_foundation_colors();
    int foundation_colors_size = all_foundation_colors_size();

    // Define some input
    rgb_color having = {189, 157, 144};
    rgb_color wanted = {198, 177, 172};
    const char* shade_name = "N4";

    // Make the query
    rgb_shade_search_result_with_meta search_results = closest_rgb_shades(
        foundation_colors,
        foundation_colors_size,
        having,
        shade_name,
        wanted
    );

    // Process the results
    if(search_results.result_arr && search_results.length) {
        printf("Face color with the owned shade:\n ");
        print_rgb_color(stdout, having);
        printf("\n\nOwned shade:\n ");
        print_rgb_shade(stdout, search_results.owned_shade);
        printf("\n\n");
        printf("Wanted face color:\n ");
        print_rgb_color(stdout, wanted);
        printf("\n\nProjected wanted shade color:\n ");
        print_rgb_color(stdout, search_results.rgb_shade_wanted);
        printf("; luminance_cmp: %.3f\n\nOptions:\n", search_results.wanted_luminance_cmp);

        for(int i=0; i<search_results.length; i++) {
            rgb_shade_search_result* sr = &search_results.result_arr[i];
            printf(" - ");
            print_rgb_shade(stdout, *(sr->mc));
            printf(": dist: %.3f; hue_dist: %.3f; luminance_cmp: %.3f\n", sr->dist, sr->hue_dist, sr->luminance_cmp);
        }
        free(search_results.result_arr);
    }
    else {
        printf("No results for this query.\n");
    }

    return 0;
}
