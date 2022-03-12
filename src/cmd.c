#include "cgit/cmd.h"
#include "cgit/util.h"
#include "cgit/compress.h"
#include "cgit/hash.h"
#include <openssl/sha.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cgit_init(void)
{
	if (mkdir_p(".git/objects", S_IRWXU) == -1)
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

int cgit_add(const char *fpath)
{
	// compress
	FILE *input = fopen(fpath, "r");
	if (!input) {
		fprintf(stderr, "failed to open input\n");
		return -1;
	}

	char *compressBuf = NULL;
	size_t compressLen;

	if (deflate_file(input, Z_DEFAULT_COMPRESSION, &compressBuf,
			 &compressLen) != 0) {
		printf("failed to Compress data\n");
		return -1;
	}

	// hash
	char *hashed = sha1hash(compressBuf, compressLen);
	if (!hashed) {
		printf("failed to Hash Compressed data\n");
		return -1;
	}

	size_t blobpathlen = strlen(".git/objects/") + strlen(hashed) + 1;
	char *blobpath = malloc(blobpathlen * sizeof(char));
	if (!blobpath) {
		perror("malloc");
		return -1;
	}

	snprintf(blobpath, blobpathlen, ".git/objects/%s", hashed);

	FILE *fblob = fopen(blobpath, "w+");
	if (!fblob) {
		printf("failed to open blob for writing\n");
		return -1;
	}

	fwrite(compressBuf, compressLen, 1, fblob);
	fclose(fblob);

	printf("blob_sha: %s\n", hashed);

	free(blobpath);
	free(compressBuf);
	free(hashed);
	return 0;
}
