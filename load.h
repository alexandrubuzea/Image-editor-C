// Buzea Alexandru-Mihai-Iulian 311CAb

#ifndef LOAD_H_
#define LOAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "selected.h"

void skip_comms(FILE * in);
void scan_image(unsigned char **image, int n, int m, FILE *in);
void scan_color(FILE *in, color_t *s);
void scan_colimage(color_t **image, int n, int m, FILE *in);
void load_p1(unsigned char ***image, int *n, int *m, FILE *in);
void load_p2(unsigned char ***image, int *n, int *m, int *maxvalue, FILE *in);
void load_p3(color_t ***colimage, int *n, int *m, int *maxvalue, FILE *in);
void load_image(unsigned char ***image, color_t ***colimage, int *n, int *m,
				int *maxvalue, char *command, char *type, selected_t *area);

#endif
