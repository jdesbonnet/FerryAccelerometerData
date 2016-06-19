#include <stdio.h>
#include <stdlib.h>

/**
 * Generate 2D histogram / heatmap
 */

void usage (char *cmd) {
	fprintf (stderr,"%s <bin-size>\n",cmd);
}

int main (int argc, char **argv) 
{
	char line[80];

	double timestamp;
	int i,j,v,x,y,z;

	if (argc < 2) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	int bin_size = atoi(argv[1]);

	int a[3];

	int nbin = (1<<16) / bin_size;

	int histogram[nbin][nbin];

	// Zero array
	for (j = 0; j < nbin; j++) {
		for (i = 0; i < nbin; i++) {
			histogram[j][i] = 0;
		}
	}

	while (!feof(stdin)) {
		fgets(line, sizeof line, stdin);
		sscanf(line, "%lf %d %d %d", &timestamp, &a[0], &a[1], &a[2]);
		x = a[0];
		y = a[1];
		i = (x + (1<<15)) / bin_size;
		j = (y + (1<<15)) / bin_size;
		if (i < 0 || i >= nbin || j < 0 || j >= nbin) {
			continue;
		}
		histogram[j][i]++;
	}

	for (j = 0; j < nbin; j++) {
		for (i = 0; i < nbin; i++) {
			fprintf (stdout, "%d %d %d\n", (i*bin_size)-(1<<15), (j*bin_size)-(1<<15), histogram[j][i]);
		}
	} 

}
