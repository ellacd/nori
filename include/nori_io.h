#ifndef NORI_IO_H
#define NORI_IO_H

#include "nori_def.h"
#include "nori_str.h"
#include <stddef.h>

// Stream functions.
// "stream" is abbreviated "s" in parameters just in case someone typedef'ed "stream".
#ifndef NORI_IO_INTERNAL
typedef void NStream;
// Xgetc is a pointer to some function that acts like clib's fgetc.
typedef int (*Xgetc) (void *param);
// Xread is a pointer to some function that acts like clib's fread.
typedef size_t (*Xread) (void *param);
#endif
NStream *nio_s_open(Xread func_read, void *param);
void *nio_s_close(NStream *s);
int32_t nio_s_set_buffer_len(NStream *s, int size);
#define nio_s_get_buffer_len(x) nstr_s_set_buffer_len((x),0)

NString *nio_gets(Xgetc func_getc, void *param, char terminator);
void nio_gets_append(NString *str, Xgetc func_getc, void *param, char terminator);
void nio_assign_gets(NString *str, Xgetc func_getc, void *param, char terminator);

void nio_s_read_line(NString *into, NStream *s, char terminator);
void nio_s_read_line_append(NString *onto, NStream *s, char terminator);
void nio_s_read_line_until(NString *into, NStream *s, NString *terminators);
void nio_s_read_line_until_append(NString *onto, NStream *s, NString *terminators);
void nio_s_read_n(NString *into, NStream *s, int32_t n);
void nio_s_read_n_append(NString *onto, NStream *s, int32_t n);
void nio_s_unread(NStream *s, const NString *str);

void nio_s_peek(NString *onto, const NStream *s);
void nio_s_eof(const NStream *s);

void nio_debug(const char *format, ...);

#endif
