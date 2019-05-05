#include <affinetransf.h>
#include <colorutils.h>

/** Data type for universal colors with three components */
typedef struct {
    double a, b, c;
} norm_col;

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
    norm_col norm_source = rgb_norm(sample_source);
    norm_col norm_target = rgb_norm(sample_target);

    norm_col yiq_source = rgb_to_yiq(norm_source);
    norm_col yiq_target = rgb_to_yiq(norm_target);

    double yiq_trans[9];
    get_yiq_trans(yiq_source, yiq_target, yiq_trans);

    norm_col norm_having = rgb_norm(rgb_having);
    norm_col yiq_having = rgb_to_yiq(norm_having);
    norm_col yiq_wanted = col_matmult(yiq_having, yiq_trans);
    norm_col norm_wanted = yiq_to_rgb(yiq_wanted);
    rgb_color rgb_wanted = rgb_unnorm(norm_wanted);

    return rgb_wanted;
}
