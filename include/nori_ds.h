// Rudimentary data structures. Nothing fancy here.
#ifndef NORI_DS_H
#define NORI_DS_H

#include <stdint.h>

#ifndef NORI_INTERNAL_H
typedef void NList;
#endif

#define nlist(t) nlist_create((#t), sizeof(t));
NList *nlist_create(const char *typename, uint16_t stride);
NList *nlist_create_and_alloc(const char *typename, uint16_t stride, uint32_t mlen);
void nlist_alloc(NList *l, uint32_t mlen);
void nlist_destroy(NList *l);
uint32_t nlist_len(const NList *l);
void *nlist_at(const NList *l, uint32_t p);
void nlist_add(NList *l, const void *el);
uint32_t nlist_find(const NList *l, const void *el, _Bool (*func_cmp)(const void *e1, const void *e2));
uint32_t nlist_find_r(const NList *l, const void *el, _Bool (*func_cmp)(const void *e1, const void *e2));
uint32_t nlist_find_from(const NList *l, const void *el,
                         _Bool (*func_cmp)(const void *e1, const void *e2), uint32_t p);
uint32_t nlist_find_r_from(const NList *l, const void *el,
                           _Bool (*func_cmp)(const void *e1, const void *e2), uint32_t p);

_Bool nlist_can_cast(const NList *to, const NList *from);
NList *nlist_copy(const NList *l);
void nlist_append(NList *onto, const NList *from);

#endif
