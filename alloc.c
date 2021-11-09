// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdlib.h>
#include "color.h"

// a function that dinamically allocs memory for a gray/black&white image
void alloc_image(unsigned char ***image, int n, int m)
{
	// allocation of an array of pointers to unsigned char
	unsigned char **tmp = (unsigned char **)
						malloc(m * sizeof(unsigned char *));

	// check if allocation has been done succesfully
	if (!tmp)
		exit(1);

	// linking the gray/black&white image to the array of pointers
	*image = tmp;

	// allocation of multiple arrays - allocating a matrix with constant length
	for (int i = 0; i < m; ++i) {
		unsigned char *temp = (unsigned char *)
								malloc(n * sizeof(unsigned char));

		// check if allocation has been done succesfully
		if (!temp)
			exit(1);

		// linking the pointer to the array of unsigned chars
		*(*image + i) = temp;
	}
}

// a function that dinamically allocs memory for a color image
void alloc_colimage(color_t ***colimage, int n, int m)
{
	// allocation of an array of pointers to color_t
	color_t **tmp = (color_t **)malloc(m * sizeof(color_t *));

	// check if allocation has been done succesfully
	if (!tmp)
		exit(1);

	// linking the color image to the array of pointers
	*colimage = tmp;

	// allocation of the each pointer from array - building a matrix
	for (int i = 0; i < m; ++i) {
		color_t *temp = (color_t *)malloc(n * sizeof(color_t));

		// check if allocation has been done successfully
		if (!temp)
			exit(1);

		// linking the pointer to the array of pixels/color_t structures
		*(*colimage + i) = temp;
	}
}
