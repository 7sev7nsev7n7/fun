#include <stdio.h>

int main(int argc, char **argv) { // main function
	// iterate over arguments in **argv
	for (int i=1; i<argc; i++) {
		FILE *file;
		if (file = fopen(*(argv+i), "r")) { // if file exists, read data
			char ch;
			while ((ch = fgetc(file)) != EOF) {
				putchar(ch);
			}
			fclose(file); // close file stream before ending loop
		} else { // else print error message
			fprintf(stderr, "catnew: %s: No such file or directory\n", *(argv+i));
		}
	}
}
