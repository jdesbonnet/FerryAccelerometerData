#include <stdio.h>
#include <stdlib.h>

/**
 * Generate histogram
 */

void usage (char *cmd) {
	fprintf (stderr,"%s <axis-index> <bin-size>\n",cmd);
	fprintf (stderr,"<axis>: 0: x-axis, 1: y-axis, 2: z-axis\n");
}

int main (int argc, char **argv) 
{
	char line[80];

	double timestamp,seg_start_timestamp;
	int i,v,x,y,z;

	if (argc < 3) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	int axis = atoi(argv[1]);
	int bin_size = atoi(argv[2]);

	int a[3];

	int nbin = (1<<16) / bin_size;
	int histogram[nbin];

	for (i = 0; i < nbin; i++) {
		histogram[i] = 0;
	}

	while (!feof(stdin)) {
		fgets(line, sizeof line, stdin);
		sscanf(line, "%lf %d %d %d", &timestamp, &a[0], &a[1], &a[2]);
		v = a[axis];
		i = (v + (1<<15)) / bin_size;
		if (i < 0 || i > nbin) {
			continue;
		}
		histogram[i]++;
	}

	for (i = 0; i < nbin; i++) {
		fprintf (stdout, "%d %d\n", (i*bin_size)-(1<<15), histogram[i]);
	} 

}
