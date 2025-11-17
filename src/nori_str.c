#include <stdint.h>
#include "nori_def.h"

// Currently, this is implemented in terms of bstrlib.
// bstrlib is by Paul Hsieh, (c) 2015; see LICENSE.
#include "bstrlib.h"

typedef struct tagbstring NString;
typedef struct bstrList NStringList;

#define NORI_STR_INTERNAL
#include "nori_str.h"


NString *nstr_from_cstr(const char *str)
{
  return bfromcstr(str);
}

NString *nstr_from_cstr_min_alloc(int32_t mlen, const char *str)
{
  return bfromcstralloc(mlen, str);
}

NString *nstr_from_cstr_range_alloc(int32_t minl, int32_t maxl, const char *str)
{
  return bfromcstrrangealloc(minl, maxl, str);
}

NString *nstr_from_block(const void *block, int32_t len)
{
  return blk2bstr(block, len);
}

char *nstr_to_cstr(const NString *str, char z)
{
  return bstr2cstr((bstring) str, z);
}

enum NRetCode nstr_cstr_free(char *str)
{
  return (enum NRetCode) bcstrfree(str);
}

// Constructors (N strings)
NString *nstr_copy(const NString *str)
{
  return bstrcpy(str);
}

NString *nstr_mid(const NString *str, int32_t left, int32_t len)
{
  return bmidstr(str, left, len);
}

enum NRetCode nstr_assign(NString *str1, const NString *str2)
{
  return bassign(str1, str2);
}

enum NRetCode nstr_assign_mid(NString *str1, const NString *str2, uint32_t left, uint32_t len)
{
  return bassignmidstr(str1, str2, left, len);
}

enum NRetCode nstr_assign_cstr(NString *str, const char *cstr)
{
  return bassigncstr(str, cstr);
}

enum NRetCode nstr_assign_block(NString *str, const void *block, int32_t len)
{
  return bassignblk(str, block, len);
}

// Constructors (Static string literals)
// TODO: this

// Destructor
enum NRetCode nstr_destroy(NString *str)
{
  return bdestroy(str);
}

// Allocation mutators
enum NRetCode nstr_alloc(NString *str, int32_t len)
{
  return balloc(str, len);
}

enum NRetCode nstr_alloc_min(NString *str, int32_t len)
{
  return ballocmin(str, len);
}

// Manipulation
enum NRetCode nstr_concat(NString *str1, const NString *str2)
{
  return bconcat(str1, str2);
}

enum NRetCode nstr_concat_char(NString *str, char c)
{
  return bconchar(str, c);
}

enum NRetCode nstr_concat_cstr(NString *str, const char *cstr)
{
  return bcatcstr(str, cstr);
}

enum NRetCode nstr_concat_block(NString *str, const void *block, int32_t len)
{
  return bcatblk(str, block, len);
}

enum NRetCode nstr_insert(NString *str1, int32_t pos, const NString *str2, unsigned char fill)
{
  return binsert(str1, pos, str2, fill);
}

enum NRetCode nstr_insert_block(NString *str, int32_t pos, const void *block, int32_t len, unsigned char fill)
{
  return binsertblk(str, pos, block, len, fill);
}

enum NRetCode nstr_insert_char(NString *str, int32_t pos, int32_t len, unsigned char fill)
{
  return binsertch(str, pos, len, fill);
}

enum NRetCode nstr_replace(NString *str1, int32_t pos, int32_t len, const NString *str2, unsigned char fill)
{
  return breplace(str1, pos, len, str2, fill);
}

enum NRetCode nstr_delete(NString *str, int32_t pos, int32_t len)
{
  return bdelete(str, pos, len);
}

enum NRetCode nstr_set_str(NString *str1, int32_t pos, const NString *str2, unsigned char fill)
{
  return bsetstr(str1, pos, str2, fill);
}

enum NRetCode nstr_truncate(NString *str, int32_t n)
{
  return btrunc(str, n);
}

// string.h drop-in replacements
int32_t nstr_cmp(const NString *str1, const NString *str2)
{
  return bstrcmp(str1, str2);
}

