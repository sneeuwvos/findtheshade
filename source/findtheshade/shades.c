#include<string.h>

#include "shades.h"
#include "colorutils.h"

/**
 * Definition of the null shade
 * */

rgb_shade null_shade = {{0, 0, 0}, NO_COLOR_TAG};

/**
 * An array of foundation colors with their respective names.
 * It is followed by the array size definition.
 * */

static rgb_shade foundation_colors[] = {
    {{238, 209, 174}, "C2"},
    {{240, 206, 170}, "C3"},
    {{239, 203, 172}, "C3.5"},
    {{255, 229, 206}, "NC10"},
    {{242, 206, 162}, "C30"},
    {{240, 206, 160}, "C35"},
    {{235, 198, 158}, "C4"},
    {{241, 201, 165}, "C4.5"},
    {{233, 195, 144}, "C40"},
    {{243, 199, 157}, "C5"},
    {{237, 193, 156}, "C5.5"},
    {{232, 185, 137}, "C6"},
    {{232, 180, 132}, "C7"},
    {{219, 169, 113}, "C8"},
    {{243, 214, 192}, "N3"},
    {{241, 210, 184}, "N4"},
    {{241, 202, 168}, "N5"},
    {{236, 151, 94}, "NC47"},
    {{217, 162, 115}, "N9"},
    {{238, 210, 186}, "NC15"},
    {{218, 123, 75}, "NW55"},
    {{243, 212, 176}, "NC20"},
    {{241, 205, 166}, "NC25"},
    {{240, 207, 163}, "NC30"},
    {{241, 202, 160}, "NC35"},
    {{241, 201, 156}, "NC40"},
    {{243, 192, 140}, "NC42"},
    {{244, 195, 136}, "NC43"},
    {{255, 195, 143}, "NC43.5"},
    {{255, 188, 135}, "NC44.5"},
    {{232, 179, 125}, "NC45"},
    {{223, 178, 120}, "NC50"},
    {{216, 170, 113}, "NC55"},
    {{242, 213, 188}, "NW10"},
    {{238, 212, 188}, "NW13"},
    {{236, 208, 187}, "NW15"},
    {{235, 207, 179}, "NW18"},
    {{231, 197, 174}, "NW20"},
    {{235, 200, 168}, "NW22"},
    {{227, 189, 156}, "NW25"},
    {{229, 183, 141}, "NW30"},
    {{228, 187, 153}, "NW33"},
    {{213, 168, 125}, "NW35"},
    {{205, 154, 113}, "NW40"},
    {{215, 159, 111}, "NW43"},
    {{218, 164, 110}, "NW44"},
    {{211, 156, 105}, "NW45"},
    {{211, 150, 99}, "NW46"},
    {{193, 142, 94}, "NW48"},
    {{191, 140, 96}, "NW50"},
    {{159, 113, 81}, "NW58"},
};

static int size_of_foundation_colors = sizeof(foundation_colors) / sizeof(rgb_shade);

/**
 * Getters for the foundation color array and its size
 * */

int all_foundation_colors_size() {
    return size_of_foundation_colors;
}

rgb_shade* all_foundation_colors() {
    return foundation_colors;
}

/**
 * Definition of the helper tha tells if a rgb_shade is a
 * null color or not.
 * */

int is_null_shade(rgb_shade color) {
    return color.name == 0 || !strcmp(color.name, NO_COLOR_TAG);
}
