#include <stdint.h>

#include "nori_str.h"

struct ASCIIMask {
  uint64_t low;
  uint64_t high;
};

static struct ASCIIMask char_to_mask(unsigned char c)
{
  struct ASCIIMask mask = {0};
  if (c >= 0x40) {
    mask.high = 0x1 << (0x80 - c);
  } else {
    mask.low = 0x1 << (0x40 - c);
  }
  return mask;
}

#if 0
struct RegexMachine {
  
}

NString *nstr_match(const NString *str, const NString *regex)
{
  
}
#endif
