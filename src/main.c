#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgit/cmd.h"
#include <clog/clog.h>

int main(int argc, char **argv)
{
	if (argc <= 1) {
		printf("%s [cmd][arg]\n", argv[0]);
		return 0;
	}

	if (!strcmp("init", argv[1])) {
		printf("CGIT INITALIZING\n");
		int ret = cgit_init();
		if (ret != 0)
			printf("failed to initalize cgit");
		return ret;
	}

	if (!strcmp("add", argv[1])) {
		if (argc < 3) {
			printf("Specify [FILE]\n");
			return 0;
		}
		int ret = cgit_add(argv[2]);
		if (ret != 0)
			printf("failed to add %s", argv[2]);
		return ret;
	}

	return 0;
}
