// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdlib.h>
#include "color.h"

// a function that executes the deallocation of a gray/black&white image
void dealloc_image(unsigned char ***image, int m)
{
	// free the arrays that are in the structure of the matrix/image
	for (int i = 0; i < m; ++i)
		free(*(*image + i));

	// free the array of pointers
	free(*image);

	// prepare the pointer for another LOAD operation possibly in coming
	*image = NULL;
}

// a function that executes the deallocation of a gray/black&white image
void dealloc_colimage(color_t ***colimage, int m)
{
	// free the arrays that are in the structure of the matrix/image
	for (int i = 0; i < m; ++i)
		free(*(*colimage + i));

	// free the array of pointers
	free(*colimage);

	// prepare the pointer for another LOAD operation possibly in coming
	*colimage = NULL;
}
