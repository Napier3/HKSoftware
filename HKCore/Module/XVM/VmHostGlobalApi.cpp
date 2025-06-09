#include "stdafx.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "VmHostGlobalApi.h"
#include "TVMSingle.h"

/* macro to `unsign' a character */
#define uchar(c)        ((unsigned char)(c))


// 
// static int str_len (lua_State *L) {
//   size_t l;
//   xvm_checklstring(L, 1, &l);
//   lua_pushinteger(L, l);
//   return 1;
// }
// 
// 
// static ptrdiff_t posrelat (ptrdiff_t pos, size_t len) {
//   /* relative string position: negative means back from end */
//   if (pos < 0) pos += (ptrdiff_t)len + 1;
//   return (pos >= 0) ? pos : 0;
// }
// 
// 
// static int str_sub (lua_State *L) {
//   size_t l;
//   const char *s = xvm_checklstring(L, 1, &l);
//   ptrdiff_t start = posrelat(xvm_checkinteger(L, 2), l);
//   ptrdiff_t end = posrelat(xvm_optinteger(L, 3, -1), l);
//   if (start < 1) start = 1;
//   if (end > (ptrdiff_t)l) end = (ptrdiff_t)l;
//   if (start <= end)
//     lua_pushlstring(L, s+start-1, end-start+1);
//   else lua_pushliteral(L, "");
//   return 1;
// }
// 
// 
// static int str_reverse (lua_State *L) {
//   size_t l;
//   xvm_Buffer b;
//   const char *s = xvm_checklstring(L, 1, &l);
//   xvm_buffinit(L, &b);
//   while (l--) xvm_addchar(&b, s[l]);
//   xvm_pushresult(&b);
//   return 1;
// }
// 
// 
// static int str_lower (lua_State *L) {
//   size_t l;
//   size_t i;
//   xvm_Buffer b;
//   const char *s = xvm_checklstring(L, 1, &l);
//   xvm_buffinit(L, &b);
//   for (i=0; i<l; i++)
//     xvm_addchar(&b, tolower(uchar(s[i])));
//   xvm_pushresult(&b);
//   return 1;
// }
// 
// 
// static int str_upper (lua_State *L) {
//   size_t l;
//   size_t i;
//   xvm_Buffer b;
//   const char *s = xvm_checklstring(L, 1, &l);
//   xvm_buffinit(L, &b);
//   for (i=0; i<l; i++)
//     xvm_addchar(&b, toupper(uchar(s[i])));
//   xvm_pushresult(&b);
//   return 1;
// }
// 
// static int str_rep (lua_State *L) {
//   size_t l;
//   xvm_Buffer b;
//   const char *s = xvm_checklstring(L, 1, &l);
//   int n = xvm_checkint(L, 2);
//   xvm_buffinit(L, &b);
//   while (n-- > 0)
//     xvm_addlstring(&b, s, l);
//   xvm_pushresult(&b);
//   return 1;
// }
// 
// 
// static int str_byte (lua_State *L) {
//   size_t l;
//   const char *s = xvm_checklstring(L, 1, &l);
//   ptrdiff_t posi = posrelat(xvm_optinteger(L, 2, 1), l);
//   ptrdiff_t pose = posrelat(xvm_optinteger(L, 3, posi), l);
//   int n, i;
//   if (posi <= 0) posi = 1;
//   if ((size_t)pose > l) pose = l;
//   if (posi > pose) return 0;  /* empty interval; return no values */
//   n = (int)(pose -  posi + 1);
//   if (posi + n <= pose)  /* overflow? */
//     xvm_error(L, "string slice too long");
//   xvm_checkstack(L, n, "string slice too long");
//   for (i=0; i<n; i++)
//     lua_pushinteger(L, uchar(s[posi+i-1]));
//   return n;
// }
// 
// 
// static int str_char (lua_State *L) {
//   int n = lua_gettop(L);  /* number of arguments */
//   int i;
//   xvm_Buffer b;
//   xvm_buffinit(L, &b);
//   for (i=1; i<=n; i++) {
//     int c = xvm_checkint(L, i);
//     xvm_argcheck(L, uchar(c) == c, i, "invalid value");
//     xvm_addchar(&b, uchar(c));
//   }
//   xvm_pushresult(&b);
//   return 1;
// }
// 
// 
// static int writer (lua_State *L, const void* b, size_t size, void* B) {
//   (void)L;
//   xvm_addlstring((xvm_Buffer*) B, (const char *)b, size);
//   return 0;
// }
// 
// 
// static int str_dump (lua_State *L) {
//   xvm_Buffer b;
//   xvm_checktype(L, 1, XVM_TFUNCTION);
//   lua_settop(L, 1);
//   xvm_buffinit(L,&b);
//   if (lua_dump(L, writer, &b) != 0)
//     xvm_error(L, "unable to dump given function");
//   xvm_pushresult(&b);
//   return 1;
// }
// 
// 
// 
// /*
// ** {======================================================
// ** PATTERN MATCHING
// ** =======================================================
// */
// 
// 
// #define CAP_UNFINISHED	(-1)
// #define CAP_POSITION	(-2)
// 
// typedef struct MatchState {
//   const char *src_init;  /* init of source string */
//   const char *src_end;  /* end (`\0') of source string */
//   lua_State *L;
//   int level;  /* total number of captures (finished or unfinished) */
//   struct {
//     const char *init;
//     ptrdiff_t len;
//   } capture[XVM_MAXCAPTURES];
// } MatchState;
// 
// 

