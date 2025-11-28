#include <stdarg.h>
#include <stdint.h>

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

void  nstr_cstr_free(char *str)
{
	bcstrfree(str);
}

// Constructors (N strings)
NString *nstr_from_nstr(const NString *str)
{
	return bstrcpy(str);
}

NString *nstr_from_mid(const NString *str, int32_t left, int32_t len)
{
	return bmidstr(str, left, len);
}

void nstr_assign(NString *str1, const NString *str2)
{
	bassign(str1, str2);
}

void nstr_assign_mid(NString *str1, const NString *str2, uint32_t left, uint32_t len)
{
	bassignmidstr(str1, str2, left, len);
}

void nstr_assign_cstr(NString *str, const char *cstr)
{
	bassigncstr(str, cstr);
}

void nstr_assign_block(NString *str, const void *block, int32_t len)
{
	bassignblk(str, block, len);
}

// Constructors (Static string literals)
// TODO: this

// Destructor
void nstr_destroy(NString *str)
{
	bdestroy(str);
}

// Allocation mutators
void nstr_alloc(NString *str, int32_t len)
{
	balloc(str, len);
}

void nstr_alloc_min(NString *str, int32_t len)
{
	ballocmin(str, len);
}

// Manipulation
void nstr_concat(NString *str1, const NString *str2)
{
	bconcat(str1, str2);
}

void nstr_concat_char(NString *str, char c)
{
	bconchar(str, c);
}

void nstr_concat_cstr(NString *str, const char *cstr)
{
	bcatcstr(str, cstr);
}

void nstr_concat_block(NString *str, const void *block, int32_t len)
{
	bcatblk(str, block, len);
}

void nstr_insert(NString *str1, int32_t pos, const NString *str2, unsigned char fill)
{
	binsert(str1, pos, str2, fill);
}

void nstr_insert_block(NString *str, int32_t pos, const void *block, int32_t len, unsigned char fill)
{
	binsertblk(str, pos, block, len, fill);
}

void nstr_insert_char(NString *str, int32_t pos, int32_t len, unsigned char fill)
{
	binsertch(str, pos, len, fill);
}

void nstr_replace(NString *str1, int32_t pos, int32_t len, const NString *str2, unsigned char fill)
{
	breplace(str1, pos, len, str2, fill);
}

void nstr_delete(NString *str, int32_t pos, int32_t len)
{
	bdelete(str, pos, len);
}

void nstr_set_str(NString *str1, int32_t pos, const NString *str2, unsigned char fill)
{
	bsetstr(str1, pos, str2, fill);
}

void nstr_truncate(NString *str, int32_t n)
{
	btrunc(str, n);
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
boolean nstr_is_eq(const NString *str1, const NString *str2)
{
	return biseq(str1, str2);
}

boolean nstr_is_eq_caseless(const NString *str1, const NString *str2)
{
	return biseqcaseless(str1, str2);
}

boolean nstr_is_eq_cstr(const NString *str, const char *cstr)
{
	return biseqcstr(str, cstr);
}

boolean nstr_is_eq_cstr_caseless(const NString *str, const char *cstr)
{
	return biseqcstrcaseless(str, cstr);
}

boolean nstr_is_eq_block(const NString *str, const void *block, int32_t len)
{
	return biseqblk(str, block, len);
}

boolean nstr_is_eq_block_caseless(const NString *str, const void *block, int32_t len)
{
	return biseqcaselessblk(str, block, len);
}

boolean nstr_is_stem_eq_block(const NString *str, const void *block, int32_t len)
{
	return bisstemeqblk(str, block, len);
}

boolean nstr_is_stem_eq_block_caseless(const NString *str, const void *block, int32_t len)
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

void nstr_list_destroy(NStringList *sl)
{
	bstrListDestroy(sl);
}

void nstr_list_alloc(NStringList *sl, int min_size)
{
	bstrListAlloc(sl, min_size);
}

void nstr_list_alloc_qty(NStringList *sl, int min_qty)
{
	bstrListAllocMin(sl, min_qty);
}

NString *nstr_list_at(const NStringList *sl, int32_t index)
{
	if (sl == NULL || sl->entry == NULL || sl->qty < 0 || sl->mlen <= 0 ||
		sl->qty > sl ->mlen || index > sl->qty - 1) {
		return NULL;
	}
	return sl->entry[index];
}

void nstr_list_append(NStringList *sl, NString *str)
{
	if (sl == NULL || sl->entry == NULL || sl->qty < 0 || sl->mlen <= 0 ||
		sl->qty > sl ->mlen) {
		return;
	} else if (str == NULL || str->data == NULL || str->slen < 0 ||
	           str->mlen <= 0 || str->slen > str->mlen ) {
		return;
	}

	nstr_list_alloc(sl, sl->qty + 1);
	if (sl) {
		sl->entry[sl->qty] = str;
		sl->qty++;
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

void nstr_split_callback(const NString *str, unsigned char split, int32_t pos,
                                  int32_t (*func_callback)(void *param, int32_t offset, int32_t len),
                                  void *param)
{
	bsplitcb(str, split, pos, func_callback, param);
}

void nstr_splits_callback(const NString *str, const NString *splits, int32_t pos,
                                   int32_t (*func_callback)(void *param, int32_t offset, int32_t len),
                                   void *param)
{
	bsplitscb(str, splits, pos, func_callback, param);
}

void nstr_split_string_callback(const NString *str, const NString *split, int32_t pos,
                                   int32_t (*func_callback)(void *param, int32_t offset, int32_t len),
                                   void *param)
{
	bsplitstrcb(str, split, pos, func_callback, param);
}

// Format
void nstr_pattern(NString *str, int32_t len)
{
	bpattern(str, len);
}

void nstr_to_upper(NString *str)
{
	btoupper(str);
}

void nstr_to_lower(NString *str)
{
	btolower(str);
}

void nstr_trim_whitespace_left(NString *str)
{
	bltrimws(str);
}

void nstr_trim_whitespace_right(NString *str)
{
	brtrimws(str);
}

void nstr_trim_whitespace(NString *str)
{
	brtrimws(str);
}

// sprintf drop-in replacements
NString *nstr_format(const char *format, ...)
{
	int32 ret;
	NString *str = bfromcstr("");
	bvformata(ret, str, format, format);
	if (ret == BSTR_OK) {
		return str;
	} else {
		return NULL;
	}
}

void nstr_format_append(NString *str, const char *format, ...)
{
	bvformata((int32){0}, str, format, format);
}

void nstr_assign_format(NString *str, const char *format, ...)
{
	nstr_destroy(str);
	str = nstr_from_cstr("");
	bvformata((int32){0}, str, format, format);
}

void nstr_vaformat(NString *str, uint32_t count, const char *format, va_list va)
{
	bvcformata(str, count, format, va);
}

uint32_t nstr_to_uint(const NString *str)
{
	if (str == NULL || str->data == NULL || str->slen < 0 ||
		str->mlen <= 0 || str->slen > str->mlen ) {
		return -1;
	} else {
		uint32_t sum = 0;
		uint32_t place_value = 1;
		uint32_t base = 10;
		uint32_t i = nstr_len(str) - 1;

		if (nstr_is_stem_eq_static(str, "0x")) {
			base = 16;
		} else if (nstr_is_stem_eq_static(str, "0b")) {
			base = 2;
		} else if (nstr_is_stem_eq_static(str, "0")) {
			base = 8;
		}

		while (i >= 0) {
			sum += nstr_char_at(str, i) * place_value;
			i--;
			place_value *= base;
		}
	return sum;
  }
}
