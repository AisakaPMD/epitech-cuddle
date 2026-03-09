/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Printf Entry Point
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"
#include "benjalib/my.h"

static void pad_before(printf_conv_specifier_t const *spec,
    printf_render_params_t *params, ssize_t writ, printf_context_t *ctx)
{
    char padding = (params->flags & RF_ZERO_PADDED) ? '0' : ' ';

    if (params->precision >= 0 && spec->is_int)
        padding = ' ';
    if (!(params->flags & RF_ADJUST_LEFT)) {
        if (!spec->is_int) {
            params->zeroes_padding += params->field_width - writ;
            params->field_width = 0;
        }
        for (int i = 0; i < (params->field_width - writ); i++) {
            printf_my_putchar(padding, ctx);
            ctx->written += 1;
        }
    }
}

static void apply_padding(printf_conv_specifier_t const *spec,
    printf_context_t *ctx, printf_render_params_t *params)
{
    ssize_t writ = 0;
    printf_context_t ctx_copy = {.errored = 0, .outputs = 0, .fd = ctx->fd,
        .buffer = ctx->buffer, .written = 0};

    va_copy(ctx_copy.args, ctx->args);
    writ = spec->callback(params, &ctx_copy);
    va_end(ctx_copy.args);
    if (writ >= params->field_width) {
        ctx->written += spec->callback(params, ctx);
        return;
    }
    pad_before(spec, params, writ, ctx);
    ctx->written += spec->callback(params, ctx);
    if (params->flags & RF_ADJUST_LEFT)
        for (int i = 0; i < (params->field_width - writ); i++) {
            printf_my_putchar(' ', ctx);
            ctx->written += 1;
        }
}

static int parse_flags(char const *format, printf_render_params_t *params)
{
    char flag = *format;
    int new_flags = 0;

    new_flags |= (flag == '#' ? RF_ALTERNATE_FORM : 0);
    new_flags |= (flag == '-' ? RF_ADJUST_LEFT : 0);
    new_flags |= (flag == '+' ? RF_SIGN : 0);
    new_flags |= (flag == ' ' ? RF_SPACE : 0);
    new_flags |= (flag == '0' ? RF_ZERO_PADDED : 0);
    if (new_flags == 0)
        return 0;
    params->flags |= new_flags;
    return 1;
}

static int parse_field_width(char const *format,
    printf_render_params_t *params)
{
    int read_count = 0;
    int value = printf_my_get_unsigned_nbr(format, &read_count, 0);

    if (value == -42) {
        params->flags = value;
        return value;
    }
    if (params->field_width > -2)
        return 0;
    if (value >= 0) {
        params->field_width = value;
        return read_count;
    }
    return parse_flags(format, params);
}

static int parse_precision(char const *format, printf_render_params_t *params)
{
    int read_count = 0;

    if (params->precision > -2)
        return 0;
    if (*format != '.')
        return parse_field_width(format, params);
    params->precision = printf_my_get_unsigned_nbr(format + 1,
        &read_count, 1);
    return read_count + 1;
}

/**
 * Attempts to match the current character(s) with a length modifier.
 * Returns its characters count on success,
 * a negative value if a length modifier was already set,
 * and calls parse_precision otherwise, returning its return value.
 * @param format the format string starting on the 1st character to be parsed
 * @param params a pointer to the render context, which will be filled with
 * the parsed value(s) by this function or further functions
 * @return -1 if the length modifier was already set; the modifier's
 * characters count on matching modifier found; the return value
 * of parse_precision otherwise.
 */
static int parse_len_modifier(char const *format,
    printf_render_params_t *params)
{
    if (params->length_modifier > 0)
        return params->length_modifier == 8 || params->length_modifier == 1
            ? -2 : -1;
    for (int i = 0; printf_length_modifiers[i].value; i++) {
        if (!my_strncmp(format, printf_length_modifiers[i].identifier,
                my_strlen(printf_length_modifiers[i].identifier))) {
            params->length_modifier = printf_length_modifiers[i].value;
            return my_strlen(printf_length_modifiers[i].identifier);
        }
    }
    return parse_precision(format, params);
}

/**
 * Attempts to match the current character with a conversion specifier.
 * Executes its callback on success and calls parse_len_modifier otherwise.
 * Sets the flags to -42 when the conversion specifier is found.
 * @param format the format string, beginning on the first character
 * to be parsed by this function
 * @param params a pointer to the rendering context
 * @param ctx a pointer to the printing context
 * @return 1 on success, the result of further parsing otherwise
 * (see parse_len_modifier)
 */
static int parse_conversion_specifier(char const *format,
    printf_render_params_t *params, printf_context_t *ctx)
{
    char conversion_specifier = format[0];

    if (my_isupper(conversion_specifier)) {
        params->is_cap = 1;
        conversion_specifier += 'a' - 'A';
    }
    if (conversion_specifier == '%') {
        ctx->written++;
        params->flags = -42;
        return printf_my_putchar('%', ctx);
    }
    for (int i = 0; printf_conversion_specifiers[i].callback != NULL; i++) {
        if (printf_conversion_specifiers[i].identifier
            == conversion_specifier) {
            apply_padding(printf_conversion_specifiers + i, ctx, params);
            params->flags = -42;
            return 1;
        }
    }
    return parse_len_modifier(format, params);
}

/**
 * Attempts to parse a conversion parameter, starting at format[0]
 * If none are found, prints the conversion parameter as-is
 * @param ctx the writing context
 * @param format the format string, starting on the parameter to parse
 * @param written a pointer to a size_t holding the number of written bytes
 * @return -42 if the string ends abruptly; -21 on other error, or
 * the size of the conversion parameter if no error is encountered
 */
static int parse_param(printf_context_t *ctx, char const *format
    , size_t *written)
{
    printf_render_params_t params = {0, 0, 0, -2, -2, 0, *written, 0};
    int total_skip = 0;
    int i = 0;
    int skip = 0;

    for (; format[i]; i++) {
        skip = parse_conversion_specifier
            (format + i, &params, ctx);
        if (params.flags < 0)
            return params.flags == -42 ? total_skip + skip : -21;
        if (skip < 1)
            break;
        i += skip - 1;
        total_skip += skip;
    }
    if (!format[i])
        return -42;
    ctx->written = printf_my_putchar('%', ctx) + total_skip + skip;
    printf_my_putstrn(format, total_skip + skip, ctx);
    return total_skip;
}

/**
 * Called for every character in the format string.
 * Prints non-percent characters as-is, and attempts
 * to parse a conversion parameter if the character
 * is a percent sign.
 * @param format the format string
 * @param written a pointer to a size_t holding the already-written bytes count
 * @param ctx a pointer to a context structure holding the printing context
 * @return the number of characters to skip,
 * or a negative value in case of error
 */
int printf_loop_callback(char const *format, size_t *written,
    printf_context_t *ctx)
{
    int skip = 0;

    ctx->written = 0;
    if (*format != '%') {
        printf_my_putchar(*format, ctx);
        (*written) += 1;
        return 0;
    }
    skip = parse_param(ctx, format + 1, written);
    (*written) += ctx->written;
    return skip;
}
