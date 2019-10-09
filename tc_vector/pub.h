#ifndef PUB_H
#define PUB_H

#define BREAK_IF_NULL(p, r, ERR_CODE) \
    if (!(p)) { (r) = ERR_CODE; break;}

#define BREAK_IF_FAILED(r) \
    if (OK != (r)) { break;}

#define RETURN_IF_FAILED(r) \
    if (OK != (r))  return r;

#define MALLOC(s)  malloc((s))

#define FREE(p) \
    do \
    { \
        if ((p)){free((p)); (p) = NULL;} \
    } \
    while (0)
#endif