// 
// 
// static int check_capture (MatchState *ms, int l) {
//   l -= '1';
//   if (l < 0 || l >= ms->level || ms->capture[l].len == CAP_UNFINISHED)
//     return xvm_error(ms->L, "invalid capture index");
//   return l;
// }
// 
// 
// static int capture_to_close (MatchState *ms) {
//   int level = ms->level;
//   for (level--; level>=0; level--)
//     if (ms->capture[level].len == CAP_UNFINISHED) return level;
//   return xvm_error(ms->L, "invalid pattern capture");
// }
// 
// 
// static const char *classend (MatchState *ms, const char *p) {
//   switch (*p++) {
//     case XVM_L_ESC: {
//       if (*p == '\0')
//         xvm_error(ms->L, "malformed pattern (ends with " XVM_QL("%%") ")");
//       return p+1;
//     }
//     case '[': {
//       if (*p == '^') p++;
//       do {  /* look for a `]' */
//         if (*p == '\0')
//           xvm_error(ms->L, "malformed pattern (missing " XVM_QL("]") ")");
//         if (*(p++) == XVM_L_ESC && *p != '\0')
//           p++;  /* skip escapes (e.g. `%]') */
//       } while (*p != ']');
//       return p+1;
//     }
//     default: {
//       return p;
//     }
//   }
// }
// 
// 
// static int match_class (int c, int cl) {
//   int res;
//   switch (tolower(cl)) {
//     case 'a' : res = isalpha(c); break;
//     case 'c' : res = iscntrl(c); break;
//     case 'd' : res = isdigit(c); break;
//     case 'l' : res = islower(c); break;
//     case 'p' : res = ispunct(c); break;
//     case 's' : res = isspace(c); break;
//     case 'u' : res = isupper(c); break;
//     case 'w' : res = isalnum(c); break;
//     case 'x' : res = isxdigit(c); break;
//     case 'z' : res = (c == 0); break;
//     default: return (cl == c);
//   }
//   return (islower(cl) ? res : !res);
// }
// 
// 
// static int matchbracketclass (int c, const char *p, const char *ec) {
//   int sig = 1;
//   if (*(p+1) == '^') {
//     sig = 0;
//     p++;  /* skip the `^' */
//   }
//   while (++p < ec) {
//     if (*p == XVM_L_ESC) {
//       p++;
//       if (match_class(c, uchar(*p)))
//         return sig;
//     }
//     else if ((*(p+1) == '-') && (p+2 < ec)) {
//       p+=2;
//       if (uchar(*(p-2)) <= c && c <= uchar(*p))
//         return sig;
//     }
//     else if (uchar(*p) == c) return sig;
//   }
//   return !sig;
// }
// 
// 
// static int singlematch (int c, const char *p, const char *ep) {
//   switch (*p) {
//     case '.': return 1;  /* matches any char */
//     case XVM_L_ESC: return match_class(c, uchar(*(p+1)));
//     case '[': return matchbracketclass(c, p, ep-1);
//     default:  return (uchar(*p) == c);
//   }
// }
// 
// 
// static const char *match (MatchState *ms, const char *s, const char *p);
// 
// 
// static const char *matchbalance (MatchState *ms, const char *s,
//                                    const char *p) {
//   if (*p == 0 || *(p+1) == 0)
//     xvm_error(ms->L, "unbalanced pattern");
//   if (*s != *p) return NULL;
//   else {
//     int b = *p;
//     int e = *(p+1);
//     int cont = 1;
//     while (++s < ms->src_end) {
//       if (*s == e) {
//         if (--cont == 0) return s+1;
//       }
//       else if (*s == b) cont++;
//     }
//   }
//   return NULL;  /* string ends out of balance */
// }
// 
// 
// static const char *max_expand (MatchState *ms, const char *s,
//                                  const char *p, const char *ep) {
//   ptrdiff_t i = 0;  /* counts maximum expand for item */
//   while ((s+i)<ms->src_end && singlematch(uchar(*(s+i)), p, ep))
//     i++;
//   /* keeps trying to match with the maximum repetitions */
//   while (i>=0) {
//     const char *res = match(ms, (s+i), ep+1);
//     if (res) return res;
//     i--;  /* else didn't match; reduce 1 repetition to try again */
//   }
//   return NULL;
// }
// 
// 
// static const char *min_expand (MatchState *ms, const char *s,
//                                  const char *p, const char *ep) {
//   for (;;) {
//     const char *res = match(ms, s, ep+1);
//     if (res != NULL)
//       return res;
//     else if (s<ms->src_end && singlematch(uchar(*s), p, ep))
//       s++;  /* try with one more repetition */
//     else return NULL;
//   }
// }
// 
// 
// static const char *start_capture (MatchState *ms, const char *s,
//                                     const char *p, int what) {
//   const char *res;
//   int level = ms->level;
//   if (level >= XVM_MAXCAPTURES) xvm_error(ms->L, "too many captures");
//   ms->capture[level].init = s;
//   ms->capture[level].len = what;
//   ms->level = level+1;
//   if ((res=match(ms, s, p)) == NULL)  /* match failed? */
//     ms->level--;  /* undo capture */
//   return res;
// }
// 
// 
// static const char *end_capture (MatchState *ms, const char *s,
//                                   const char *p) {
//   int l = capture_to_close(ms);
//   const char *res;
//   ms->capture[l].len = s - ms->capture[l].init;  /* close capture */
//   if ((res = match(ms, s, p)) == NULL)  /* match failed? */
//     ms->capture[l].len = CAP_UNFINISHED;  /* undo capture */
//   return res;
// }
// 
// 
// static const char *match_capture (MatchState *ms, const char *s, int l) {
//   size_t len;
//   l = check_capture(ms, l);
//   len = ms->capture[l].len;
//   if ((size_t)(ms->src_end-s) >= len &&
//       memcmp(ms->capture[l].init, s, len) == 0)
//     return s+len;
//   else return NULL;
// }
// 
// 
// static const char *match (MatchState *ms, const char *s, const char *p) {
//   init: /* using goto's to optimize tail recursion */
//   switch (*p) {
//     case '(': {  /* start capture */
//       if (*(p+1) == ')')  /* position capture? */
//         return start_capture(ms, s, p+2, CAP_POSITION);
//       else
//         return start_capture(ms, s, p+1, CAP_UNFINISHED);
//     }
//     case ')': {  /* end capture */
//       return end_capture(ms, s, p+1);
//     }
//     case XVM_L_ESC: {
//       switch (*(p+1)) {
//         case 'b': {  /* balanced string? */
//           s = matchbalance(ms, s, p+2);
//           if (s == NULL) return NULL;
//           p+=4; goto init;  /* else return match(ms, s, p+4); */
//         }
//         case 'f': {  /* frontier? */
//           const char *ep; char previous;
//           p += 2;
//           if (*p != '[')
//             xvm_error(ms->L, "missing " XVM_QL("[") " after "
//                                XVM_QL("%%f") " in pattern");
//           ep = classend(ms, p);  /* points to what is next */
//           previous = (s == ms->src_init) ? '\0' : *(s-1);
//           if (matchbracketclass(uchar(previous), p, ep-1) ||
//              !matchbracketclass(uchar(*s), p, ep-1)) return NULL;
//           p=ep; goto init;  /* else return match(ms, s, ep); */
//         }
//         default: {
//           if (isdigit(uchar(*(p+1)))) {  /* capture results (%0-%9)? */
//             s = match_capture(ms, s, uchar(*(p+1)));
//             if (s == NULL) return NULL;
//             p+=2; goto init;  /* else return match(ms, s, p+2) */
//           }
//           goto dflt;  /* case default */
//         }
//       }
//     }
//     case '\0': {  /* end of pattern */
//       return s;  /* match succeeded */
//     }
//     case '$': {
//       if (*(p+1) == '\0')  /* is the `$' the last char in pattern? */
//         return (s == ms->src_end) ? s : NULL;  /* check end of string */
//       else goto dflt;
//     }
//     default: dflt: {  /* it is a pattern item */
//       const char *ep = classend(ms, p);  /* points to what is next */
//       int m = s<ms->src_end && singlematch(uchar(*s), p, ep);
//       switch (*ep) {
//         case '?': {  /* optional */
//           const char *res;
//           if (m && ((res=match(ms, s+1, ep+1)) != NULL))
//             return res;
//           p=ep+1; goto init;  /* else return match(ms, s, ep+1); */
//         }
//         case '*': {  /* 0 or more repetitions */
//           return max_expand(ms, s, p, ep);
//         }
//         case '+': {  /* 1 or more repetitions */
//           return (m ? max_expand(ms, s+1, p, ep) : NULL);
//         }
//         case '-': {  /* 0 or more repetitions (minimum) */
//           return min_expand(ms, s, p, ep);
//         }
//         default: {
//           if (!m) return NULL;
//           s++; p=ep; goto init;  /* else return match(ms, s+1, ep); */
//         }
//       }
//     }
//   }
// }
// 
// 
// 
// static const char *lmemfind (const char *s1, size_t l1,
//                                const char *s2, size_t l2) {
//   if (l2 == 0) return s1;  /* empty strings are everywhere */
//   else if (l2 > l1) return NULL;  /* avoids a negative `l1' */
//   else {
//     const char *init;  /* to search for a `*s2' inside `s1' */
//     l2--;  /* 1st char will be checked by `memchr' */
//     l1 = l1-l2;  /* `s2' cannot be found after that */
//     while (l1 > 0 && (init = (const char *)memchr(s1, *s2, l1)) != NULL) {
//       init++;   /* 1st char is already checked */
//       if (memcmp(init, s2+1, l2) == 0)
//         return init-1;
//       else {  /* correct `l1' and `s1' to try again */
//         l1 -= init-s1;
//         s1 = init;
//       }
//     }
//     return NULL;  /* not found */
//   }
// }
// 
// 
// static void push_onecapture (MatchState *ms, int i, const char *s,
//                                                     const char *e) {
//   if (i >= ms->level) {
//     if (i == 0)  /* ms->level == 0, too */
//       lua_pushlstring(ms->L, s, e - s);  /* add whole match */
//     else
//       xvm_error(ms->L, "invalid capture index");
//   }
//   else {
//     ptrdiff_t l = ms->capture[i].len;
//     if (l == CAP_UNFINISHED) xvm_error(ms->L, "unfinished capture");
//     if (l == CAP_POSITION)
//       lua_pushinteger(ms->L, ms->capture[i].init - ms->src_init + 1);
//     else
//       lua_pushlstring(ms->L, ms->capture[i].init, l);
//   }
// }
// 
// 
// static int push_captures (MatchState *ms, const char *s, const char *e) {
//   int i;
//   int nlevels = (ms->level == 0 && s) ? 1 : ms->level;
//   xvm_checkstack(ms->L, nlevels, "too many captures");
//   for (i = 0; i < nlevels; i++)
//     push_onecapture(ms, i, s, e);
//   return nlevels;  /* number of strings pushed */
// }
// 
// 
// static int str_find_aux (lua_State *L, int find) {
//   size_t l1, l2;
//   const char *s = xvm_checklstring(L, 1, &l1);
//   const char *p = xvm_checklstring(L, 2, &l2);
//   ptrdiff_t init = posrelat(xvm_optinteger(L, 3, 1), l1) - 1;
//   if (init < 0) init = 0;
//   else if ((size_t)(init) > l1) init = (ptrdiff_t)l1;
//   if (find && (lua_toboolean(L, 4) ||  /* explicit request? */
//       strpbrk(p, XVM_SPECIALS) == NULL)) {  /* or no special characters? */
//     /* do a plain search */
//     const char *s2 = lmemfind(s+init, l1-init, p, l2);
//     if (s2) {
//       lua_pushinteger(L, s2-s+1);
//       lua_pushinteger(L, s2-s+l2);
//       return 2;
//     }
//   }
//   else {
//     MatchState ms;
//     int anchor = (*p == '^') ? (p++, 1) : 0;
//     const char *s1=s+init;
//     ms.L = L;
//     ms.src_init = s;
//     ms.src_end = s+l1;
//     do {
//       const char *res;
//       ms.level = 0;
//       if ((res=match(&ms, s1, p)) != NULL) {
//         if (find) {
//           lua_pushinteger(L, s1-s+1);  /* start */
//           lua_pushinteger(L, res-s);   /* end */
//           return push_captures(&ms, NULL, 0) + 2;
//         }
//         else
//           return push_captures(&ms, s1, res);
//       }
//     } while (s1++ < ms.src_end && !anchor);
//   }
//   lua_pushnil(L);  /* not found */
//   return 1;
// }
// 
// 
// static int str_find (lua_State *L) {
//   return str_find_aux(L, 1);
// }
// 
// 
// static int str_match (lua_State *L) {
//   return str_find_aux(L, 0);
// }
// 
// 
// static int gmatch_aux (lua_State *L) {
//   MatchState ms;
//   size_t ls;
//   const char *s = lua_tolstring(L, lua_upvalueindex(1), &ls);
//   const char *p = lua_tostring(L, lua_upvalueindex(2));
//   const char *src;
//   ms.L = L;
//   ms.src_init = s;
//   ms.src_end = s+ls;
//   for (src = s + (size_t)lua_tointeger(L, lua_upvalueindex(3));
//        src <= ms.src_end;
//        src++) {
//     const char *e;
//     ms.level = 0;
//     if ((e = match(&ms, src, p)) != NULL) {
//       lua_Integer newstart = e-s;
//       if (e == src) newstart++;  /* empty match? go at least one position */
//       lua_pushinteger(L, newstart);
//       lua_replace(L, lua_upvalueindex(3));
//       return push_captures(&ms, src, e);
//     }
//   }
//   return 0;  /* not found */
// }
// 
// 
// static int gmatch (lua_State *L) {
//   xvm_checkstring(L, 1);
//   xvm_checkstring(L, 2);
//   lua_settop(L, 2);
//   lua_pushinteger(L, 0);
//   lua_pushcclosure(L, gmatch_aux, 3);
//   return 1;
// }
// 
// 
// static int gfind_nodef (lua_State *L) {
//   return xvm_error(L, XVM_QL("string.gfind") " was renamed to "
//                        XVM_QL("string.gmatch"));
// }
// 
// 
// static void add_s (MatchState *ms, xvm_Buffer *b, const char *s,
//                                                    const char *e) {
//   size_t l, i;
//   const char *news = lua_tolstring(ms->L, 3, &l);
//   for (i = 0; i < l; i++) {
//     if (news[i] != XVM_L_ESC)
//       xvm_addchar(b, news[i]);
//     else {
//       i++;  /* skip ESC */
//       if (!isdigit(uchar(news[i])))
//         xvm_addchar(b, news[i]);
//       else if (news[i] == '0')
//           xvm_addlstring(b, s, e - s);
//       else {
//         push_onecapture(ms, news[i] - '1', s, e);
//         xvm_addvalue(b);  /* add capture to accumulated result */
//       }
//     }
//   }
// }
// 
// 
// static void add_value (MatchState *ms, xvm_Buffer *b, const char *s,
//                                                        const char *e) {
//   lua_State *L = ms->L;
//   switch (lua_type(L, 3)) {
//     case XVM_TNUMBER:
//     case XVM_TSTRING: {
//       add_s(ms, b, s, e);
//       return;
//     }
//     case XVM_TFUNCTION: {
//       int n;
//       lua_pushvalue(L, 3);
//       n = push_captures(ms, s, e);
//       lua_call(L, n, 1);
//       break;
//     }
//     case XVM_TTABLE: {
//       push_onecapture(ms, 0, s, e);
//       lua_gettable(L, 3);
//       break;
//     }
//   }
//   if (!lua_toboolean(L, -1)) {  /* nil or false? */
//     lua_pop(L, 1);
//     lua_pushlstring(L, s, e - s);  /* keep original text */
//   }
//   else if (!lua_isstring(L, -1))
//     xvm_error(L, "invalid replacement value (a %s)", xvm_typename(L, -1)); 
//   xvm_addvalue(b);  /* add result to accumulator */
// }
// 
// 
// static int str_gsub (lua_State *L) {
//   size_t srcl;
//   const char *src = xvm_checklstring(L, 1, &srcl);
//   const char *p = xvm_checkstring(L, 2);
//   int  tr = lua_type(L, 3);
//   int max_s = xvm_optint(L, 4, srcl+1);
//   int anchor = (*p == '^') ? (p++, 1) : 0;
//   int n = 0;
//   MatchState ms;
//   xvm_Buffer b;
//   xvm_argcheck(L, tr == XVM_TNUMBER || tr == XVM_TSTRING ||
//                    tr == XVM_TFUNCTION || tr == XVM_TTABLE, 3,
//                       "string/function/table expected");
//   xvm_buffinit(L, &b);
//   ms.L = L;
//   ms.src_init = src;
//   ms.src_end = src+srcl;
//   while (n < max_s) {
//     const char *e;
//     ms.level = 0;
//     e = match(&ms, src, p);
//     if (e) {
//       n++;
//       add_value(&ms, &b, src, e);
//     }
//     if (e && e>src) /* non empty match? */
//       src = e;  /* skip it */
//     else if (src < ms.src_end)
//       xvm_addchar(&b, *src++);
//     else break;
//     if (anchor) break;
//   }
//   xvm_addlstring(&b, src, ms.src_end-src);
//   xvm_pushresult(&b);
//   lua_pushinteger(L, n);  /* number of substitutions */
//   return 2;
// }

