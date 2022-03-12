#ifndef _CGIT_COMPRESS_H_
#define _CGIT_COMPRESS_H_

#include "zlib_wrap.h"

int deflate_file(FILE *src, int level, char **buf, size_t *bufsize);
char *inflate_file(FILE *src);
int inflate_data(const char *data, int datalen, char **buf, size_t *bufsize);

#endif
