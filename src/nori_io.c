#include "bstrlib.h"
#include <stdio.h>

#define NORI_IO_INTERNAL
typedef struct bStream NStream;
typedef bNgetc Xgetc;
typedef bNread Xread;
#include "nori_io.h"

NStream *nio_s_open(Xread func_read, void *param)
{
  return bsopen(func_read, param);
}

void *nio_s_close(NStream *s)
{
  return bsclose(s);
}

int32_t nio_s_set_buffer_len(NStream *s, int size)
{
  return bsbufflength(s, size);
}

NString *nio_gets(Xgetc func_getc, void *param, char terminator)
{
  return bgets(func_getc, param, terminator);
}

void nio_gets_append(NString *str, Xgetc func_getc, void *param, char terminator)
{
  bgetsa(str, func_getc, param, terminator);
}

void nio_assign_gets(NString *str, Xgetc func_getc, void *param, char terminator)
{
  bassigngets(str, func_getc, param, terminator);
}

void nio_s_read_line(NString *into, NStream *s, char terminator)
{
  bsreadln(into, s, terminator);
}

void nio_s_read_line_append(NString *onto, NStream *s, char terminator)
{
  bsreadlna(onto, s, terminator);
}

void nio_s_read_line_until(NString *into, NStream *s, NString *terminators)
{
  bsreadlns(into, s, terminators);
}

void nio_s_read_line_until_append(NString *onto, NStream *s, NString *terminators)
{
  bsreadlnsa(onto, s, terminators);
}

void nio_s_read_n(NString *into, NStream *s, int32_t n)
{
  bsread(into, s, n);
}

void nio_s_read_n_append(NString *onto, NStream *s, int32_t n)
{
  bsreada(onto, s, n);
}

void nio_s_unread(NStream *s, const NString *str)
{
  bsunread(s, str);
}

void nio_s_peek(NString *onto, const NStream *s)
{
  bspeek(onto, s);
}

void nio_s_eof(const NStream *s)
{
  bseof(s);
}

void nio_debug(const char *format, ...)
{
#ifndef NLOG
  va_list va;
  va_start(va, format);
  vprintf(format, va);
  va_end(va);
#endif
  return;
}
