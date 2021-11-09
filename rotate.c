// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "selected.h"
#include "alloc.h"
#include "dealloc.h"

// classical swap function for integer values
void swap_int(int *p, int *q)
{
	int aux = *p;
	*p = *q;
	*q = aux;
}

// classical swap function for unsigned char values
void swap_uchar(unsigned char *p, unsigned char *q)
{
	unsigned char aux = *p;
	*p = *q;
	*q = aux;
}

// classical swap function for color_t structure
void swap_color(color_t *a, color_t *b)
{
	color_t aux = *a;
	*a = *b;
	*b = aux;
}

// a function that checks if a certain string is a real number
int check_number(char *str)
{
	// to count the number of decimal dots (in order for the string to
	// be a real number, num_dots can be 0 or 1)
	int num_dots = 0;

	// the first character of a string is special, because it can be
	// '-', '.', or a digit
	if (!strchr("-.0123456789", str[0]))
		return 0;
	else if (str[0] == '.')
		++num_dots;

	// check for the other digits
	for (int i = 1; str[i] != 0; ++i) {
		if (!strchr(".0123456789", str[i]))
			return 0;
		if (str[i] == '.')
			++num_dots;
		if (num_dots > 1) // no more than 1 dot
			return 0;
	}
	return 1; // if all conditions are satisfied, the string is a number
}

// a function which rotates all image with 90 degrees to right
void rotate_all_90(unsigned char ***image, int *n, int *m, selected_t *area)
{
	// the dimnesions of the image are, in general, different
	// declaration and allocation of a new matrix
	unsigned char **cpimage;
	cpimage = NULL;
	alloc_image(&cpimage, *m, *n);

	// copying the pixels in the new image
	for (int i = 0; i < *m; ++i)
		for (int j = 0; j < *n; ++j)
			cpimage[j][*m - 1 - i] = (*image)[i][j];

	// deallocation of the old image
	dealloc_image(image, *m);

	// linking the old image pointer to the new matrix
	*image = cpimage;

	// in order to update dimensions, swap them
	swap_int(m, n);

	// update the selected area;
	area->x1 = 0;
	area->x2 = *n;
	area->y1 = 0;
	area->y2 = *m;
}

// a function which rotates only a square selection of the matrix
void rotate_90(unsigned char ***image, selected_t *area)
{
	// the selection is a square, so recording one dimension is enough
	int width = area->x2 - area->x1;

	// declaration allocation for the selected area (it is more convenient to
	// to the rotation this way)
	unsigned char **cpimage;
	alloc_image(&cpimage, width, width);

	// moving the elements from the selection in the new matrix and rotate
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < width; ++j)
			cpimage[j][width - 1 - i] = (*image)[area->y1 + i][area->x1 + j];

	// moving back the rotated elements into the image
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < width; ++j)
			(*image)[area->y1 + i][area->x1 + j] = cpimage[i][j];

	// final deallocation of the used matrix
	dealloc_image(&cpimage, width);
}

// a function that rotates with 180 degrees to the right any selection,
// no matter its dimensions
void rotate_180(unsigned char ***image, selected_t *area)
{
	// the selection is not necessarily a square, we need two dimensions
	int width = area->x2 - area->x1;
	int height = area->y2 - area->y1;

	// swapping the pixels with respect to one axis of symmetry
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width / 2; ++j) {
			swap_uchar(&(*image)[area->y1 + i][area->x1 + j],
					   &(*image)[area->y1 + i][area->x2 - j - 1]);
		}
	}

	// swapping the elements with respect to the other axis of symmetry
	for (int i = 0; i < height / 2; ++i) {
		for (int j = 0; j < width; ++j) {
			swap_uchar(&(*image)[area->y1 + i][area->x1 + j],
					   &(*image)[area->y2 - i - 1][area->x1 + j]);
		}
	}
}

// a function that rotates the whole image with 270 degrees to the right
// (or 90 degrees to the left)
void rotate_all_270(unsigned char ***image, int *n, int *m, selected_t *area)
{
	// declaration and allocation of the matrix in which we will copy
	// the rotated image
	unsigned char **cpimage;
	alloc_image(&cpimage, *m, *n);

	// copy the image into thw new matrix
	for (int i = 0; i < *m; ++i)
		for (int j = 0; j < *n; ++j)
			cpimage[*n - j - 1][i] = (*image)[i][j];

	// deallocation of the old image
	dealloc_image(image, *m);

	// linking the old pointer to the new matrix
	*image = cpimage;

	// after rotate, we need to swap dimensions
	swap_int(m, n);

	// update the selected area
	area->x1 = 0;
	area->y1 = 0;
	area->x2 = *n;
	area->y2 = *m;
}

