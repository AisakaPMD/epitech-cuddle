/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for e conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

static int writedouble(double nb, int precision, printf_context_t *ctx)
{
    int written = 0;

    written += printf_my_put_nbr((long int) nb, ctx);
    written += printf_my_putchar('.', ctx);
    for (int i = 0; i != precision; i++) {
        nb *= 10;
        written += printf_my_put_nbr((int) nb % 10, ctx);
    }
    return written;
}

static double dbl_pow(char neg, int precision)
{
    double multiple = .1;

    for (double d = 0; d < precision; d++)
        multiple /= 10.0;
    return 10.0 + (!neg ? (-multiple) : (multiple));
}

static int for_e(double nb, printf_render_params_t *params,
    printf_context_t *ctx)
{
    int written = 0;
    int exp = 0;
    char neg = nb != 0.0 && nb < 1.0;
    int precision = params->precision >= 0 ? params->precision : 6;
    double multiple = dbl_pow(neg, precision);

    if (neg)
        for (; nb < 1.0; nb *= multiple)
            exp++;
    else
        for (; nb >= 10; nb /= multiple)
            exp++;
    written += writedouble(nb, precision, ctx);
    if (neg)
        written += printf_my_putstr(params->is_cap ? "E-" : "e-", ctx);
    else
        written += printf_my_putstr(params->is_cap ? "E+" : "e+", ctx);
    if (exp < 10)
        written += printf_my_putchar('0', ctx);
    return written + printf_my_put_nbr(exp, ctx);
}

int printf_exponent(printf_render_params_t *params,
    printf_context_t *ctx)
{
    double nb = va_arg(ctx->args, double);
    char neg = (char) (*(unsigned long long *) &nb >> 63);
    int written = 0;

    written += printf_write_sign_prefix(neg, params, ctx);
    if (printf_print_invalid_double(nb, params->is_cap, ctx, &written))
        return written;
    return for_e(neg ? -nb : nb, params, ctx) + written;
}
