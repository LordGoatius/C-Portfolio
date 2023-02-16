#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBERS_ARGS 1

//parse command line
FILE* parseCommandLine(int argc, char** argv, int* bits) {
	if (argc > 2) {
		printf("Usage: %s [-b]|-bits]\n", argv[0]);
		exit(BAD_NUMBERS_ARGS);
	}
	if (argc == 2 && (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
		*bits = TRUE;
	}
	else {
		*bits = FALSE;
	}
	return stdin;
}

void printDataAsHex(unsigned char* data, size_t size) {
	unsigned int* output[16];
	//printf("%02x", temp);

	for (int i = 0; i < size; i++) {
		output[i] = (int)data[i];
	}

	for (int i = 0; i < size - 2; i += 2) {
		printf("%02x%02x ", output[i], output[i + 1]);
	}
	printf("%02x%02x", output[size - 2], output[size - 1]);

}

void printDataAsChars(unsigned char* data, size_t size) {
	//prints as chars
	printf("%s", data);
}

void printDataAsBits(unsigned char* data, size_t size) {
	printf("TODO");
}

void readAndPrintInputAsHex(FILE* input) {
	unsigned char data[16];
	int numBytesRead = fread(data, 1, 16, input);
	unsigned int offset = 0;
	while (numBytesRead != 0) {
		printf("%08x:", offset);
		offset += numBytesRead;
		printDataAsHex(data, numBytesRead);
		printf("  ");
		printDataAsChars(data, numBytesRead);
		printf("\n");
		numBytesRead = fread(data, 1, 16, input);
	}
}

void readAndPrintInputAsBits(FILE* input) {
	//read and print as bits
	unsigned char data[16];
	int numBytesRead = fread(data, 1, 16, input);
	unsigned int offset = 0;
	while (numBytesRead != 0) {
		printf("%08x:", offset);
		offset += numBytesRead;
		printDataAsBits(data, numBytesRead);
		printf("  ");
		printDataAsChars(data, numBytesRead);
		printf("\n");
		numBytesRead = fread(data, 1, 16, input);
	}

}

int main(int argc, char* argv[]) {
	int bits = FALSE;
	FILE* input = parseCommandLine(argc, argv, &bits);

	if (bits == FALSE) {
		readAndPrintInputAsHex(input);
	}
	else {
		readAndPrintInputAsBits(input);
	}
	return 0;
}