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
  return nlist_create_and_alloc(typename, stride, 8);
}

NList *nlist_create_and_alloc(const char *typename, uint16 stride, uint32 mlen)
{
  NList *l = malloc(sizeof(*l));

  l->qty = 0;
  l->mlen = mlen;
  l->stride = stride;
  l->data = malloc(stride * l->mlen);
  memcpy(l->typename, typename, 16);
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

void *nlist_at(const NList *l, uint32 p)
{
  if (p > l->qty - 1) return NULL;
  else return (l->data + p * l->stride);
}

void nlist_insert(NList *l, uint32 p, const void *el)
{
  if (l->qty + 1 >= l->mlen) nlist_alloc(l, l->mlen * 2);  
  memmove(&l->data[(p + 1) * l->stride],
          &l->data[p * l->stride],
          (l->qty - p) * l->stride);
  memcpy(&l->data[p * l->stride], el, l->stride);
}

void nlist_push_back(NList *l, void *el)
{
  if (l->qty + 1 >= l->mlen) nlist_alloc(l, l->mlen * 2);
  memcpy(&l->data[l->qty++ * l->stride], el, l->stride);
}

void *nlist_pop_back(NList *l)
{
  return &l->data[l->qty -= l->stride];
}
