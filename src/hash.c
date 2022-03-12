#include "cgit/hash.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>

char *sha1hash(const char *data, int datalen)
{
	int maxlen = 41;

	unsigned char hash[SHA_DIGEST_LENGTH];
	if (!SHA1(data, datalen, hash)) {
		fprintf(stderr, "failed to hash data with SHA1\n");
		return NULL;
	}

	char *hashstr = malloc(maxlen * sizeof(char));
	if (!hashstr) {
		perror("malloc");
		return NULL;
	}

	for (int i = 0; i < 20; i++)
		snprintf(&hashstr[i * 2], maxlen, "%02x", hash[i]);

	hashstr[40] = 0;
	return hashstr;
}