int32_t nstr_cmp_n(const NString *str1, const NString *str2, int32_t n)
{
  return bstrncmp(str1, str2, n);
}

int32_t nstr_cmp_caseless(const NString *str1, const NString *str2)
{
  return bstricmp(str1, str2);
}

int32_t nstr_cmp_n_caseless(const NString *str1, const NString *str2, int32_t n)
{
  return bstrnicmp(str1, str2, n);
}

// Plain Old Accessors
int32_t nstr_len(const NString *str)
{
  return blength(str);
}

char nstr_char_at(const NString *str, int32_t pos)
{
  return bchar(str, pos);
}

char *nstr_data(NString *str)
{
  return bdata(str);
}

char *nstr_data_offset(NString *str, int32_t offset)
{
  return bdataofs(str, offset);
}

// String equality checks. Use instead of strcmp where possible
enum NRetCode nstr_is_eq(const NString *str1, const NString *str2)
{
  return biseq(str1, str2);
}

enum NRetCode nstr_is_eq_caseless(const NString *str1, const NString *str2)
{
  return biseqcaseless(str1, str2);
}

enum NRetCode nstr_is_eq_cstr(const NString *str, const char *cstr)
{
  return biseqcstr(str, cstr);
}

enum NRetCode nstr_is_eq_cstr_caseless(const NString *str, const char *cstr)
{
  return biseqcstrcaseless(str, cstr);
}

enum NRetCode nstr_is_eq_block(const NString *str, const void *block, int32_t len)
{
  return biseqblk(str, block, len);
}

enum NRetCode nstr_is_eq_block_caseless(const NString *str, const void *block, int32_t len)
{
  return biseqcaselessblk(str, block, len);
}

enum NRetCode nstr_is_stem_eq_block(const NString *str, const void *block, int32_t len)
{
  return bisstemeqblk(str, block, len);
}

enum NRetCode nstr_is_stem_eq_block_caseless(const NString *str, const void *block, int32_t len)
{
  return bisstemeqcaselessblk(str, block, len);
}

// Substring queries
int32_t nstr_in_str(const NString *str1, int32_t pos, const NString *str2)
{
  return binstr(str1, pos, str2);
}

int32_t nstr_in_str_reverse(const NString *str1, int32_t pos, const NString *str2)
{
  return binstrr(str1, pos, str2);
}

int32_t nstr_in_str_caseless(const NString *str1, int32_t pos, const NString *str2)
{
  return binstrcaseless(str1, pos, str2);
}

int32_t nstr_in_str_reverse_caseless(const NString *str1, int32_t pos, const NString *str2)
{
  return binstrrcaseless(str1, pos, str2);
}

int32_t nstr_find_char_from_pos(const NString *str, char c, int32_t pos)
{
  return bstrchrp(str, c, pos);
}

int32_t nstr_find_char_from_pos_reverse(const NString *str, char c, int32_t pos)
{
  return bstrrchrp(str, c, pos);
}

int32_t nstr_first_of(const NString *str, int32_t pos, const NString *allowlist)
{
  return binchr(str, pos, allowlist);
}

int32_t nstr_last_of(const NString *str, int32_t pos, const NString *allowlist)
{
  return binchrr(str, pos, allowlist);
}

int32_t nstr_first_of_not(const NString *str, int32_t pos, const NString *denylist)
{
  return bninchr(str, pos, denylist);
}

int32_t nstr_last_of_not(const NString *str, int32_t pos, const NString *denylist)
{
  return bninchrr(str, pos, denylist);
}

int32_t nstr_find_replace(NString *str, const NString *find, const NString *repl, int32_t pos)
{
  return bfindreplace(str, find, repl, pos);
}

int32_t nstr_find_replace_caseless(NString *str, const NString *find, const NString *repl, int32_t pos)
{
  return bfindreplacecaseless(str, find, repl, pos);
}

// List functions
NStringList *nstr_list_create(void)
{
  return bstrListCreate();
}

