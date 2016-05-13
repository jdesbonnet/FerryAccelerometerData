#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>

/**
 * Frequency analysis of accelerometer data.
 */

int main (int argc, char **argv) 
{
	char line[80];

	fftw_complex *out;
	fftw_plan p;

	int N = 2048;
	double timestamp;
	int i,x,y,z;

	N = atoi(argv[1]);

	double in[N];

	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);


	for (i = 0; i < N; i++) {
		fgets(line, sizeof line, stdin);
		sscanf(line, "%lf %d %d %d", &timestamp, &x, &y, &z);
		in[i] = (double)z;
		//printf ("in[%d]=%d\n",i,z);
	}

	int flags = FFTW_ESTIMATE;
	p = fftw_plan_dft_r2c_1d(N, in, out, flags);

	fftw_execute(p);

	double oi,oj,mag;

	for (i = 0; i < N/2; i++) {
		oi = out[i][0];
		oj = out[i][1];
		mag = sqrt(oi*oi+oj*oj);
		fprintf (stdout, "%d %f %f %f\n", i, mag, oi, oj);

	}

	fftw_destroy_plan(p);
	fftw_free(out);
}
