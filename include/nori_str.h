// Nori (String):
// Ella's string function wrapper.
// For complaints, email ella.lr.duncan@gmail.com
//
// This header wraps Paul Hsieh's bstrlib.
// Please see LICENSE for relevant copyright information.
#ifndef NORI_STR_H
#define NORI_STR_H

#include "nori_def.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#ifndef NORI_STR_INTERNAL
typedef void NString;
typedef void NStringList;
#endif

// Constructors (C strings)
NString *nstr_from_cstr(const char *str);
NString *nstr_from_cstr_min_alloc(int32_t mlen, const char *str);
NString *nstr_from_cstr_range_alloc(int32_t minl, int32_t maxl, const char *str);
NString *nstr_from_block(const void *block, int32_t len);

// Constructors (N strings)
#define nstr_copy(n) nstr_from_nstr((n))
NString *nstr_from_nstr(const NString *str);
#define nstr_mid(n,p,l) nstr_from_mid((n),(p),(l))
NString *nstr_from_mid(const NString *str, int32_t left, int32_t len);
enum NRetCode nstr_assign(NString *str1, const NString *str2);
enum NRetCode nstr_assign_mid(NString *str1, const NString *str2, uint32_t left, uint32_t len);
enum NRetCode nstr_assign_cstr(NString *str, const char *cstr);
enum NRetCode nstr_assign_block(NString *str, const void *block, int32_t len);

// Convert back to c string
char *nstr_to_cstr(const NString *str, char z);
enum NRetCode nstr_cstr_free(char *str);

// Destructor
enum NRetCode nstr_destroy(NString *str);

// Plain Old Accessors
int32_t nstr_len(const NString *str);
char nstr_char_at(const NString *str, int32_t pos);
char *nstr_data(NString *str);
char *nstr_data_offset(NString *str, int32_t offset);

// Allocation mutators
enum NRetCode nstr_alloc(NString *str, int32_t len);
enum NRetCode nstr_alloc_min(NString *str, int32_t len);

// Manipulation
enum NRetCode nstr_concat(NString *str1, const NString *str2);
enum NRetCode nstr_concat_char(NString *str, char c);
enum NRetCode nstr_concat_cstr(NString *str, const char *cstr);
enum NRetCode nstr_concat_block(NString *str, const void *block, int32_t len);
enum NRetCode nstr_insert(NString *str1, int32_t pos, const NString *str2, unsigned char fill);
enum NRetCode nstr_insert_block(NString *str, int32_t pos, const void *block, int32_t len, unsigned char fill);
enum NRetCode nstr_insert_char(NString *str, int32_t pos, int32_t len, unsigned char fill);
enum NRetCode nstr_replace(NString *str1, int32_t pos, int32_t len, const NString *str2, unsigned char fill);
enum NRetCode nstr_delete(NString *str, int32_t pos, int32_t len);
enum NRetCode nstr_set_str(NString *str1, int32_t pos, const NString *str2, unsigned char fill);
enum NRetCode nstr_truncate(NString *str, int32_t n);

// strcmp drop-in replacements
int32_t nstr_cmp(const NString *str1, const NString *str2);
int32_t nstr_cmp_n(const NString *str1, const NString *str2, int32_t n);
int32_t nstr_cmp_caseless(const NString *str1, const NString *str2);
int32_t nstr_cmp_n_caseless(const NString *str1, const NString *str2, int32_t n);

// String equality checks. Use instead of strcmp where possible
enum NRetCode nstr_is_eq(const NString *str1, const NString *str2);
enum NRetCode nstr_is_eq_caseless(const NString *str1, const NString *str2);
enum NRetCode nstr_is_eq_cstr(const NString *str, const char *cstr);
enum NRetCode nstr_is_eq_cstr_caseless(const NString *str, const char *cstr);
enum NRetCode nstr_is_eq_block(const NString *str, const void *block, int32_t len);
enum NRetCode nstr_is_eq_block_caseless(const NString *str, const void *block, int32_t len);
enum NRetCode nstr_is_stem_eq_block(const NString *str, const void *block, int32_t len);
enum NRetCode nstr_is_stem_eq_block_caseless(const NString *str, const void *block, int32_t len);

