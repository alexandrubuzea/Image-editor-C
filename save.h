// Buzea Alexandru-Mihai-Iulian 311CAb

#ifndef SAVE_H_
#define SAVE_H_

#include <stdio.h>
#include "color.h"
#include "selected.h"

void save_image_ascii(unsigned char **image, int n, int m, FILE * *out);
void save_image_binary(unsigned char **image, int n, int m, FILE **out,
					   char *filename);
void save_colimage_ascii(color_t **colimage, int n, int m, FILE **out);
void save_colimage_binary(color_t **colimage, int n, int m, FILE **out,
						  char *filename);
void save(unsigned char **image, color_t **colimage, char *command,
		  int n, int m, char *type, int maxvalue);

#endif
