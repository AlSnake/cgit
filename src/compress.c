#include "cgit/compress.h"
#include <wchar.h>

int deflate_file(FILE *src, int level, char **buf, size_t *bufsize)
{
	FILE *bufstream = open_memstream(buf, bufsize);
	if (!bufstream) {
		fprintf(stderr, "failed to open buffer stream\n");
		return -1;
	}

	int ret = def(src, bufstream, level);
	if (ret != Z_OK) {
		fclose(bufstream);
		zerr(ret);
		return ret;
	}

	fclose(bufstream);
	return 0;
}

char *inflate_file(FILE *src)
{
	char *buf = NULL;
	size_t bufsize;

	FILE *bufstream = open_memstream(&buf, &bufsize);
	if (!bufstream) {
		fprintf(stderr, "failed to open buffer stream\n");
		return NULL;
	}

	int ret = inf(src, bufstream);
	if (ret != Z_OK) {
		zerr(ret);
		return ret;
	}

	fclose(bufstream);
	return buf;
}

int inflate_data(const char *data, int datalen, char **buf, size_t *bufsize)
{
	FILE *bufstream = open_memstream(buf, bufsize);
	if (!bufstream) {
		fprintf(stderr, "failed to open buffer stream\n");
		return -1;
	}

	FILE *datastream = fmemopen(data, datalen, "r");
	if (!datastream) {
		fprintf(stderr, "failed to open buffer stream\n");
		return -1;
	}

	int ret = inf(datastream, bufstream);
	if (ret != Z_OK) {
		zerr(ret);
		return ret;
	}

	fclose(datastream);
	fclose(bufstream);
	return 0;
}
