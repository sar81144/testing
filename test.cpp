#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdarg>

#define MAX_CP_SIZE 256     // max codepoint "<file:func(line)>\0" size
#define MAX_FT_SIZE 512     // max size for free text formatted message
#define MAX_KV_SIZE 512     // max size for json formatted key-values

#define KVP_CODE_POINT "CODE_POINT"

// Helper to extract filename from full path
inline const char* getFilename(const char* path) {
    const char* slash = strrchr(path, '/');
    return slash ? (slash + 1) : path;
}

// Helper to generate codepoint string
inline void makeCodePoint(char* buf, const char* file, const char* func, int line) {
    snprintf(buf, MAX_CP_SIZE, "<%s:%s(%d)>", getFilename(file), func, line);
}

// Helper to format the key-value pair
inline int makeKVP(char* kvpBuf, const char* file, const char* func, int line) {
    char codepoint[MAX_CP_SIZE];
    makeCodePoint(codepoint, file, func, line);
    return snprintf(kvpBuf, MAX_KV_SIZE, "{\"%s\":\"%s\"}", KVP_CODE_POINT, codepoint);
}

// Main logging function
inline void logPrint(int level, const char* file, const char* func, int line, const char* fmt, ...) {
    char kvp[MAX_KV_SIZE];
    int offset = makeKVP(kvp, file, func, line);

    if (offset < 0 || offset >= MAX_KV_SIZE) return;

    kvp[offset] = ' ';

    va_list args;
    va_start(args, fmt);
    snprintf(kvp + offset + 1, MAX_KV_SIZE - offset - 1, fmt, args);
    va_end(args);

    std::cout << "[Level " << level << "] " << kvp << std::endl;
}

inline void logDebug(const char* file, const char* func, int line, const char* fmt, ...) {
    char kvp[MAX_KV_SIZE];
    int offset = makeKVP(kvp, file, func, line);

    if (offset < 0 || offset >= MAX_KV_SIZE) return;

    kvp[offset] = ' ';

    va_list args;
    va_start(args, fmt);
    snprintf(kvp + offset + 1, MAX_KV_SIZE - offset - 1, fmt, args);
    va_end(args);

    std::cout << "[DEBUG] " << kvp << std::endl;
}

// Wrapper macros to auto-fill file, func, line
#define LOG_TRACE(fmt, ...) logDebug(__FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) logPrint(6, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) logPrint(4, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) logPrint(3, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...) logPrint(2, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

int main() {
    LOG_TRACE("There's a DRM obj in json option string");
    LOG_INFO("Info level log example with value: %d", 42);
    LOG_ERROR("An error occurred: %s", "File not found");

    // Removed incorrect buffer usage
    char buffer[100] = {0};
    buffer[0] = 'r';  // Safe usage

    return 0;
}
