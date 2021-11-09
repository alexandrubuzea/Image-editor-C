// Buzea Alexandru-Mihai-Iulian 311CAb

#ifndef ADDFILTER_H_
#define ADDFILTER_H_

#include "color.h"
#include "selected.h"

unsigned char maximal_value(unsigned char a, unsigned char b);
void grayscale(color_t *s);
void add_grayscale(color_t **colimage, selected_t *area);
void sepia(color_t *s, int maxvalue);
void add_sepia(color_t **colimage, selected_t *area, int maxvalue);
void add_filter(unsigned char **image, color_t **colimage, char *comtype,
				selected_t *area, int maxvalue);

#endif