/* }====================================================== */


/* maximum size of each formatted item (> len(format('%99.99f', -1e308))) */
#define XVM_MAX_ITEM	512
/* valid flags in a format specification */
#define XVM_FMT_FLAGS	"-+ #0"
/*
** maximum size of each format specification (such as '%-099.99d')
** (+10 accounts for %99.99x plus margin of error)
*/
#define XVM_MAX_FORMAT	(sizeof(XVM_FMT_FLAGS) + sizeof(XVM_INTFRMLEN) + 10)


inline void xvm_addchar(xvm_Buffer &B, char c)
{
	ASSERT (B.p  < B.pEnd);
	*B.p =c;
	B.p++;
}


inline void xvm_addchar(xvm_Buffer *B, char c)
{
	ASSERT (B->p  < B->pEnd);
	*B->p =c;
	B->p++;
}

void xvm_addlstring (xvm_Buffer *B, const char *s, size_t l)
{
	while (l--)
		xvm_addchar(B, *s++);
}


const char* xvm_checklstring(CTScriptSingleVM *pSingleVm, int arg, size_t &sfl)
{
	ASSERT (pSingleVm != NULL);
	char *pString = pSingleVm->TS_GetParamAsString(arg);
	sfl = strlen(pString);
	return pString;
}

static void addquoted (CTScriptSingleVM *pSingleVm, xvm_Buffer *b, int arg) 
{
	size_t l;
	const char *s = xvm_checklstring(pSingleVm, arg, l);
	xvm_addchar(b, '"');

	while (l--) 
	{
		switch (*s) 
		{
		case '"': case '\\': case '\n': 
			{
				xvm_addchar(b, '\\');
				xvm_addchar(b, *s);
				break;
			}

		case '\r':
			{
				xvm_addlstring(b, "\\r", 2);
				break;
			}

		case '\0': 
			{
				xvm_addlstring(b, "\\000", 4);
				break;
			}

		default: {
			xvm_addchar(b, *s);
			break;
				 }
		}
		s++;
	}

	xvm_addchar(b, '"');
}

