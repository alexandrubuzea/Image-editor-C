// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "selected.h"

// classical swap function for integer values
void swap(int *p, int *q)
{
	int aux = *p;
	*p = *q;
	*q = aux;
}

// a function which checks if a number is an integer
int is_number(char *str)
{
	if (!strchr("-0123456789", str[0]))
		return 0;
	for (int i = 1; str[i]; ++i)
		if (!strchr("0123456789", str[i]))
			return 0;
	return 1;
}

// a function that updates the selected_t struct and the selected area
void select_area(unsigned char **image, color_t **colimage, int n,
				 int m, selected_t *area, char *command)
{
	char delim[] = "\n\t "; // prepare to apply strtok

	if (!image && !colimage) { // if no image is loaded, print expected output
		printf("No image loaded\n");
		return;
	}

	char *token = strtok(command, delim); // first token, the "SELECT" command
	token = strtok(NULL, delim);
	if (!token) {
		printf("Invalid command\n");
		return;
	}

	if (!strcmp(token, "ALL")) { // special "SELECT ALL" case
		printf("Selected ALL\n");
		area->x1 = 0;
		area->y1 = 0;
		area->x2 = n;
		area->y2 = m;
		return;
	}

	if (!is_number(token)) { // if is not a number, the pattern does not match
		printf("Invalid command\n"); // the established format
		return;
	}
	int x1 = atoi(token); // first integer token

	token = strtok(NULL, delim); // the third token
	if (!token) {
		printf("Invalid command\n");
		return;
	}
	if (!is_number(token)) { // if token is NULL, the pattern does not match
		printf("Invalid command\n"); // the established format
		return;
	}
	int y1 = atoi(token); // the second integer

	token = strtok(NULL, delim); // extracting the fourth token
	if (!token) { // if token is NULL, the pattern does not match
		printf("Invalid command\n"); // the established format
		return;
	}
	if (!is_number(token)) {
		printf("Invalid command\n");
		return;
	}
	int x2 = atoi(token); // the third integer

	token = strtok(NULL, delim); // the fifth and the last token
	if (!token) { // if it is NULL, it does not match the pattern
		printf("Invalid command\n");
		return;
	}
	if (!is_number(token)) {
		printf("Invalid command\n");
		return;
	}
	int y2 = atoi(token); // the fourth integer

	if (x1 > x2)
		swap(&x1, &x2);
	if (y1 > y2)
		swap(&y1, &y2);

	if (x2 > n || x1 < 0 || y2 > m || y1 < 0 || x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		return;
	}
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2); // the expected output

	area->x1 = x1; // update the selection
	area->x2 = x2;
	area->y1 = y1;
	area->y2 = y2;
}
