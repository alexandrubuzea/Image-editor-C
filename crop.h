// Buzea Alexandru-Mihai-Iulian 311CAb

#ifndef CROP_H_
#define CROP_H_

#include "color.h"
#include "selected.h"

void crop_image(unsigned char ***image, int *n, int *m, selected_t *area);
void shallow_copy(color_t *s1, const color_t *s2);
void crop_colimage(color_t ***colimage, int *n, int *m, selected_t *area);
void crop(unsigned char ***image, color_t ***colimage, int *n, int *m,
		  selected_t *area);

#endif