enum NRetCode nstr_list_destroy(NStringList *sl)
{
  return bstrListDestroy(sl);
}

enum NRetCode nstr_list_alloc(NStringList *sl, int min_size)
{
  return bstrListAlloc(sl, min_size);
}

enum NRetCode nstr_list_alloc_qty(NStringList *sl, int min_qty)
{
  return bstrListAllocMin(sl, min_qty);
}

NString *nstr_list_at(const NStringList *sl, int32_t index)
{
  if (sl == NULL || sl->entry == NULL || sl->qty < 0 || sl->mlen <= 0 ||
      sl->qty > sl ->mlen || index > sl->qty - 1) {
    return NULL;
  }

  return sl->entry[index];
}

enum NRetCode nstr_list_append(NStringList *sl, NString *str)
{
  if (sl == NULL || sl->entry == NULL || sl->qty < 0 || sl->mlen <= 0 ||
      sl->qty > sl ->mlen) {
    return NULL;
  } else if (str == NULL || str->data == NULL || str->slen < 0 ||
             str->mlen <= 0 || str->slen > str->mlen ) {
    return NULL;
  }

  nstr_list_alloc(sl, sl->qty + 1);
  if (sl) {
    sl->entry[sl->qty] = str;
    sl->qty++;
    return NORI_OK;
  } else {
    return NORI_ERR;
  }
}

// Tokenizer
NStringList *nstr_split(const NString *str, unsigned char split)
{
  return bsplit(str, split);
}

NStringList *nstr_splits(const NString *str, const NString *splits)
{
  return bsplits(str, splits);
}

NStringList *nstr_split_string(const NString *str, const NString *split)
{
  return bsplitstr(str, split);
}

NString *nstr_join(const NStringList *sl, const NString *separator)
{
  return bjoin(sl, separator);
}

NString *nstr_join_block(const NStringList *sl, const void *block, int32_t len)
{
  return bjoinblk(sl, block, len);
}

enum NRetCode nstr_split_callback(const NString *str, unsigned char split, int32_t pos,
                                  int32_t (*func_callback)(void *param, int32_t offset, int32_t len),
                                  void *param)
{
  return bsplitcb(str, split, pos, func_callback, param);
}

enum NRetCode nstr_splits_callback(const NString *str, const NString *splits, int32_t pos,
                                   int32_t (*func_callback)(void *param, int32_t offset, int32_t len),
                                   void *param)
{
  return bsplitscb(str, splits, pos, func_callback, param);
}

enum NRetCode nstr_split_string_callback(const NString *str, const NString *split, int32_t pos,
                                   int32_t (*func_callback)(void *param, int32_t offset, int32_t len),
                                   void *param)
{
  return bsplitstrcb(str, split, pos, func_callback, param);
}

// Format
enum NRetCode nstr_pattern(NString *str, int32_t len)
{
  return bpattern(str, len);
}

enum NRetCode nstr_to_upper(NString *str)
{
  return btoupper(str);
}

enum NRetCode nstr_to_lower(NString *str)
{
  return btolower(str);
}

enum NRetCode nstr_trim_whitespace_left(NString *str)
{
  return bltrimws(str);
}

enum NRetCode nstr_trim_whitespace_right(NString *str)
{
  return brtrimws(str);
}

enum NRetCode nstr_trim_whitespace(NString *str)
{
  return brtrimws(str);
}

// sprintf drop-in replacements
NString *nstr_format(const char *format, ...)
{
  enum NRetCode ret;
  NString *str = bfromcstr("");
  bvformata(ret, str, format, format);
  if (ret == NORI_OK) {
    return str;
  } else {
    return NULL;
  }
}

enum NRetCode nstr_format_append(NString *str, const char *format, ...)
{
  enum NRetCode ret;
  bvformata(ret, str, format, format);
  return ret;
}

enum NRetCode nstr_assign_format(NString *str, const char *format, ...)
{
   enum NRetCode ret;
   nstr_destroy(str);
   str = nstr_from_cstr("");
   bvformata(ret, str, format, format);
   return ret;
}

// Regex: see nori_str_regex.c