// a function that rotates only a square selection, with 270 degrees to the
// right (or 90 degrees to the left)
void rotate_270(unsigned char ***image, selected_t *area)
{
	// since the selection is a square, we need to record only one dimension
	int width = (area->x2) - (area->x1);

	// allocation and initialization of the matrix in which we will copy the
	// pixels of the selected square area
	unsigned char **cpimage;
	cpimage = NULL;
	alloc_image(&cpimage, width, width);

	// copying the pixels and rotate
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < width; ++j)
			cpimage[width - 1 - j][i] =
					(*image)[(area->y1) + i][(area->x1) + j];

	// copying the pixels back in the image
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < width; ++j)
			(*image)[(area->y1) + i][(area->x1) + j] = cpimage[i][j];

	// deallocation of the square matrix
	dealloc_image(&cpimage, width);
}

// the logical structure for the rotation functions for gray/black&white image
void rotate_image(unsigned char ***image, selected_t *area, int *n, int *m,
				  int initial_angle, int theta, int all)
{
	// consider different cases for theta
	// case A: theta is 90 degrees to the right
	if (theta == 90 && all) { // case I : rotate all image
		rotate_all_90(image, n, m, area);
		printf("Rotated %d\n", initial_angle);
		return;
	}

	if (theta == 90 && area->x2 - area->x1 == area->y2 - area->y1) {
		rotate_90(image, area); // case II : rotate a square selection
		printf("Rotated %d\n", initial_angle);
		return;
	}
	if (theta == 90) { // case III : Other situations
		printf("The selection must be a square\n");
		return;
	}

	// case B: theta is 180 degrees (the direction does not matter, obviously)
	if (theta == 180) {
		rotate_180(image, area);
		printf("Rotated %d\n", initial_angle);
		return;
	}

	// case C: theta is 270 degrees to the right (or 90 degrees to the left)
	if (theta == 270 && all) { // case I: rotate all image
		rotate_all_270(image, n, m, area);
		printf("Rotated %d\n", initial_angle);
		return;
	}
	if (theta == 270 && (area->x2 - area->x1 == area->y2 - area->y1)) {
		rotate_270(image, area); // case II: rotate a square selection
		printf("Rotated %d\n", initial_angle);
		return;
	} else if (theta == 270) { // case III: other situations
		printf("The selection must be a square\n");
		return;
	}
}

// a function which rotates a whole color image 90 degrees to the right
void rotate_col_all_90(color_t ***colimage, int *n, int *m, selected_t *area)
{
	// declaration and allocation of the copy matrix
	color_t **cpcolimage;
	alloc_colimage(&cpcolimage, *m, *n);

	// copying and rotating the pixels
	for (int i = 0; i < *m; ++i)
		for (int j = 0; j < *n; ++j)
			cpcolimage[j][*m - 1 - i] = (*colimage)[i][j];

	// deallocation of the color image
	dealloc_colimage(colimage, *m);

	//linking the old color image pointer to the new rotated image
	*colimage = cpcolimage;

	// update dimensions
	swap_int(m, n);

	// update selection
	area->x1 = 0;
	area->x2 = *n;
	area->y1 = 0;
	area->y2 = *m;
}

// a function which rotates a square selection of the image
void rotate_col_90(color_t ***colimage, selected_t *area)
{
	// record the dimension of the square selection
	int width = area->x2 - area->x1;

	// allocation and declaration for the copy matrix
	color_t **cpcolimage;
	alloc_colimage(&cpcolimage, width, width);

	// copy and rotate pixels
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < width; ++j) {
			cpcolimage[j][width - 1 - i] =
			(*colimage)[area->y1 + i][area->x1 + j];
		}
	}

	// copy the rotated pixels back in the image
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < width; ++j)
			(*colimage)[area->y1 + i][area->x1 + j] = cpcolimage[i][j];

	// deallocation of the matrix used to copy pixels
	dealloc_colimage(&cpcolimage, width);
}

// a function which rotates an image to 180 degrees, no matter which is
// the selection
void rotate_col_180(color_t ***colimage, selected_t *area)
{
	// record the dimensions of the matrix
	int width = area->x2 - area->x1;
	int height = area->y2 - area->y1;

	// swapping the pixels with respect to one axis of symmetry
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width / 2; ++j) {
			swap_color(&(*colimage)[area->y1 + i][area->x1 + j],
					   &(*colimage)[area->y1 + i][area->x2 - j - 1]);
		}
	}

	// swapping the pixels with respect to the other axis of symmetry
	for (int i = 0; i < height / 2; ++i) {
		for (int j = 0; j < width; ++j) {
			swap_color(&(*colimage)[area->y1 + i][area->x1 + j],
					   &(*colimage)[area->y2 - i - 1][area->x1 + j]);
		}
	}
}

// a function which rotates a color image with 270 degrees to right (or 90
// degrees to the left)
void rotate_col_all_270(color_t ***colimage, int *n, int *m, selected_t *area)
{
	// declaration and allocation of the new color image
	color_t **cpcolimage;
	alloc_colimage(&cpcolimage, *m, *n);

	// copying the pixels in the new color image
	for (int i = 0; i < *m; ++i)
		for (int j = 0; j < *n; ++j)
			cpcolimage[*n - j - 1][i] = (*colimage)[i][j];

	// deallocation of the old color image
	dealloc_colimage(colimage, *m);

	// linking the old image pointer to the new image
	*colimage = cpcolimage;

	// update (swapping) the dimensions of the image
	swap_int(m, n);

	// update the selection
	area->x1 = 0;
	area->y1 = 0;
	area->x2 = *n;
	area->y2 = *m;
}