static const char *scanformat (CTScriptSingleVM *pSingleVm, const char *strfrmt, char *form)
{
  const char *p = strfrmt;
  while (*p != '\0' && strchr(XVM_FMT_FLAGS, *p) != NULL) p++;  /* skip flags */

  if ((size_t)(p - strfrmt) >= sizeof(XVM_FMT_FLAGS))
  {
	 // xvm_error(nThreadIndex, "invalid format (repeated flags)");
  }
  if (isdigit(uchar(*p))) p++;  /* skip width */
  if (isdigit(uchar(*p))) p++;  /* (2 digits at most) */

  if (*p == '.') 
  {
    p++;
    if (isdigit(uchar(*p))) p++;  /* skip precision */
    if (isdigit(uchar(*p))) p++;  /* (2 digits at most) */
  }

  if (isdigit(uchar(*p)))
  {
	  //xvm_error(L, "invalid format (width or precision too long)");
  }

  *(form++) = '%';
  strncpy(form, strfrmt, p - strfrmt + 1);
  form += p - strfrmt + 1;
  *form = '\0';

  return p;
}


static void addintlen (char *form) 
{
  size_t l = strlen(form);
  char spec = form[l - 1];
  strcpy(form + l - 1, XVM_INTFRMLEN);
  form[l + sizeof(XVM_INTFRMLEN) - 2] = spec;
  form[l + sizeof(XVM_INTFRMLEN) - 1] = '\0';
}


