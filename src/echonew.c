#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 256 // length in chars of the buffer to be read

// function declaration
int str_length();
char *read_stdin();
char last_char();

int main(int argc, char **argv) { // main function
	if (argc>1) { // if there are arguments, print those
		for (int i=1; i<argc; i++) {
			printf("%s ",argv[i]);
		} printf("\n"); // add new line since arguments will not have it by default
	} else { // else use stdin
		char *input = read_stdin();
		printf("%s\n",input);
	}
	return 0;
}

// functions definition
char *read_stdin(){ // dynamically read input from stdin
	// variable initialization
	char *buf = malloc(sizeof(char)*BUFSIZE); // temporary buffer to be read
	char *str = malloc(sizeof(char)*BUFSIZE); // char array to hold the total string
	size_t str_s = 0; // char index of the buffer that's been read

	// read stdin until EOF is found
	char c1; // char to store the value to get checked
	while ((c1 = getc(stdin)) != EOF) {
		// replace checked char back into stdin
		ungetc(c1, stdin);

		// read BUFSIZE (-1 due to the null terminator)  chars from stdin into buffer
		fgets(buf, BUFSIZE, stdin);

		// create a temporary buffer the size of the new full string
		size_t temp_s = str_length(str)+BUFSIZE; // increase existing str by BUFSIZE
		char *temp = (char *)malloc(temp_s);

		// copy to temp from str
		memcpy(temp, str, str_length(str)*sizeof(char));
		// copy to temp from buf
		memcpy(temp+(str_length(str)*sizeof(char)), buf, BUFSIZE);

		// reallocate memory for str
		str_s+=BUFSIZE;
		str=realloc(str, str_s*sizeof(char));
		// copy to str from temp
		memcpy(str, temp, temp_s*sizeof(char));

		free(temp);
	}
	//str[str_length(str)-1]='\0'; // remove newline that gets appended from STDIN
	return str;
}

int str_length(char *buf) { // get length of given string
	int length = 0;
	for (int i=0; buf[i] != '\0'; i++) {
		length ++;
	}
	return length;
}

char last_char(char *buf) { // get last character of buffer
	return buf[str_length(buf)-1];
}
