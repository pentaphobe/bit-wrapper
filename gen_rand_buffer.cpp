#include <cstdio>
#include <cstdlib>
#include <ctime>

#define RANDOM_BYTES (1 << 16)

int main(int argc, char *argv[]) {
	FILE *fp = fopen("random.dat", "w");

	srand((unsigned int) time (NULL));
	for (int i=0; i < RANDOM_BYTES; i++) {
		char c = rand() % 256;
		fwrite(&c, sizeof(char), 1, fp);
	}

	fclose(fp);
}