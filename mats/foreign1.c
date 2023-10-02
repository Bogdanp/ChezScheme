/* foreign1.c
 * Copyright 1984-2017 Cisco Systems, Inc.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef _WIN32
#  define SCHEME_IMPORT
#  include "scheme.h"
#  undef EXPORT
#  define EXPORT extern __declspec (dllexport)
#else
#include "scheme.h"
#endif

EXPORT int id(int x) {
   return x;
}

EXPORT int idid(int x) {
    return id(id(x));
}

EXPORT int ididid(int x) {
    return idid(id(x));
}

EXPORT unsigned int iduns(unsigned int x) {
   return x;
}

EXPORT iptr idiptr(iptr x) {
   return x;
}

EXPORT iptr idiptr_addr(void) {
   return (iptr)&idiptr;
}

EXPORT double float_id(double x) {
   return x;
}

#define XMKID(prefix,bits,suffix) prefix##bits##suffix
/* build list of results matching description in foreign.stex */
#define XIRT(name, bits, itype, utype) \
  EXPORT ptr name(itype x) { \
    ptr ls = Snil; \
    ls = Scons(Sinteger64((itype)XMKID(Sunsigned,bits,_value)(XMKID(Sunsigned,bits,)((utype)x))), ls); \
    ls = Scons(Sinteger64(XMKID(Sinteger,bits,_value)(XMKID(Sunsigned,bits,)((utype)x))), ls); \
    ls = Scons(Sinteger64((itype)XMKID(Sunsigned,bits,_value)(XMKID(Sinteger,bits,)(x))), ls); \
    ls = Scons(Sinteger64(XMKID(Sinteger,bits,_value)(XMKID(Sinteger,bits,)(x))), ls); \
    return ls; \
  }
/* build list of results matching description in foreign.stex */
#define XURT(name, bits, itype, utype) \
  EXPORT ptr name(itype x) { \
    ptr ls = Snil; \
    ls = Scons(Sunsigned64(XMKID(Sunsigned,bits,_value)(XMKID(Sunsigned,bits,)(x))), ls); \
    ls = Scons(Sunsigned64((utype)XMKID(Sinteger,bits,_value)(XMKID(Sunsigned,bits,)(x))), ls); \
    ls = Scons(Sunsigned64(XMKID(Sunsigned,bits,_value)(XMKID(Sinteger,bits,)((itype)x))), ls); \
    ls = Scons(Sunsigned64((utype)XMKID(Sinteger,bits,_value)(XMKID(Sinteger,bits,)((itype)x))), ls); \
    return ls; \
  }

XIRT(rt_int,,iptr,uptr)
XIRT(rt_int32,32,Sint32_t,Suint32_t)
XIRT(rt_int64,64,Sint64_t,Suint64_t)

XURT(rt_uint,,iptr,uptr)
XURT(rt_uint32,32,Sint32_t,Suint32_t)
XURT(rt_uint64,64,Sint64_t,Suint64_t)

#define XTOI(name, bits, type) EXPORT type name(ptr x) { return XMKID(Sinteger,bits,_value)(x); }
#define XTOU(name, bits, type) EXPORT type name(ptr x) { return XMKID(Sunsigned,bits,_value)(x); }

XTOI(to_int,,iptr)
XTOI(to_int32,32,Sint32_t)
XTOI(to_int64,64,Sint64_t)

XTOU(to_uint,,uptr)
XTOU(to_uint32,32,Suint32_t)
XTOU(to_uint64,64,Suint64_t)

#ifdef _WIN32
#include <stdlib.h>

EXPORT int windows_strcpy(char *dst, char *src) {
  return strcpy(dst, src);
}

EXPORT int windows_strcmp(char *dst, char *src) {
  return strcmp(dst, src);
}

EXPORT void *windows_malloc(long n) {
  return malloc(n);
}

EXPORT void windows_free(void *x) {
  free(x);
}
#endif
