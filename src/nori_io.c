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

enum NRetCode nio_gets_append(NString *str, Xgetc func_getc, void *param, char terminator)
{
  return bgetsa(str, func_getc, param, terminator);
}

enum NRetCode nio_assign_gets(NString *str, Xgetc func_getc, void *param, char terminator)
{
  return bassigngets(str, func_getc, param, terminator);
}

enum NRetCode nio_s_read_line(NString *into, NStream *s, char terminator)
{
  return bsreadln(into, s, terminator);
}

enum NRetCode nio_s_read_line_append(NString *onto, NStream *s, char terminator)
{
  return bsreadlna(onto, s, terminator);
}

enum NRetCode nio_s_read_line_until(NString *into, NStream *s, NString *terminators)
{
  return bsreadlns(into, s, terminators);
}

enum NRetCode nio_s_read_line_until_append(NString *onto, NStream *s, NString *terminators)
{
  return bsreadlnsa(onto, s, terminators);
}

enum NRetCode nio_s_read_n(NString *into, NStream *s, int32_t n)
{
  return bsread(into, s, n);
}

enum NRetCode nio_s_read_n_append(NString *onto, NStream *s, int32_t n)
{
  return bsreada(onto, s, n);
}

enum NRetCode nio_s_unread(NStream *s, const NString *str)
{
  return bsunread(s, str);
}

enum NRetCode nio_s_peek(NString *onto, const NStream *s)
{
  return bspeek(onto, s);
}

enum NRetCode nio_s_eof(const NStream *s)
{
  return bseof(s);
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
