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
	char name[14];
	unsigned char *data;
};

NList *nlist_create(const char *name, uint16 stride)
{
	return nlist_create_and_alloc(name, stride, 8);
}

NList *nlist_create_and_alloc(const char *name, uint16 stride, uint32 mlen)
{
	uint32 name_len;
	NList *l = malloc(sizeof(*l));

	l->qty = 0;
	l->mlen = mlen;
	l->stride = stride;
	l->data = malloc(stride * l->mlen);
	/* TODO:
	 * It may be worth trimming whitespace & unifying different ways of
	 * writing pointers; e.g. "char[]" and "char*" and "char *"
	 * should really all map to the same place.
	 */
	name_len = strlen(name);
	memcpy(l->name, name, 16 < name_len ? 16 : name_len);
	l->name[name_len - 1] = '\0';
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
	return strcmp(to->name, from->name) == 0;
}

NList *nlist_copy(const NList *l)
{
	NList *l2 = nlist_create_and_alloc(l->name l->stride, l->mlen);
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
	else return &l->data[p * l->stride];
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

void nlist_mergesort(NList *l,
                     int32 (*func_cmp)(const void *e1, const void *e2),
                     void (*func_swap)(void *e1, void *e2))
{
	NList *ptr_stack;
	void *a, *b, *a_iter, *y_iter, *end;
	uint32 half, odd;

	ptr_stack = nlist(void*);
	half = l->qty / 2;
	odd = l->qty % 2;
	a = l->data;
	b = &l->data[(half + odd) * l->stride];
	end = &l->data[l->qty * l->stride];
	/* The smallest call we want to make to merge() is two unsorted
	* lists of two elements each, since sorting the two lists is trivial &
	* not slower than making separate calls to each. For this reason,
	* we only push new markers for pairs containing >= 1 list of size >=3.
	*/
	while (half + odd > 2) {
		printf("half: %d\todd: %d\n", half, odd);
		while (a < end) {
			nlist_push(ptr_stack, a);
			nlist_push(ptr_stack, b);
			printf("Merge pair from %ld to %ld ",
			       ((unsigned char *) a - l->data)/l->stride,
			       ((unsigned char *) b - l->data)/l->stride);
			a = (unsigned char *) b + half * l->stride;
			printf("(end: %ld)\n", ((unsigned char *) a - l->data)/l->stride);
			b = (unsigned char *) a + (half + odd) * l->stride;
		}
	odd = half % 2;
	half = half / 2;
	}

	nlist_destroy(ptr_stack);
}
