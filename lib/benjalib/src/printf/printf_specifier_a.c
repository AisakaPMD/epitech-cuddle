/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for a conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

static int writedouble(double nb, int precision,
    printf_context_t *ctx, char is_cap)
{
    int written = 0;
    char const *base = is_cap ?
        "0123456789ABCDEF" : "0123456789abcdef";

    written += printf_my_putnbr_base((long int) nb, base, ctx);
    written += printf_my_putchar('.', ctx);
    for (int i = 0; i != precision; i++) {
        nb *= 16;
        written += printf_my_putnbr_base((int) nb % 16, base, ctx);
    }
    return written;
}

static int for_a(double nb, printf_render_params_t *params,
    printf_context_t *ctx)
{
    int written = 0;
    int exp = 0;
    char neg = nb != 0.0 && nb < 1.0;
    int precision = params->precision >= 0 ? params->precision : 4;
    double multiple = 2.0;

    written += printf_my_putstr(params->is_cap ? "0X" : "0x", ctx);
    if (neg)
        for (; nb < 1.0; nb *= multiple)
            exp++;
    else
        for (; nb >= 2.0; nb /= multiple)
            exp++;
    written += writedouble(nb, precision, ctx, params->is_cap);
    if (neg)
        written += printf_my_putstr(params->is_cap ? "P-" : "p-", ctx);
    else
        written += printf_my_putstr(params->is_cap ? "P+" : "p+", ctx);
    return written + printf_my_put_nbr(exp, ctx);
}

int printf_exp_hex(printf_render_params_t *params,
    printf_context_t *ctx)
{
    double nb = va_arg(ctx->args, double);
    char neg = (char) (*(unsigned long long *) &nb >> 63);
    int written = 0;

    written += printf_write_sign_prefix(neg, params, ctx);
    if (printf_print_invalid_double(nb, params->is_cap, ctx, &written))
        return written;
    return for_a(neg ? -nb : nb, params, ctx) + written;
}
