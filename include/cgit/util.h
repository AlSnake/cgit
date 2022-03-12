#ifndef _CGIT_UTIL_H_
#define _CGIT_UTIL_H_

#include <stdio.h>
#include <sys/types.h>

int mkdir_p(const char *path, mode_t mode);
long get_file_size(FILE *fp);
char *get_file_content(FILE *fp);

#endif
