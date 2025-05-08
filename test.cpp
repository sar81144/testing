#include <string.h>
#include <stdio.h>
#include <time.h>
#include<iostream>
using namespace std;


#pragma GCC system_header

#include <bits/c++config.h>
#include <string.h>

#ifndef _GLIBCXX_CSTRING
#define _GLIBCXX_CSTRING 1

// Get rid of those macros defined in <string.h> in lieu of real functions.
#undef memchr
#undef memcmp
#undef memcpy
#undef memmove
#undef memset
#undef strcat
#undef strchr
#undef strcmp
#undef strcoll
#undef strcpy
#undef strcspn
#undef strerror
#undef strlen
#undef strncat
#undef strncmp
#undef strncpy
#undef strpbrk
#undef strrchr
#undef strspn
#undef strstr
#undef strtok
#undef strxfrm

extern "C++"
{
namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  using ::memchr;
  using ::memcmp;
  using ::memcpy;
  using ::memmove;
  using ::memset;
  using ::strcat;
  using ::strcmp;
  using ::strcoll;
  using ::strcpy;
  using ::strcspn;
  using ::strerror;
  using ::strlen;
  using ::strncat;
  using ::strncmp;
  using ::strncpy;
  using ::strspn;
  using ::strtok;
  using ::strxfrm;
  using ::strchr;
  using ::strpbrk;
  using ::strrchr;
  using ::strstr;

#ifndef __CORRECT_ISO_CPP_STRING_H_PROTO
  inline char*
  strrchr(char* __s, int __n)
  { return __builtin_strrchr(__s, __n); }
#endif

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
} // extern "C++"

#endif



// KVP tags
#define KVP_CODE_POINT           "CODE_POINT"            // code point (file, function, line)

typedef enum
{
    kPmLogLevel_None       = -1,    /* no output */
    kPmLogLevel_Emergency = 0,     /* system is unusable */
    kPmLogLevel_Alert     = 1,     /* action must be taken immediately */
    kPmLogLevel_Critical  = 2,     /* critical conditions */
    kPmLogLevel_Error     = 3,     /* error conditions */
    kPmLogLevel_Warning   = 4,     /* warning conditions */
    kPmLogLevel_Notice    = 5,     /* normal but significant condition */
    kPmLogLevel_Info      = 6,     /* informational */
    kPmLogLevel_Debug     = 7      /* debug-level messages */
} PmLogLevel;

// Modified code for fixing 468276, strchr null check return value
#define __GET_FILENAME(path) ({ \
    const char* __p = strrchr((path), '/'); \
    __p ? (__p + 1) : (path); \
})
#define __FLE __GET_FILENAME(__FILE__)

#ifdef FILE_LOG_ENABLE
#define LOG_PRINT(__level, __msgid, __format, ...) do {\
    int codePointBufferSize = printf("<%s:%s(%d)> " __format "\n", __FLE, __func__, __LINE__, ##__VA_ARGS__);\
    if (codePointBufferSize < 0) {\
        cout<<"snprintf failed"<<endl;\
    }\
} while(0)
#else
#define MAX_CP_SIZE 256     // max codepoint "<file:func(line)>\0" size
#define MAX_FT_SIZE 512     // max size for free text formatted message
#define MAX_KV_SIZE 512     // max size for json formatted key-values

#define __CODEPOINT(__codepoint, __file, __func, __line) do {\
    int codePointBufferSize = snprintf(__codepoint, MAX_CP_SIZE, "<%s:%s(%d)>", __file, __func, __line);\
    if (codePointBufferSize < 0 || codePointBufferSize >= MAX_CP_SIZE) {\
        cout<<"snprintf failed"<<endl;\
    }\
} while(0)

#define __MAKE_KVP(__kvp, __offset) do {\
    char __codepoint[MAX_CP_SIZE];\
    __CODEPOINT(__codepoint, __FLE, __func__, __LINE__);\
    __offset = snprintf(__kvp, MAX_KV_SIZE, "{\"%s\":\"%s\"}", KVP_CODE_POINT, __codepoint);\
    if (__offset < 0 || __offset >= MAX_KV_SIZE) {\
        cout<<"snprintf failed"<<endl;\
    }\
} while(0)

#define LOG_PRINT(__level, __format, ...) do {\
    int __offset;\
    char __kvp[MAX_KV_SIZE];\
    __MAKE_KVP(__kvp, __offset);\
    char __message[MAX_FT_SIZE];\
    int logSize = snprintf(__message, MAX_FT_SIZE, __format, ##__VA_ARGS__);\
    if (logSize < 0 || logSize >= MAX_FT_SIZE) {\
        cout<<"snprintf failed"<<endl;\
    } else {\
        if (__level == kPmLogLevel_Debug) {\
            cout<<"snprintf failed"<<endl;\
        } else {\
            cout<<"snprintf failed"<<endl;\
        }\
    }\
} while(0)
#endif

#ifdef FILE_LOG_ENABLE
#define LOG_DEBUG(__format, ...) do {\
    LOG_PRINT(kPmLogLevel_Debug, __format, ##__VA_ARGS__);\
} while(0)
#else
#define LOG_DEBUG(__format, ...) do {\
    int __offset;\
    char __message[MAX_KV_SIZE];\
    __MAKE_KVP(__message, __offset);\
    if (__offset > 0 &&__offset + 1 < MAX_FT_SIZE) {\
        __message[__offset] = ' ';\
        int __logSize = snprintf(__message + __offset + 1, MAX_FT_SIZE - __offset - 1, __format, ##__VA_ARGS__);\
        if (__logSize >= 0 && __logSize < (MAX_FT_SIZE - __offset - 1)) {\
            cout<<"snprintf failed"<<endl;\
        } else {\
            cout<<"snprintf failed"<<endl;\
        }\
    }\
} while(0)
#endif

#define LOG_INFO(__format, ...) LOG_PRINT(kPmLogLevel_Info, __format, ##__VA_ARGS__)
#define LOG_NOTICE(__format, ...) LOG_PRINT(kPmLogLevel_Info, __format, ##__VA_ARGS__)
#define LOG_WARNING(__format, ...) LOG_PRINT(kPmLogLevel_Warning, __format, ##__VA_ARGS__)
#define LOG_ERROR(__format, ...) LOG_PRINT(kPmLogLevel_Error, __format, ##__VA_ARGS__)
#define LOG_CRITICAL(__format, ...) LOG_PRINT(kPmLogLevel_Critical, __format, ##__VA_ARGS__)
#define LOG_TRACE(__format, ...) LOG_DEBUG(__format, ##__VA_ARGS__)

int main() {
    LOG_TRACE("There's a DRM obj in json option string");

    LOG_DEBUG("userBufferCtrl[] preBufferTimed] bufferingMinTime[] bufferingMaxTime[]");

    return 0;
} 
