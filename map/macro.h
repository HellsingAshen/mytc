
#define INTCMP(i1, i2)              (((unsigned long long )i1 > (unsigned long long)i2) ?  1 : (((unsigned long long)i1 < (unsigned long long)i2 ) ? -1 : 0))
#define CMPVALBYTYPE(t, n, v2)      ((INT == t) ? (INTCMP(ivkey(n), v2)) : (strcmp(pcvkey(n), (char*)v2)))

#define F_OK        -1
#define OK          0

#define MAP_MAX_SIZE                (65536)
#define MAP_DEFAULT_SIZE            (32)

#define     FREE(p) \
    do \
    { \
        if (p) free(p); p = NULL; \
    } while (0);

#define MIN(n1, n2) ((n1 > n2) ? n2 : n1)

#define PRTE        printf
#define LOGE        printf
#define DESC(str)   (1)

