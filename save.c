// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <string.h>
#include "color.h"
#include "selected.h"

// a function that saves the gray/black&white image in an ASCII file
void save_image_ascii(unsigned char **image, int n, int m, FILE **out)
{
	// printing each pixel from the image
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j)
			fprintf(*out, "%d ", (int)(image[i][j]));
		// print '\n' at the end of each line
		fprintf(*out, "\n");
	}

	fclose(*out); // no memory leaks
}

// a function that saves the gray/black&white image in a binary file
void save_image_binary(unsigned char **image, int n, int m, FILE **out,
					   char *filename)
{
	fclose(*out); // close the file in order to open it in append binary mode
	*out = fopen(filename, "ab");

	// write each pixel from image
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			fwrite(&image[i][j], sizeof(unsigned char), 1, *out);

	fclose(*out); // no memory leaks
}

// a function that saves the color image in an ASCII file
void save_colimage_ascii(color_t **colimage, int n, int m, FILE **out)
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			// print each field of the structure
			fprintf(*out, "%d ", (int)colimage[i][j].red);
			fprintf(*out, "%d ", (int)colimage[i][j].green);
			fprintf(*out, "%d ", (int)colimage[i][j].blue);
		}
		// print '\n' at the end of each line
		fprintf(*out, "\n");
	}

	fclose(*out); // no memory leaks
}

void save_colimage_binary(color_t **colimage, int n, int m, FILE **out,
						  char *filename)
{
	fclose(*out); // close the file in order to open it in append binary mode
	*out = fopen(filename, "ab");

	// write each pixel in the binary file
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			fwrite(&colimage[i][j], sizeof(color_t), 1, *out);

	fclose(*out); // no memory leaks
}

void save(unsigned char **image, color_t **colimage, char *command,
		  int n, int m, char *type, int maxvalue)
{
	// if no image is loaded, the expected output is printed
	if (!image && !colimage) {
		printf("No image loaded\n");
		return;
	}
	// prepare to use strtok
	char delim[] = "\n\t ";

	char *filename = strtok(command, delim); // the first token
	filename = strtok(NULL, delim); // the second token, the filename

	// filetype is "ascii" for ASCII file and NULL for binary file
	char *filetype = strtok(NULL, delim);

	FILE *out = fopen(filename, "wt");

	// if the image is black&white
	if (strstr("P1P4", type)) {
		if (!filetype)
			strcpy(type, "P4");
		else
			strcpy(type, "P1");
	}

	//if the image is gray
	if (strstr("P2P5", type)) {
		if (!filetype)
			strcpy(type, "P5");
		else
			strcpy(type, "P2");
	}

	// if the image is color
	if (strstr("P3P6", type)) {
		if (!filetype)
			strcpy(type, "P6");
		else
			strcpy(type, "P3");
	}

	// printing the type, dimensions and maxvalue according to each format
	fprintf(out, "%s\n", type);
	fprintf(out, "%d %d\n", n, m);
	if (maxvalue)
		fprintf(out, "%d\n", maxvalue);

	if (image && !filetype) { // save a gray/black&white image in binary file
		save_image_binary(image, n, m, &out, filename);
		printf("Saved %s\n", filename);
		return;
	}

	if (colimage && !filetype) { // save a color image in a binary file
		save_colimage_binary(colimage, n, m, &out, filename);
		printf("Saved %s\n", filename);
		return;
	}

	if (image && (!strcmp(filetype, "ascii"))) {
		// save the gray/black&white image in an ASCII file
		save_image_ascii(image, n, m, &out);
		printf("Saved %s\n", filename);
		return;
	}

	if (colimage && (!strcmp(filetype, "ascii"))) {
		// save the color image in an ASCII file
		save_colimage_ascii(colimage, n, m, &out);
		printf("Saved %s\n", filename);
		return;
	}
}
