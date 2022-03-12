#ifndef _CGIT_ZLIB_WRAP_H_
#define _CGIT_ZLIB_WRAP_H_

#include <zlib.h>
#include <stdio.h>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#include <fcntl.h>
#include <io.h>
#define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#define SET_BINARY_MODE(file)
#endif

int def(FILE *source, FILE *dest, int level);
int inf(FILE *source, FILE *dest);
void zerr(int ret);

#endif
