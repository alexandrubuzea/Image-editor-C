// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"
#include "exit_editor.h"
#include "color.h"
#include "selected.h"
#include "select.h"
#include "addfilter.h"
#include "crop.h"
#include "save.h"
#include "rotate.h"

#define NMAX 100
#define N 5

int main(void)
{
	char delim[] = "\n\t "; // prepare the delimitators for strtok
	char type[N + 1]; // a string which can have the value P1-P6
	int n, m; // the dimensions of the image
	int maxvalue = 0; // the maximal value a pixel/field can have

	// this struct will provide us the limits of the selected area
	selected_t area;
	memset(&area, 0, sizeof(selected_t)); // initialization

	color_t **colimage; // color image, if it exists
	unsigned char **image; // black & white / gray image, if it exists
	colimage = NULL; // no image is loaded at the beginning
	image = NULL; // no image is loaded at the beginning

	char command[NMAX]; // a buffer that stores the original command given

	while (fgets(command, NMAX, stdin)) {
		if (command[strlen(command) - 1] == '\n') //getting rid of '\n'
			command[strlen(command) - 1] = '\0';

		char comcopy[NMAX]; // creating a copy of the original command
		strcpy(comcopy, command);

		char *comtype = strtok(comcopy, delim); // extract the keyword

		// the logical structure of the whole source: identifying the
		// command type
		if (strcmp(comtype, "LOAD") == 0) {
			load_image(&image, &colimage, &n, &m, &maxvalue, command,
					   type, &area);
			continue;
		}

		if (strcmp(comtype, "EXIT") == 0) {
			exit_editor(&image, &colimage, m);
			return 0;
		}

		if (strcmp(comtype, "SELECT") == 0) {
			select_area(image, colimage, n, m, &area, command);
			continue;
		}

		if (!strcmp(comtype, "SEPIA") || !strcmp(comtype, "GRAYSCALE")) {
			add_filter(image, colimage, comtype, &area, maxvalue);
			continue;
		}

		if (strcmp(comtype, "SAVE") == 0) {
			save(image, colimage, command, n, m, type, maxvalue);
			continue;
		}

		if (strcmp(comtype, "ROTATE") == 0) {
			rotate(&image, &colimage, &area, &n, &m, command);
			continue;
		}

		if (strcmp(comtype, "CROP") == 0) {
			crop(&image, &colimage, &n, &m, &area);
			continue;
		}

		// if the command is not recognised, print the expected output
		printf("Invalid command\n");
	}

	exit_editor(&image, &colimage, m); // if no command is given #ponies

	return 0;
}
