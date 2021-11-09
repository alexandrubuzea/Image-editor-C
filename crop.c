// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include "alloc.h"
#include "dealloc.h"
#include "color.h"
#include "selected.h"

// a function that cropps a gray/black&white image after the selection
void crop_image(unsigned char ***image, int *n, int *m, selected_t *area)
{
	// determine width and height of the new image
	int width = (area->x2) - (area->x1);
	int height = (area->y2) - (area->y1);

	// declaration and initialization of the new image, the cropped image
	unsigned char **crimage;
	crimage = NULL;

	// allocation of the new image, given the dimensions
	alloc_image(&crimage, width, height);

	// copying each pixel to the new image
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			crimage[i][j] = (*image)[(area->y1) + i][(area->x1) + j];

	// deallocation of the old image #livingponies
	dealloc_image(image, *m);

	// linking the pointer to the new matrix
	*image = crimage;

	// updating the selected area: at the present time all image is selected
	area->x1 = 0;
	area->y1 = 0;
	area->x2 = width;
	area->y2 = height;

	// updating the dimensions of the new image
	*n = width;
	*m = height;
}

// a more esthetical way to execute shallow copy, although it's not necessary
void shallow_copy(color_t *s1, const color_t *s2)
{
	// copying the values of each field of the structure
	s1->red = s2->red;
	s1->green = s2->green;
	s1->blue = s2->blue;
}

// a function that cropps a color image after the selection
void crop_colimage(color_t ***colimage, int *n, int *m, selected_t *area)
{
	// determine the dimensions of the new image
	int width = (area->x2) - (area->x1);
	int height = (area->y2) - (area->y1);

	// declaration and initialization of the new image
	color_t **crcolimage;
	crcolimage = NULL;

	// allocation of the new image
	alloc_colimage(&crcolimage, width, height);

	// copying the pixels form old image to the new image
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			shallow_copy(&crcolimage[i][j],
						 &(*colimage)[(area->y1) + i][(area->x1) + j]);

	// deallocation of the old image
	dealloc_colimage(colimage, *m);

	// linking the old image pointer to the new image
	*colimage = crcolimage;

	// updating the seleccted area
	area->x1 = 0;
	area->y1 = 0;
	area->x2 = width;
	area->y2 = height;

	// updating the dimensions
	*n = width;
	*m = height;
}

// a function that cropps an image, no matter what is its type
// basically the logical structure of the CROP function
void crop(unsigned char ***image, color_t ***colimage, int *n, int *m,
		  selected_t *area)
{
	// if no image is loaded, the expected output is printed
	if (!*image && !*colimage) {
		printf("No image loaded\n");
		return;
	}

	// if the gray/black&white image exists, crop the selection
	if (*image) {
		crop_image(image, n, m, area);
		printf("Image cropped\n");
		return;
	}

	// if the color image exists, crop the selection
	if (*colimage) {
		crop_colimage(colimage, n, m, area);
		printf("Image cropped\n");
		return;
	}
}
