#ifndef NORI_H
#define NORI_H

#include <stdarg.h>
#include <stddef.h>

#ifndef NULL
#define NULL	((void *)0)
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#if __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#include <stdint.h>
typedef int8_t							int8;
typedef uint8_t							uint8;
typedef int16_t							int16;
typedef uint16_t						uint16;
typedef int32_t							int32;
typedef uint32_t						uint32;
typedef int64_t							int64;
typedef uint64_t						uint64;
#else
typedef signed char 		    int8;
typedef unsigned char 	    uint8;
typedef signed short 		    int16;
typedef unsigned short 	    uint16;
typedef signed int 			    int32;
typedef unsigned int 		    uint32;
typedef signed long long 	  int64;
typedef unsigned long long 	uint64;
#endif
typedef float 				      real32;
typedef double 				      real64;
typedef unsigned char 		  boolean;

#define ARRAY_LENGTH(x) (sizeof((x))/sizeof((x)[0]))

// Useful data structures that I have to reimplement often
#if !defined(NORI_DS)
typedef void NList;
#endif

#define nlist(t) nlist_of_type(t)
#define nlist_of_type(t) nlist_create((#t), sizeof(t));
NList *	nlist_create(const char *name, uint16 stride);
NList *	nlist_create_and_alloc(const char *name, uint16 stride, uint32 mlen);
void    nlist_alloc(NList *l, uint32 mlen);
void    nlist_destroy(NList *l);
uint32 	nlist_len(const NList *l);
boolean nlist_can_cast(const NList *to, const NList *from);
NList *	nlist_copy(const NList *l);
void    nlist_append(NList *onto, const NList *from);

/*
 * Accessors/mutators:
 * NLists can pretend to be several data structures, including:
 * - Stack (push()/pop(), alias to push_back()/pop_back())
 * - Array/list (at(), insert())
 * The programmer is trusted to differentiate between these themselves;
 * no checks are made to restrict usage of these functions on any list.
 */

void *	nlist_at(const NList *l, uint32 p);
void    nlist_insert(NList *l, uint32 p, const void *el);
#define nlist_push(l,e) nlist_push_back((l),(e))
void    nlist_push_back(NList *l, void *el);
#define nlist_pop(l) nlist_pop_back((l))
void *	nlist_pop_back(NList *l);

#endif
