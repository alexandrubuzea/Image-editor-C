// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "selected.h"
#include "dealloc.h"

// a function that executes the EXIT command: deallocation of all resources
void exit_editor(unsigned char ***image, color_t ***colimage, int m)
{
	// if no image is loaded, the expected output is printed
	if (!*image && !*colimage) {
		printf("No image loaded\n");
		return;
	}

	// if the gray/black&white image is loaded, the deallocation is realised
	if (*image)
		dealloc_image(image, m);

	// if the color image is loaded, the deallocation is realised
	if (*colimage)
		dealloc_colimage(colimage, m);
}