// Substring queries
int32_t nstr_in_str(const NString *str1, int32_t pos, const NString *str2);
int32_t nstr_in_str_reverse(const NString *str1, int32_t pos, const NString *str2);
int32_t nstr_in_str_caseless(const NString *str1, int32_t pos, const NString *str2);
int32_t nstr_in_str_reverse_caseless(const NString *str1, int32_t pos, const NString *str2);
int32_t nstr_find_char_from_pos(const NString *str, char c, int32_t pos);
int32_t nstr_find_char_from_pos_reverse(const NString *str, char c, int32_t pos);
int32_t nstr_first_of(const NString *str, int32_t pos, const NString *allowlist);
int32_t nstr_last_of(const NString *str, int32_t pos, const NString *allowlist);
int32_t nstr_first_of_not(const NString *str, int32_t pos, const NString *denylist);
int32_t nstr_last_of_not(const NString *str, int32_t pos, const NString *denylist);
int32_t nstr_find_replace(NString *str, const NString *find, const NString *repl, int32_t pos);
int32_t nstr_find_replace_caseless(NString *str, const NString *find, const NString *repl, int32_t pos);

// List functions
NStringList *nstr_list_create(void);
enum NRetCode nstr_list_destroy(NStringList *sl);
enum NRetCode nstr_list_alloc(NStringList *sl, int min_size);
enum NRetCode nstr_list_alloc_qty(NStringList *sl, int min_qty);
NString *nstr_list_at(const NStringList *list, int32_t index);
enum NRetCode nstr_list_append(NStringList *list, NString *str);

// Tokenizer
NStringList *nstr_split(const NString *str, unsigned char split);
NStringList *nstr_splits(const NString *str, const NString *splits);
NStringList *nstr_split_string(const NString *str, const NString *split);
NString *nstr_join(const NStringList *sl, const NString *separator);
NString *nstr_join_block(const NStringList *sl, const void *block, int32_t len);
enum NRetCode nstr_split_callback(const NString *str, unsigned char split, int32_t pos,
  int32_t (*func_callback)(void *param, int32_t offset, int32_t len), void *param);
enum NRetCode nstr_splits_callback(const NString *str, const NString *splits, int32_t pos,
  int32_t (*func_callback)(void *param, int32_t offset, int32_t len), void *param);
enum NRetCode nstr_split_string_callback(const NString *str, const NString *split, int32_t pos,
  int32_t (*func_callback)(void *param, int32_t offset, int32_t len), void *param);

// Format
enum NRetCode nstr_pattern(NString *str, int32_t len);
enum NRetCode nstr_to_upper(NString *str);
enum NRetCode nstr_to_lower(NString *str);
enum NRetCode nstr_trim_whitespace_left(NString *str);
enum NRetCode nstr_trim_whitespace_right(NString *str);
enum NRetCode nstr_trim_whitespace(NString *str);

// sprintf drop-in replacements
NString *nstr_format(const char *format, ...);
enum NRetCode nstr_format_append(NString *str, const char *format, ...);
enum NRetCode nstr_assign_format(NString *str, const char *format, ...);
enum NRetCode nstr_vaformat(NString *str, uint32_t count, const char *format, va_list va);

uint32_t nstr_to_uint(const NString *str);

// For now, these use code from bstrlib!
#define nstr_static_mlen(q,m) {(m), (int) sizeof(q)-1, (unsigned char *) ("" q "")}
#define nstr_static(q) nstr_static_mlen(q,-32)
#define nstr_static_block_params(q) ((void *)("" q "")), ((int) sizeof(q)-1)
#define nstr_from_static(s) ((nstr_from_block)(nstr_static_block_params(s)))
#define nstr_assign_static(n,s) ((nstr_assign_block)((n), nstr_static_block_params(s)))
#define nstr_concat_static(n,s) ((nstr_concat_block)((n), nstr_static_block_params(s)))
#define nstr_insert_static(n,p,s,f) ((nstr_insert_block)((n), (p), nstr_static_block_params(s),(f)))
#define nstr_is_eq_static(n,s) ((nstr_is_eq_block)((n), nstr_static_block_params(s)))
#define nstr_is_eq_static_caseless(n,s) ((nstr_is_eq_block_caseless)((n), nstr_static_block_params(s)))
#define nstr_is_stem_eq_static(n,s) ((nstr_is_stem_eq_block)((n), nstr_static_block_params(s)))
#define nstr_is_stem_eq_static_caseless(n,s) ((nstr_is_stem_eq_block_caseless)((n), nstr_static_block_params(s)))
#define nstr_join_static(n,s) ((nstr_join_block)((n), nstr_static_block_params(s)))
#define nstr_find_char(str,ch) nstr_find_char_from_pos((str), (ch), 0)
#define nstr_find_char_reverse(str,ch) nstr_find_char_from_pos_reverse((str), (ch), nstr_len(str)-1)

#endif
