// Buzea Alexandru-Mihai-Iulian 311CAb

#ifndef ROTATE_H_
#define ROTATE_H_

#include "color.h"
#include "selected.h"

void swap_int(int *p, int *q);
void swap_uchar(unsigned char *p, unsigned char *q);
void swap_color(color_t *a, color_t *b);
int check_number(char *str);
void rotate_all_90(unsigned char ***image, int *n, int *m, selected_t *area);
void rotate_90(unsigned char ***image, selected_t *area);
void rotate_180(unsigned char ***image, selected_t *area);
void rotate_all_270(unsigned char ***image, int *n, int *m, selected_t *area);
void rotate_270(unsigned char ***image, selected_t *area);
void rotate_image(unsigned char ***image, selected_t *area, int *n, int *m,
				  int initial_angle, int theta, int all);
void rotate_col_all_90(color_t ***colimage, int *n, int *m, selected_t *area);
void rotate_col_90(color_t ***colimage, selected_t *area);
void rotate_col_180(color_t ***colimage, selected_t *area);
void rotate_col_all_270(color_t ***colimage, int *n, int *m, selected_t *area);
void rotate_col_270(color_t ***colimage, selected_t *area);
void rotate_colimage(color_t ***colimage, selected_t *area, int *n, int *m,
					 int initial_angle, int theta, int all);
void rotate(unsigned char ***image, color_t ***colimage, selected_t *area,
			int *n, int *m, char *command);

#endif