float xvm_checknumber(CTScriptSingleVM *pSingleVm, int arg)
{
	ASSERT (pSingleVm != NULL);
	return pSingleVm->TS_GetParamAsFloat(arg);
}

long xvm_checknumber_int(CTScriptSingleVM *pSingleVm, int arg)
{
	ASSERT (pSingleVm != NULL);
	return pSingleVm->TS_GetParamAsInt(arg);
}

void xvm_buffinit (CTScriptSingleVM *pSingleVm, xvm_Buffer *B) 
{
	B->pXvm = pSingleVm;
	B->p = B->buffer;
	B->lvl = 0;
	B->pEnd = B->buffer + XVM_BUFFERSIZE;
}

static int emptybuffer (xvm_Buffer *B)
{
	size_t l = bufflen(B);
	if (l == 0)
	{
		return 0;  /* put nothing on stack */
	}
	else 
	{
		B->p = B->buffer;
		B->lvl++;
		return 1;
	}
}


int xvm_str_format_buffer (CTScriptSingleVM *pSingleVm, xvm_Buffer &b) 
{
	int paras = 0;
	int arg = 0;
	size_t sfl;
	paras = xvm_checknumber(pSingleVm, 0);
	arg = paras;
	const char *strfrmt = xvm_checklstring(pSingleVm, paras, sfl);
	const char *strfrmt_end = strfrmt+sfl;
	xvm_buffinit(pSingleVm, &b);

	while (strfrmt < strfrmt_end) 
	{
		if (*strfrmt != XVM_L_ESC)
			xvm_addchar(&b, *strfrmt++);
		else if (*++strfrmt == XVM_L_ESC)
			xvm_addchar(&b, *strfrmt++);  /* %% */
		else 
		{ /* format item */
			char form[XVM_MAX_FORMAT];  /* to store the format (`%...') */
			char buff[XVM_MAX_ITEM];  /* to store the formatted item */
			arg--;
			strfrmt = scanformat(pSingleVm, strfrmt, form);

			switch (*strfrmt++) 
			{
			case 'c': 
				{
					sprintf(buff, form, (int)xvm_checknumber_int(pSingleVm, arg));
					break;
				}
			case 'd':  
			case 'i': 
				{
					addintlen(form);
					sprintf(buff, form, (XVM_INTFRM_T)xvm_checknumber_int(pSingleVm, arg));
					break;
				}
			case 'o': 
			case 'u':  
			case 'x':  
			case 'X': 
				{
					addintlen(form);
					sprintf(buff, form, (unsigned XVM_INTFRM_T)xvm_checknumber_int(pSingleVm, arg));
					break;
				}

			case 'e':  
			case 'E': 
			case 'f':
			case 'g':
			case 'G': 
				{
					sprintf(buff, form, (double)xvm_checknumber(pSingleVm, arg));
					break;
				}

			case 'q':
				{
					addquoted(pSingleVm, &b, arg);
					continue;  /* skip the 'addsize' at the end */
				}

			case 's': 
				{
					size_t l;
					const char *s = xvm_checklstring(pSingleVm, arg, l);
					sprintf(buff, form, s);
				}
				break;
			default: 
				{  /* also treat cases `pnLlh' */
					return paras;
				}
			}

			xvm_addlstring(&b, buff, strlen(buff));
		}
	}

	*b.p = 0;

	return paras;
}

