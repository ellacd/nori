#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NList NList;

#define NORI_INTERNAL_H
#include "nori_ds.h"

struct NList {
  uint32 qty;
  uint32 mlen;
  uint16 stride;
  char typename[16];
  unsigned char *data;
};

NList *nlist_create(const char *typename, uint16 stride)
{
  NList *l = malloc(sizeof(*l));
  l->qty = 0;
  l->mlen = 4;
  l->stride = stride;
  l->data = malloc(stride * l->mlen);
  snprintf(l->typename, 16, "%s", typename);
  l->typename[15] = '\0';
  return l;
}

NList *nlist_create_and_alloc(const char *typename, uint16 stride, uint32 mlen)
{
  NList *l = malloc(sizeof(*l));
  l->qty = 0;
  l->mlen = mlen;
  l->stride = stride;
  l->data = malloc(stride * l->mlen);
  snprintf(l->typename, 16, "%s", typename);
  l->typename[15] = '\0';
  return l;
}

void nlist_alloc(NList *l, uint32 mlen)
{
  unsigned char *new_data;
  if (l->mlen >= mlen) return;

  new_data = realloc(l->data, l->stride * mlen);
  if (!new_data) return;

  l->mlen = mlen;
  l->data = new_data;
}

void nlist_destroy(NList *l)
{
  if (l) {
    if (l->data) {
      free(l->data);
    }
    free(l);
  }
}

uint32 nlist_len(const NList *l)
{
  return l->qty;
}

void *nlist_at(const NList *l, uint32 p)
{
  if (p >= l->qty) return NULL;
  else return (l->data + p * l->stride);
}

void nlist_add(NList *l, const void *el)
{
  if (l->qty + 1 >= l->mlen) nlist_alloc(l, l->mlen * 2);
  memcpy(&l->data[l->qty++ * l->stride], el, l->stride);
}

uint32 nlist_find(const NList *l, const void *el,
                    boolean (*func_is_eq)(const void *e1, const void *e2))
{
  return nlist_find_from(l, el, func_is_eq, 0);
}

uint32 nlist_find_from(const NList *l, const void *el,
                         boolean (*func_is_eq)(const void *e1, const void *e2), uint32 p)
{
  uint32 i;
  uint32 len = nlist_len(l);

  for (i = p; i < len; i++) {
    const void *ei = nlist_at(l, i);
    if (ei && func_is_eq(ei, el) == 0) {
      return i;
    }
  }

  return -1;
}

uint32 nlist_find_r(const NList *l, const void *el,
                      boolean (*func_is_eq)(const void *e1, const void *e2))
{
  return nlist_find_r_from(l, el, func_is_eq, nlist_len(l) - 1);
}

uint32 nlist_find_r_from(const NList *l, const void *el,
                           boolean (*func_is_eq)(const void *e1, const void *e2), uint32 p)
{
  uint32 i;

  for (i = p; i >= 0; i--) {
    const void *ei = nlist_at(l, i);
    if (ei && func_is_eq(ei, el) == 0) {
      return i;
    }
  }

  return -1;
}

boolean nlist_can_cast(const NList *to, const NList *from)
{
  return strcmp(to->typename, from->typename) == 0;
}

NList *nlist_copy(const NList *l)
{
  NList *l2 = nlist_create_and_alloc(l->typename, l->stride, l->mlen);
  l2->qty = l->qty;
  memcpy(l2->data, l->data, l->qty * l->stride);
  return l2;
}

void nlist_append(NList *onto, const NList *from)
{
  nlist_alloc(onto, onto->mlen + from->mlen);
  memcpy(onto->data + onto->qty * onto->stride,
    from->data, from->qty * from->stride);
  onto->qty += from->qty;
}

