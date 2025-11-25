#ifndef NORI_DEF_H
#define NORI_DEF_H

enum NRetCode {
  NORI_ERR = -1,
  NORI_OK = 0,
  NORI_EOF = 1,
  NORI_EQ = 1,
  NORI_NEQ = 0
};

#define ARRAY_LENGTH(x) (sizeof((x))/sizeof((x)[0]))
#endif
