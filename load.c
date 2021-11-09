// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "selected.h"
#include "alloc.h"
#include "dealloc.h"

#define N 5

// a function that is used to skip comments in a file, no matter the type
void skip_comms(FILE *in)
{
	char garbage, trash;
	fscanf(in, " %c%c", &garbage, &trash); // read 2 characters

	// if the first non-whitespace is not #, there is no point in
	// continuing the function, because we don't have comments here
	if (garbage != '#') {
		fseek(in, -2, SEEK_CUR);
		return;
	}

	// I need to exit this "while" when garbage is a newline and the next
	// character is not an #, so I negate using DeMorgan rules
	while (garbage != '\n' || trash == '#') {
		garbage = trash;
		fscanf(in, "%c", &trash);
	}

	// the last read character is redundant or is a pixel/ some important data
	fseek(in, -1, SEEK_CUR);
}

// parsing the gray/black&white image from ASCII file
void scan_image(unsigned char **image, int n, int m, FILE *in)
{
	// scanning with int datatype allows to skip whitespaces
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			int value;
			fscanf(in, "%d", &value);
			image[i][j] = (unsigned char)value;
		}
	}
}

// parsing a pixel in a color image from ASCII format
void scan_color(FILE *in, color_t *s)
{
	int value;
	fscanf(in, "%d", &value);
	s->red = (unsigned char)value;
	fscanf(in, "%d", &value);
	s->green = (unsigned char)value;
	fscanf(in, "%d", &value);
	s->blue = (unsigned char)value;
}

// parsing the whole color image from ASCII format
void scan_colimage(color_t **image, int n, int m, FILE *in)
{
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			scan_color(in, &image[i][j]);
}

// parsing the black&white/gray image from binary file
void read_image(unsigned char **image, int n, int m, FILE *in)
{
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			fread(&image[i][j], sizeof(unsigned char), 1, in);
}

// parsing the color image from binary file
void read_colimage(color_t **colimage, int n, int m, FILE *in)
{
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			fread(&colimage[i][j], sizeof(color_t), 1, in);
}

// a function that parses the P1 file format (as described in the README)
void load_p1(unsigned char ***image, int *n, int *m, FILE *in)
{
	skip_comms(in); // there could be comments here
	fscanf(in, "%d%d", n, m); // read the dimensions
	skip_comms(in); // there could be comments here

	// allocation and parsing of a matrix with given dimensions
	alloc_image(image, *n, *m);
	scan_image(*image, *n, *m, in);
}

// a function that parses the P2 file format (as described in the README)
void load_p2(unsigned char ***image, int *n, int *m, int *maxvalue, FILE *in)
{
	skip_comms(in); // there could be comments here
	fscanf(in, "%d%d", n, m);
	skip_comms(in); // there could be comments here

	// reading the maximal value
	fscanf(in, "%d", maxvalue);

	// allocation and parsing of image in a matrix with given dimensions
	alloc_image(image, *n, *m);
	scan_image(*image, *n, *m, in);
}

// a function that parses the P3 file format (as described in the README)
void load_p3(color_t ***colimage, int *n, int *m, int *maxvalue, FILE *in)
{
	skip_comms(in); // there could be comments here
	fscanf(in, "%d%d", n, m);
	skip_comms(in); // there could be comments here
	fscanf(in, "%d", maxvalue);

	// allocation and parsing of image in a matrix with given dimensions
	alloc_colimage(colimage, *n, *m);
	scan_colimage(*colimage, *n, *m, in);
}

// a function that parses the P4 file format (as described in the README)
void load_p4(unsigned char ***image, int *n, int *m, FILE **in, char *filename)
{
	skip_comms(*in); //there could be comments here
	fscanf(*in, "%d%d", n, m);
	fseek(*in, 1, SEEK_CUR); // skip the '\n' character

	// allocation of the matrix
	alloc_image(image, *n, *m);

	// record the position of the cursor
	long position = ftell(*in);
	fclose(*in);

	// open the file in binary mode, and move the cursor to the beginning of
	// the image
	*in = fopen(filename, "rb");
	fseek(*in, position, SEEK_SET);
	read_image(*image, *n, *m, *in);
}

void load_p5(unsigned char ***image, int *n, int *m, int *maxvalue,
			 FILE **in, char *filename)
{
	skip_comms(*in); // there could be comments here
	fscanf(*in, "%d%d", n, m);
	skip_comms(*in); // there could be comments here
	fscanf(*in, "%d", maxvalue);
	fseek(*in, 1, SEEK_CUR); // skip the '\n' character

	// allocation of the matrix
	alloc_image(image, *n, *m);

	// record the position of the cursor
	long position = ftell(*in);
	fclose(*in);

	// open the file in binary mode and parsing
	*in = fopen(filename, "rb");
	fseek(*in, position, SEEK_SET);
	read_image(*image, *n, *m, *in);
}

void load_p6(color_t ***colimage, int *n, int *m, int *maxvalue,
			 FILE **in, char *filename)
{
	skip_comms(*in); // there could be comments here
	fscanf(*in, "%d%d", n, m);
	skip_comms(*in); // there could be comments here
	fscanf(*in, "%d", maxvalue);
	fseek(*in, 1, SEEK_CUR); // skip the '\n' character

	// allocation of the matrix (for color image)
	alloc_colimage(colimage, *n, *m);

	//record the position of the cursor
	long position = ftell(*in);
	fclose(*in);

	// open the file in binary mode and parsing
	*in = fopen(filename, "rb");
	fseek(*in, position, SEEK_SET);
	read_colimage(*colimage, *n, *m, *in);
}

// the main logical sequence for LOAD command
void load_image(unsigned char ***image, color_t ***colimage, int *n, int *m,
				int *maxvalue, char *command, char *type, selected_t *area)
{
	// if there is no image loaded, print the expected output
	if (*image)
		dealloc_image(image, *m);
	if (*colimage)
		dealloc_colimage(colimage, *m);

	// preparing the delimeter's string for strtok
	char delim[] = "\t\n ";

	//first token, the "LOAD" command
	char *filename = strtok(command, delim);

	// second token, which is the file name
	filename = strtok(NULL, delim);

	// if there is no filename, the format does not match the known pattern
	if (!filename) {
		printf("Invalid command\n");
		return;
	}

	// opening the file for parsing
	FILE *in = fopen(filename, "rt");
	if (!in) {
		printf("Failed to load %s\n", filename);
		return;
	}

	// reading the filetype (P1-6)
	fgets(type, N, in);
	type[strlen(type) - 1] = '\0'; // getting rid of '\n'

	// if type is P1 or P4, there is no maxvalue
	if (strstr("P1P4", type))
		*maxvalue = 0;

	// having all posibilities in consideration
	if (strcmp(type, "P1") == 0)
		load_p1(image, n, m, in);
	if (strcmp(type, "P2") == 0)
		load_p2(image, n, m, maxvalue, in);
	if (strcmp(type, "P3") == 0)
		load_p3(colimage, n, m, maxvalue, in);
	if (strcmp(type, "P4") == 0)
		load_p4(image, n, m, &in, filename);
	if (strcmp(type, "P5") == 0)
		load_p5(image, n, m, maxvalue, &in, filename);
	if (strcmp(type, "P6") == 0)
		load_p6(colimage, n, m, maxvalue, &in, filename);
	if (*image || *colimage)
		printf("Loaded %s\n", filename);

// update the selected area
	area->x1 = 0;
	area->x2 = *n;
	area->y1 = 0;
	area->y2 = *m;

	fclose(in);
}
