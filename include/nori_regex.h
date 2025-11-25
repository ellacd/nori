#ifndef NORI_REGEX_H
#define NORI_REGEX_H

#include "nori_str.h"

typedef struct {
  uint64_t low;
  uint64_t high;
} NRegexMask;

// Character class definitions are left public so you know what you're getting.

// \w: matches ASCII letters (upper or lower), digits, and _
static const NRegexMask NREGEX_WORD = {
  0x000000000000FFC0,
  0x7FFFFFE17FFFFFE0
};

// \W: inverse of \w
static const NRegexMask NREGEX_NWORD = {
  ~NREGEX_WORD.low,
  ~NREGEX_WORD.high
};

// \d: digits 0-9
// also referred to by [:digit:]
static const NRegexMask NREGEX_DIGIT = {
  0x000000000000FFC0,
  0x0000000000000000
};

// \D: inverse of \d
static const NRegexMask NREGEX_NDIGIT = {
  ~NREGEX_DIGIT.low,
  ~NREGEX_DIGIT.high
};

// [:xdigit:] Hex digits; equivalent to [0-9A-Fa-f]
static const NRegexMask NREGEX_XDIGIT = {
  NREGEX_DIGIT.low,
  NREGEX_DIGIT.high | 0x7E0000007E000000
};

// \s: whitespace, specifically \s, \t, \v, \r, and \n
// also referred to by [:space:]
static const NRegexMask NREGEX_WHITESPACE = {
  0x0074000080000000,
  0x0000000000000000
};

// \S: not whitespace
// also referred to by [:print:]
static const NRegexMask NREGEX_NWHITESPACE = {
  ~NREGEX_WHITESPACE.low,
  ~NREGEX_WHITESPACE.high
};

// .: excludes newline.
static const NRegexMask NREGEX_DOT = {
  0xFFDFFFFFFFFFFFFF,
  0xFFFFFFFFFFFFFFFF
};

// [:lower:]
static const NRegexMask NREGEX_LOWER = {
  0x0000000000000000,
  0x000000007FFFFFE0
};

// [:upper:]
static const NRegexMask NREGEX_UPPER = {
  0x0000000000000000,
  0x7FFFFFE000000000
};

// [:alpha:]
static const NRegexMask NREGEX_ALPHA = {
  NREGEX_LOWER.low  | NREGEX_UPPER.low,
  NREGEX_LOWER.high | NREGEX_UPPER.high
};

// [:alnum:]
static const NRegexMask NREGEX_ALNUM = {
  NREGEX_DIGIT.low  | NREGEX_ALPHA.low,
  NREGEX_DIGIT.high | NREGEX_ALPHA.high
};

// [:punct:]
static const NRegexMask NREGEX_PUNCT = {
  0x00000000400A0021,
  0x0000000000000000
};

// [:blank:]
static const NRegexMask NREGEX_BLANK = {
  0x0040000080000000,
  0x0000000000000000
};

// [:cntrl:], matches control characters
static const NRegexMask NREGEX_CONTROL = {
  0xFFAFFFFF00000000,
  0x0000000000000001
};

// includes space but only space
static const NRegexMask NREGEX_GRAPH = {
  NREGEX_NWHITESPACE.low | 0x0000000080000000,
  NREGEX_NWHITESPACE.high
};

NStringList *nrx_match(enum NRetCode *ret, const NString *str, const NString *pattern);

#endif
