#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include <clog/clog.h>

static int mkdir_p(const char *path, mode_t mode)
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

int cgit_init(void)
{
	if (mkdir_p(".git/objects", S_IRWXU) == -1)
		perror("mkdir");

	if (mkdir_p(".git/refs", S_IRWXU) == -1)
		perror("mkdir");

	if (mkdir_p(".git/refs", S_IRWXU) == -1)
		perror("mkdir");

	FILE *fhead = fopen(".git/HEAD", "w+");
	if (!fhead) {
		printf("failed to open .git/HEAD");
		return -1;
	}

	fprintf(fhead, "ref: refs/heads/master\n");
	fclose(fhead);
	return 0;
}

int main(void)
{
	if (cgit_init() == -1) {
		printf("CGIT INIT FAILED\n");
		return 1;
	}

	printf("CGIT INITALIZED\n");

	return 0;
}
