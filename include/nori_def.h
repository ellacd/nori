#ifndef NORI_DEF_H
#define NORI_DEF_H

#define NULL	((void *)0)

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef signed char 		    int8;
typedef unsigned char 	    uint8;
typedef signed short 		    int16;
typedef unsigned short 	    uint16;
typedef signed int 			    int32;
typedef unsigned int 		    uint32;
typedef signed long long 	  int64;
typedef unsigned long long 	uint64;
typedef float 				      real32;
typedef double 				      real64;
typedef unsigned char 		  boolean;

#define ARRAY_LENGTH(x) (sizeof((x))/sizeof((x)[0]))
#endif
