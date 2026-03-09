/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for g conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

static int if_zero_bigger_five(
    int count, printf_context_t *ctx, printf_render_params_t *params)
{
    int bits = 0;

    bits += printf_my_putstr(params->is_cap ? "E-" : "e-", ctx);
    if (count < 10) {
        bits += (int) printf_my_putchar('0', ctx);
    }
    bits += printf_my_put_nbr(count, ctx);
    return bits;
}

static int rectification(double nb)
{
    int count = -1;
    int nbcopy = nb;
    int do_nb = nbcopy % 10;

    for (; do_nb == 0; nb /= 10) {
        nbcopy = nb;
        do_nb = nbcopy % 10;
        count++;
        if (count == 5)
            return 5;
        if (do_nb != 0)
            return count;
    }
    if (count == -1)
        count = 0;
    return count;
}

static double fo_up_inf_do(int precision, double cool_number)
{
    for (int i = 0; i < precision; i++) {
        cool_number *= 10.000001;
    }
    return cool_number;
}

static int show_after_comma_nb(int precision,
    double nb_frac, printf_context_t *ctx)
{
    int written = 0;
    int num = 0;

    for (int i = 0; i < precision; i++) {
        nb_frac *= 10.00001;
        num = printf_my_modf(nb_frac, 10.000000001);
        written += printf_my_put_nbr(num, ctx);
    }
    return written;
}

static int infinitenbr(double nb, int precision, printf_context_t *ctx)
{
    int trim_count = 0;
    int written = 0;
    double integer_nb = 0.0;
    double nb_frac = 0.0;

    printf_my_putdouble(nb, &(printf_context_t){.outputs = 0}, &nb_frac);
    nb_frac = nb_frac > 0 ? 0 : -nb_frac;
    integer_nb = nb - nb_frac;
    written += printf_my_put_nbr(integer_nb, ctx);
    trim_count = rectification(fo_up_inf_do(precision, nb_frac));
    precision -= trim_count;
    if ((trim_count == 5 && integer_nb != 0) || precision == 0) {
        return written;
    }
    written += printf_my_putchar('.', ctx);
    written += show_after_comma_nb(precision, nb_frac, ctx);
    return written;
}

static int if_zero(double nb, printf_context_t *ctx,
    printf_render_params_t *params)
{
    int count = 0;
    long int simplenb = 0;
    int kar = 0;
    int written = 0;

    for (double d = nb; (int)d == 0; d *= 10) {
        count++;
        if (count > 350)
            return printf_my_putchar('0', ctx);
    }
    if (count >= 5) {
        nb = fo_up_inf_do(count, nb);
        simplenb = nb;
        for (double i = 1.0; i < simplenb; i *= 10.0)
            kar++;
        written += infinitenbr(nb, 6 - kar, ctx);
        return written + if_zero_bigger_five(count, ctx, params);
    }
    return infinitenbr(nb, 6, ctx);
}

static int scientific_plus(double nb, int after_comma,
    printf_render_params_t *params, printf_context_t *ctx)
{
    int bits = 0;
    int count = 0;

    for (; nb >= 10; nb /= 10) {
        count++;
    }
    bits += infinitenbr(nb, after_comma, ctx);
    bits += printf_my_putstr(params->is_cap ? "E+" : "e+", ctx);
    if (count < 10)
        bits += printf_my_putchar('0', ctx);
    bits += printf_my_put_nbr(count, ctx);
    return bits;
}

static int for_g(double nb, printf_render_params_t *params,
    printf_context_t *ctx)
{
    double part_entiere = 0.0;
    int amount = 0;

    printf_my_putdouble(nb, &(printf_context_t){.outputs = 0}, &part_entiere);
    part_entiere += nb;
    if ((long int)nb != 0)
        for (double i = 1.0; i <= nb; i *= 10.0) {
            amount++;
        }
    if (params->precision == 0)
        params->precision++;
    if (amount > params->precision)
        return scientific_plus(nb, params->precision - 1, params, ctx);
    if ((int) part_entiere == 0) {
        return if_zero(nb, ctx, params);
    }
    return infinitenbr(nb, params->precision - amount, ctx);
}

int printf_hybrid(printf_render_params_t *params,
    printf_context_t *ctx)
{
    double nb = va_arg(ctx->args, double);
    char neg = (char) (*(unsigned long long *) &nb >> 63);
    int written = 0;

    if (params->precision < 0)
        params->precision = 6;
    written += printf_write_sign_prefix(neg, params, ctx);
    if (printf_print_invalid_double(nb, params->is_cap, ctx, &written))
        return written;
    return for_g(neg ? -nb : nb, params, ctx) + written;
}