void xvm_str_format (LPVOID pXvm) 
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM*)pXvm;
	xvm_Buffer b;
	long nParas = xvm_str_format_buffer(pSingleVm, b);
	pSingleVm->TS_ReturnString(nParas+1, b.buffer);
}

void xvm_logprint (LPVOID pXvm) 
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM*)pXvm;
	xvm_Buffer b;
	long nParas = xvm_str_format_buffer(pSingleVm, b);
	CString strText;
	strText = b.buffer;
	CLogPrint::LogString(XLOGLEVEL_TRACE,strText);

	pSingleVm->TS_ReturnInt(nParas+1, b.p - b.buffer);
}

void xvm_strlength (LPVOID pXvm) 
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM*)pXvm;
	
	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);
	long nLen = strlen(vValue);

	pSingleVm->TS_ReturnInt(nParas+1,nLen);
}

void xvm_str_to_utf8 (LPVOID pXvm) 
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM*)pXvm;

	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);
	long nLen = strlen(vValue);

	pSingleVm->IncreaseChReturn();
	char *pszReturn = pSingleVm->GetChReurn();
	long nRetLen = 0;

#ifndef _PSX_QT_LINUX_
	charGBK_to_charUtf8(vValue, strlen(vValue), pszReturn, nRetLen);
#endif

	pSingleVm->TS_ReturnString(nParas+1,pszReturn);
}

