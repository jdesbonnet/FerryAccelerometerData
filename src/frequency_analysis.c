#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>

/**
 * Frequency analysis of accelerometer data.
 */

void usage (char *cmd) {
	fprintf (stderr,"%s <N> <axis-index>\n",cmd);
	fprintf (stderr,"<N>: number of samples expressed as power of 2, eg 8 means 256 samples\n");
	fprintf (stderr,"<axis>: 0: x-axis, 1: y-axis, 2: z-axis\n");
}

int main (int argc, char **argv) 
{
	char line[80];

	fftw_complex *out;
	fftw_plan p;

	// Samples per second
	const int SPS = 100;

	double timestamp;
	int i,v,x,y,z;

	if (argc < 3) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	int N = atoi(argv[1]);
	int axis = atoi(argv[2]);

	N = 1 << N;

	double in[N];

	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

	int a[3];

	for (i = 0; i < N; i++) {
		fgets(line, sizeof line, stdin);
		sscanf(line, "%lf %d %d %d", &timestamp, &a[0], &a[1], &a[2]);
		//a[2] -= 17000;
		v = a[axis];
		in[i] = (double)a[axis]/(1<<14);
	}

	int flags = FFTW_ESTIMATE;
	p = fftw_plan_dft_r2c_1d(N, in, out, flags);

	fftw_execute(p);

	// Output FFT
	double oi,oj,mag;
	for (i = 0; i < N/2; i++) {
		oi = out[i][0];
		oj = out[i][1];
		mag = sqrt(oi*oi+oj*oj)/(double)N;
                //mag = sqrt(oi*oi+oj*oj);

		fprintf (stdout, "%d %f %f %f %f\n", i, ((double)(i*SPS)/N), mag, oi, oj);
	}

	fftw_destroy_plan(p);
	fftw_free(out);
}
