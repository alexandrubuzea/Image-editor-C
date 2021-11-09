// Buzea Alexandru-Mihai-Iulian 311CAb

#ifndef SELECT_H_
#define SELECT_H_

#include "color.h"
#include "selected.h"

void swap(int *p, int *q);
int is_number(char *str);
void select_area(unsigned char **image, color_t **colimage, int n,
				 int m, selected_t *area, char *command);

#endif
