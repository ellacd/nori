/* Rudimentary data structures. Nothing fancy here. */

#ifndef NORI_DS_H
#define NORI_DS_H

#include "nori.h"

#ifndef NORI_INTERNAL_H
typedef void NList;
#endif

#define nlist(t) nlist_of_type(t)
#define nlist_of_type(t) nlist_create((#t), sizeof(t));
NList *	nlist_create(const char *typename, uint16 stride);
NList *	nlist_create_and_alloc(const char *typename, uint16 stride, uint32 mlen);
void 	nlist_alloc(NList *l, uint32 mlen);
void 	nlist_destroy(NList *l);
uint32 	nlist_len(const NList *l);
void 	nlist_add(NList *l, const void *el);
boolean nlist_can_cast(const NList *to, const NList *from);
NList *	nlist_copy(const NList *l);
void 	nlist_append(NList *onto, const NList *from);

/*
 * Accessors/mutators:
 * NLists can pretend to be several data structures, including:
 * - Stack (push()/pop(), alias to push_back()/pop_back())
 * - Array/list (at(), insert())
 * The programmer is trusted to differentiate between these themselves;
 * no checks are made to restrict usage of these functions on any list.
 */

void *	nlist_at(const NList *l, uint32 p);
void nlist_insert(NList *l, uint32 p, const void *el);
#define nlist_push(l,e) nlist_push_back((l),(e))
void 	nlist_push_back(NList *l, void *el);
#define nlist_pop(l) nlist_pop_back((l))
void *	nlist_pop_back(NList *l);

/* Sorting functions.
 * Currently unimplemented.
 */
void nlist_mergesort(NList *l,
                     int32 (*func_cmp)(const void *e1, const void *e2),
                     void (*func_swap)(void *e1, void *e2));

#endif
