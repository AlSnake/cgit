#include "cgit/util.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int mkdir_p(const char *path, mode_t mode)
{
	char *tmp = strndup(path, 256);
	size_t len = strlen(tmp);
	char *p = NULL;

	if (tmp[len - 1] == '/')
		tmp[len - 1] = 0;

	for (p = tmp + 1; *p; p++) {
		if (*p == '/') {
			*p = 0;
			mkdir(tmp, mode);
			*p = '/';
		}
	}

	int ret = mkdir(tmp, mode);
	free(tmp);
	return ret;
}

long get_file_size(FILE *fp)
{
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return fsize;
}

char *get_file_content(FILE *fp)
{
	long fsize = get_file_size(fp);
	char *content = malloc(fsize + 1);
	if (!content) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	fread(content, 1, fsize, fp);
	content[fsize] = 0;
	return content;
}
