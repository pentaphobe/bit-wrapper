#include <cstdio>
#include <cstdlib>

void explode(char inBuf[], unsigned int length, char outBuf[]) {
	int out = 0;
	for (int in=0; in < length; in++) {
		char next = inBuf[in];
		for (int bit=0; bit < 8; bit++) {
			char mask = 1 << bit;
			outBuf[out++] = (next & mask) >> bit; // ? '1' : '0';
		}
	}
}

void implode(char bitBuf[], unsigned int bitSize, char outBuf[]) {
	char accum = 0;
	for (int i=0; i < bitSize; i++) {
		int bit = i % 8;
		int bitVal = bitBuf[i];
		accum |= bitVal << bit;
		outBuf[i / 8] = accum;
		if (bit == 7) {
			accum = 0;
		}
	}
}

void reflow(char inBuf[], char outBuf[], unsigned int length, unsigned int skip) {
	int out = 0;

	for (int in=0; in < length; in++) {
		outBuf[out] = inBuf[in];
		out = (out + skip + 1) % length;
	}
}

void saveBuffer(int id, char buf[], int length) {
	char *filename;
	asprintf(&filename, "skip_%03d.bin", id);
	// printf("saving %s\n", filename);

	FILE *fp = fopen(filename, "w");
	fwrite(&id, sizeof(char), sizeof(id), fp);
	fwrite(buf, sizeof(char), length, fp);
	fclose(fp);

	char *cmd;
	asprintf(&cmd, "zip -9 %s.zip %s > /dev/null", filename, filename);
	// printf("running command: %s\n", cmd);
	system(cmd);
}

#define BUFSIZE (1 << 18)

int main(int argc, char *argv[]) {

	char inBuf[BUFSIZE];
	char bitBuf[BUFSIZE*8];
	char modifiedBuf[BUFSIZE*8];
	char outBuf[BUFSIZE];

	int bytesRead = fread(inBuf, sizeof(char), BUFSIZE, stdin);
	int bitSize = bytesRead * 8;

	// printf("read %d\n", bytesRead);
	explode(inBuf, bytesRead, bitBuf);

	for (int skips=0; skips < 400; skips++) {
		reflow(bitBuf, modifiedBuf, bitSize, skips);
		implode(modifiedBuf, bitSize, outBuf);
		saveBuffer(skips, outBuf, bytesRead);
	}

	//fwrite(bitBuf, sizeof(char), bytesRead * 8, stdout);
}
