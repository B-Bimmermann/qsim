#ifndef DEBUG_PRINT
#define DEBUG_PRINT

#define DEBUG_ENABLE 1

#ifndef DEBUG_ENABLE
    #include <stddef.h>
    #define DEBUG_ENABLE 0
    char * __progname = NULL;
#else
    extern char * __progname;
#endif

#ifdef DEBUG_ENABLE
    #include <stdio.h>

    #define DB_PRINT(...) do { \
        if (DEBUG_ENABLE) { \
            fprintf(stderr, "DEBUG | PROGRAM: %-10s | FUNCTION: %-10s | ",__progname, __func__); \
            fprintf(stderr, ## __VA_ARGS__); \
            fprintf(stderr, " \n"); \
            fflush(stderr); \
        } \
    } while (0);
#endif

#endif // DEBUG_PRINT

