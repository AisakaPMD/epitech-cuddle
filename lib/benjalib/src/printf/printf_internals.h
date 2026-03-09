/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** My Printf Internals Header File
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#ifndef PRINTF_INTERNALS_H
    #define PRINTF_INTERNALS_H
    #include <stdarg.h>
    #include "benjalib/my_printf.h"
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #define STRBUF_SIZE 1024


    #ifndef EPITECH_RESTRICTED
        #define MYPRINTF_ERR_STR strerror(errno)
    #else
        #define MYPRINTF_ERR_STR "Err info not available"
    #endif




// Structures

struct printf_string_buffer_s;
typedef struct printf_string_buffer_s printf_string_buffer_t;

struct printf_string_buffer_s {
    char str[STRBUF_SIZE];
    size_t pos;
    printf_string_buffer_t *next;
};

typedef struct printf_context_s {
    char errored;
    char outputs;
    int fd;
    va_list args;
    printf_string_buffer_t *buffer;
    size_t written;
    size_t limit;
} printf_context_t;

typedef struct printf_render_params_s {
    int flags;
    char conversion_specifier;
    int length_modifier;
    int precision;
    int field_width;
    int is_cap;
    size_t written;
    int zeroes_padding;
} printf_render_params_t;

typedef struct printf_conversion_specifier_s {
    char identifier;
    int (*callback)(printf_render_params_t *, printf_context_t *ctx);
    char is_int;
} printf_conv_specifier_t;

typedef struct printf_length_modifier_s {
    char identifier[3];
    int value;
} printf_len_modifier_t;

// Enums

enum printf_render_flags {
    RF_ALTERNATE_FORM = 1 << 0,
    RF_ZERO_PADDED = 1 << 1,
    RF_ADJUST_LEFT = 1 << 2,
    RF_SPACE = 1 << 3,
    RF_SIGN = 1 << 4
};

// Internal functions

int printf_exp_hex(printf_render_params_t *params, printf_context_t *ctx);
int printf_bin(printf_render_params_t *params, printf_context_t *ctx);
int printf_char(printf_render_params_t *params, printf_context_t *ctx);
int printf_decimal(printf_render_params_t *params, printf_context_t *ctx);
int printf_exponent(printf_render_params_t *params, printf_context_t *ctx);
int printf_float(printf_render_params_t *params, printf_context_t *ctx);
int printf_hybrid(printf_render_params_t *params, printf_context_t *ctx);
int printf_merror(printf_render_params_t *params, printf_context_t *ctx);
int printf_written(printf_render_params_t *params, printf_context_t *ctx);
int printf_octal(printf_render_params_t *params, printf_context_t *ctx);
int printf_ptr(printf_render_params_t *params, printf_context_t *ctx);
int printf_str(printf_render_params_t *params, printf_context_t *ctx);
int printf_unsigned(printf_render_params_t *params, printf_context_t *ctx);
int printf_hex(printf_render_params_t *params, printf_context_t *ctx);

unsigned long long printf_get_sized_uint(va_list arg, int flagValue);
long long printf_get_sized_int(va_list arg, int flagValue);
ssize_t printf_write_sign_prefix(char isneg,
    printf_render_params_t *params, printf_context_t *ctx);
int printf_print_invalid_double
(double d, char cap, printf_context_t *ctx, int *written);

int printf_print_unsigned(unsigned long long abs, printf_context_t *ctx,
    char const *base, int precision);

int printf_loop_callback(char const *format, size_t *written,
    struct printf_context_s *ctx);
int printf_my_put_nbr(long long nb, printf_context_t *ctx);
ssize_t printf_my_putchar(int c, printf_context_t *ctx);
int printf_my_putstr(char const *str, printf_context_t *ctx);
int printf_my_putstrn(char const *str, int n, printf_context_t *ctx);
int printf_my_strlen(char const *str);
int printf_my_getnbr(char const *str);
unsigned long long printf_my_unsigned_compute_power_it(
    unsigned long long nb, unsigned int power);
int printf_my_strncmp(char const *s1, char const *s2, int n);
int printf_my_putnbr_base(long long nbr, char const *base,
    printf_context_t *ctx);
int printf_my_char_isupper(char c);
int printf_my_big_putnbr(long long value, printf_context_t *ctx);
int printf_my_big_putnbr_base(unsigned long long value,
    char const *base, printf_context_t *ctx);
long int printf_my_get_unsigned_nbr(char const *str,
    int *skip, char allowZero);
int printf_my_putdouble(double d, printf_context_t *ctx,
    double *part_entiere);
double printf_my_modf(double number, double mod);
ssize_t printf_printf_my_strbuf_write(printf_string_buffer_t *buf, int c);

// String Buffer utils
void printf_my_strbuf_get(char *dst, printf_string_buffer_t *strbuf);
size_t printf_my_strbuf_len(printf_string_buffer_t *buf);
void printf_my_strbuf_free(printf_string_buffer_t *buf);
ssize_t printf_printf_my_strbuf_write(printf_string_buffer_t *buf, int c);
printf_string_buffer_t *printf_my_strbuf_init(void);

// Runtime constants

static const printf_conv_specifier_t printf_conversion_specifiers[] = {
    {'a', &printf_exp_hex, 0},
    {'b', &printf_bin, 1},
    {'c', &printf_char, 1},
    {'d', &printf_decimal, 1},
    {'e', &printf_exponent, 0},
    {'f', &printf_float, 0},
    {'g', &printf_hybrid, 0},
    {'i', &printf_decimal, 1},
    {'m', &printf_merror, 1},
    {'n', &printf_written, 0},
    {'o', &printf_octal, 1},
    {'p', &printf_ptr, 1},
    {'s', &printf_str, 1},
    {'u', &printf_unsigned, 1},
    {'x', &printf_hex, 1},
    {0, NULL, 0}
};

static const printf_len_modifier_t printf_length_modifiers[] = {
    {"ll", 8},
    {"hh", 1},
    {"l", 4},
    {"h", 2},
    {"q", 8},
    {"L", 9},
    {"j", 10},
    {"z", 11},
    {"Z", 11},
    {"t", 12},
    {"", 0}
};

#endif