void xvm_tostring (LPVOID pXvm) 
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM*)pXvm;
	xvm_Buffer b;

	int paras = xvm_checknumber_int(pSingleVm, 0);
	pSingleVm->TS_ToString(1, b.buffer);

	pSingleVm->TS_ReturnString(paras+1, b.buffer);
}

// void xvm_abs (LPVOID pXvm) 
// {
// 	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM*)pXvm;
// 	xvm_Buffer b;
// 
// 	int paras = xvm_checknumber(pSingleVm, 0);
// 	float fValue = pSingleVm->TS_GetParamAsFloat(1);
// 	fValue = fabs(fValue);
// 
// 	pSingleVm->TS_ReturnFloat(paras+1, fValue);
// }



// 
// static const xvm_Reg strlib[] = {
//   {"byte", str_byte},
//   {"char", str_char},
//   {"dump", str_dump},
//   {"find", str_find},
//   {"format", str_format},
//   {"gfind", gfind_nodef},
//   {"gmatch", gmatch},
//   {"gsub", str_gsub},
//   {"len", str_len},
//   {"lower", str_lower},
//   {"match", str_match},
//   {"rep", str_rep},
//   {"reverse", str_reverse},
//   {"sub", str_sub},
//   {"upper", str_upper},
//   {NULL, NULL}
// };
// 
// 
// static void createmetatable (lua_State *L) {
//   lua_createtable(L, 0, 1);  /* create metatable for strings */
//   lua_pushliteral(L, "");  /* dummy string */
//   lua_pushvalue(L, -2);
//   lua_setmetatable(L, -2);  /* set string metatable */
//   lua_pop(L, 1);  /* pop dummy string */
//   lua_pushvalue(L, -2);  /* string library... */
//   lua_setfield(L, -2, "__index");  /* ...is the __index metamethod */
//   lua_pop(L, 1);  /* pop metatable */
// }
// 
// 
// /*
// ** Open string library
// */
// LUALIB_API int luaopen_string (lua_State *L) {
//   xvm_register(L, XVM_STRLIBNAME, strlib);
// #if defined(XVM_COMPAT_GFIND)
//   lua_getfield(L, -1, "gmatch");
//   lua_setfield(L, -2, "gfind");
// #endif
//   createmetatable(L);
//   return 1;
// }
// 
