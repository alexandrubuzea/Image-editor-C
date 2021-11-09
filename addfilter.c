// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "color.h"
#include "selected.h"

// classical function for minimal value betwwen two numbers
int minimal_value(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

// a function that turns a colored pixel into a gray pixel
void grayscale(color_t *s)
{
	// using double datatype in order to use round() function
	// for better results
	double newvalue = (double)(s->red);
	newvalue += (double)(s->green);
	newvalue += (double)(s->blue);
	newvalue /= 3;

	// finding the closest integer, in order to convert to our datatype
	newvalue = round(newvalue);

	// each elementary color must have the same ratio in order to display
	// a suitable grayscale image
	s->red = (unsigned char)newvalue;
	s->green = (unsigned char)newvalue;
	s->blue = (unsigned char)newvalue;
}

// adding grayscale filter to the whole selection
void add_grayscale(color_t **colimage, selected_t *area)
{
	for (int i = (area->y1); i < (area->y2); ++i)
		for (int j = (area->x1); j < (area->x2); ++j)
			grayscale(&colimage[i][j]);
}

// a function that adds the sepia filter to a single pixel
void sepia(color_t *s, int maxvalue)
{
	// used double datatype for better precision and better results
	// determined the new percentages of elemetary colors based on the
	// following equations:

	// for red: newRED = 0.393 * RED + 0.769 GREEN + 0.189 BLUE
	double nwred = 0.393 * (double)(s->red);
	nwred += 0.769 * (double)(s->green);
	nwred += 0.189 * (double)(s->blue);

	// for green: newGREEN = 0.349 * RED + 0.686 * GREEN + 0.168 * BLUE
	double nwgreen = 0.349 * (double)(s->red);
	nwgreen += 0.686 * (double)(s->green);
	nwgreen += 0.168 * (double)(s->blue);

	// for blue: newBLUE = 0.272 * RED + 0.534 * GREEN + 0.131 * BLUE
	double nwblue = 0.272 * (double)(s->red);
	nwblue += 0.534 * (double)(s->green);
	nwblue += 0.131 * (double)(s->blue);

	// round the double values - preparing for cast into integer types
	nwred = round(nwred);
	nwgreen = round(nwgreen);
	nwblue = round(nwblue);

	// update the value of the each elemetary color
	s->red = (unsigned char)minimal_value((int)nwred, maxvalue);
	s->green = (unsigned char)minimal_value((int)nwgreen, maxvalue);
	s->blue = (unsigned char)minimal_value((int)nwblue, maxvalue);
}

// a function that adds the sepia filter to the whole selection
void add_sepia(color_t **colimage, selected_t *area, int maxvalue)
{
	for (int i = (area->y1); i < (area->y2); ++i)
		for (int j = area->x1; j < (area->x2); ++j)
			sepia(&colimage[i][j], maxvalue);
}

// a function that treats all possible situations, and that applies the
// desired filter to the image (only if it is color)
void add_filter(unsigned char **image, color_t **colimage, char *comtype,
				selected_t *area, int maxvalue)
{
	// if no image is loaded, there is no point in continuing this function
	if (!image && !colimage) {
		printf("No image loaded\n");
		return;
	}

	// if the GRAYSCALE filter is the one who needs to be applied
	if (!strcmp(comtype, "GRAYSCALE")) {
		if (image) { // Gray and black&white images are not suitable
			printf("Grayscale filter not available\n");
			return;
		}
		add_grayscale(colimage, area); // adding GRAYSCALE
		printf("Grayscale filter applied\n");
		return;
	}

	// if the SEPIA filter is the one who needs to be applied
	if (!strcmp(comtype, "SEPIA")) {
		if (image) { // Gray and black&white images are not suitable
			printf("Sepia filter not available\n");
			return;
		}
		add_sepia(colimage, area, maxvalue); // adding SEPIA
		printf("Sepia filter applied\n");
	}
}
