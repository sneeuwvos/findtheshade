#include "affinetransf.h"

/**
 * This helper takes two YIQ colors with three components
 * each, and defines the matrix that transforms one into
 * the other
 * */

void get_yiq_trans(norm_col source, norm_col target, double* mat) {
    double v = target.r / source.r;
    double beta = (target.b - source.b*target.g / source.g)
                / (source.g + source.b*source.b / source.g);
    double alpha = (target.g + source.b * beta) / source.g;

    mat[0] = v;
    mat[1] = 0;
    mat[2] = 0;
    mat[3] = 0;
    mat[4] = alpha;
    mat[5] = -beta;
    mat[6] = 0;
    mat[7] = beta;
    mat[8] = alpha;
}

/** See the *.h file */

rgb_color apply_affine_trans_via_yiq(
    rgb_color sample_source,
    rgb_color sample_target,
    rgb_color rgb_having
) {
    /* Normalize the input colors from RGB 0-255 to RGB 0-1 */
    norm_col norm_source = rgb_norm(sample_source);
    norm_col norm_target = rgb_norm(sample_target);

    /* Convert the normalized RGB colors to the YIQ color space */
    norm_col yiq_source = rgb_to_yiq(norm_source);
    norm_col yiq_target = rgb_to_yiq(norm_target);

    /* More vars to be used later */
    double yiq_trans[9];
    norm_col norm_having;
    norm_col yiq_having;
    norm_col yiq_wanted;
    norm_col norm_wanted;
    rgb_color rgb_wanted;

    /* Obtain transformation matris yiq_source -> yiq_target */
    get_yiq_trans(yiq_source, yiq_target, yiq_trans);

    /**
     * Normalize the owned color and convert it to the YIQ
     * colorspace
     * */
    norm_having = rgb_norm(rgb_having);
    yiq_having = rgb_to_yiq(norm_having);

    /**
     * Project the owned into the wanted color in the YIQ color
     * space and convert it back to the RGB 0-255.
     * */
    yiq_wanted = col_matmult(yiq_having, yiq_trans);
    norm_wanted = yiq_to_rgb(yiq_wanted);
    rgb_wanted = rgb_unnorm(norm_wanted);

    return rgb_wanted;
}
