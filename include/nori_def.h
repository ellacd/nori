#ifndef NORI_DEF_H
#define NORI_DEF_H

#define NULL	((void *)0)

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
#endif
