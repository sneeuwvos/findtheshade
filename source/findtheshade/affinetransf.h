#ifndef INCL_FTS_AFFINE_TRANSF
#define INCL_FTS_AFFINE_TRANSF

#include "colorutils.h"

/**
 * This helper takes two YIQ colors with three components
 * each, and defines the matrix that transforms one into
 * the other
 * */

void get_yiq_trans(norm_col source, norm_col target, double* mat);

/**
 * Uses affine transformation in via the UIQ color space in
 * order to prject the shade_source color onto what it would
 * have been if it were to become sample_target from the
 * sample_source.
 * */

rgb_color apply_affine_trans_via_yiq(
    rgb_color sample_source,
    rgb_color sample_target,
    rgb_color shade_source
);

#endif
