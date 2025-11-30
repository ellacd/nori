#ifndef NORI_UTIL_H
#define NORI_UTIL_H

#include <stdarg.h>
#include <stdio.h>

#include "nori.h"

int32 snprintf(char *s, size_t sz, const char *template, ...);
int32 vsnprintf(char *s, size_t sz, const char *template, va_list args);

#endif