// a function that rotates a square selection with 270 degrees to the right
void rotate_col_270(color_t ***colimage, selected_t *area)
{
	// record the dimension of the square selection
	int width = area->x2 - area->x1;

	// allocation and declaration of the color matrix in which we will copy
	// the pixels of square selection
	color_t **cpcolimage;
	cpcolimage = NULL;
	alloc_colimage(&cpcolimage, width, width);

	// the copying and rotation of the pixels
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < width; ++j) {
			cpcolimage[width - 1 - j][i] =
				(*colimage)[area->y1 + i][area->x1 + j];
		}
	}

	// copying back in the color image the rotated pixels
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < width; ++j)
			(*colimage)[area->y1 + i][area->x1 + j] = cpcolimage[i][j];

	// deallocation for the matrix used in rotation
	dealloc_colimage(&cpcolimage, width);
}

// the logical structure for the rotation functions for color images
void rotate_colimage(color_t ***colimage, selected_t *area, int *n, int *m,
					 int initial_angle, int theta, int all)
{
	// taking into consideration different cases
	// case A: theta/rotation angle is 90 degrees to the right
	if (theta == 90 && all) {
		// case I: all image is selected
		rotate_col_all_90(colimage, n, m, area);
		printf("Rotated %d\n", initial_angle);
		return;
	}

	if (theta == 90 && area->x2 - area->x1 == area->y2 - area->y1) {
		// case II: only a square area is selected
		rotate_col_90(colimage, area);
		printf("Rotated %d\n", initial_angle);
		return;
	}

	if (theta == 90) {
		// case III: other situations (selected area is not a square)
		printf("The selection must be a square\n");
		return;
	}

	// case B: theta is 180 degrees, no matter the selection or the direction
	if (theta == 180) {
		rotate_col_180(colimage, area);
		printf("Rotated %d\n", initial_angle);
		return;
	}

	// case C: theta is 270 degrees to the right
	// case I: all image is selected
	if (theta == 270 && all) {
		rotate_col_all_270(colimage, n, m, area);
		printf("Rotated %d\n", initial_angle);
		return;
	}

	// case II: just a square area is selected
	if (theta == 270 && area->x2 - area->x1 == area->y2 - area->y1) {
		rotate_col_270(colimage, area);
		printf("Rotated %d\n", initial_angle);
		return;
	} else if (theta == 270) {
		// case III: Other situations, such as the selection is not a square
		printf("The selection must be a square\n");
		return;
	}
}

// the main logical structure for ROTATION command, no matter the image type
void rotate(unsigned char ***image, color_t ***colimage, selected_t *area,
			int *n, int *m, char *command)
{
	// if no image is loaded, both pointers are NULL
	if (!*image && !*colimage) {
		printf("No image loaded\n");
		return;
	}

	char delim[] = "\n\t "; // prepare for using strtok

	// extract the first token, the command type "ROTATE"
	char *angle = strtok(command, delim);

	// extract the second token, the angle
	angle = strtok(NULL, delim);

	// analyzing the different situations based on the extracted angle
	// if no angle is entered, the whole command is invalid
	if (!angle) {
		printf("Invalid command\n");
		return;
	}

	// if the angle is not a number, the whole command is invalid
	if (!check_number(angle)) {
		printf("Invalid command");
		return;
	}

	// if the angle is a real number, it is obviously an unsupported angle
	if (check_number(angle) && strchr(angle, '.')) {
		printf("Unsupported rotation angle\n");
		return;
	}

	// one case remains: the angle is an integer
	int theta = atoi(angle);

	int initial_angle = theta; // for printing the input angle
	if (theta < 0) {
		theta = (theta % 360);
		if (theta < 0)
			theta += 360; // bring the angle to the first circle
	} else {
		theta = theta % 360;
	}
	if (theta % 90) { // only multiple of 90 degrees are valid
		printf("Unsupported rotation angle\n");
		return;
	}

	int all = 0; // tells us if the whole image is selected
	if (area->x1 == 0 && area->x2 == *n)
		if (area->y1 == 0 && area->y2 == *m)
			all = 1;

	if (*image) {
		if (!theta) { // if initial angle was 0 or a multiple of 360 degrees
			printf("Rotated %d\n", initial_angle);
			return;
		}
		rotate_image(image, area, n, m, initial_angle, theta, all);
		return;
	}

	if (*colimage) {
		if (!theta) { // if initial angle was 0 or a multiple of 360 degrees
			printf("Rotated %d\n", initial_angle);
			return;
		}
		rotate_colimage(colimage, area, n, m, initial_angle, theta, all);
		return;
	}
}
