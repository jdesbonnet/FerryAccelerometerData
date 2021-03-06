#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>

/**
 * Frequency analysis of accelerometer data. This spits the timeseries into 
 * segments, does FFT on each segment and reports the start time, preak f
 * frequency under 1Hz and the magnitude of that peak.
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

	double timestamp,seg_start_timestamp;
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

        p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);


	int a[3];

	while (1) {
		seg_start_timestamp=0;
		for (i = 0; i < N; i++) {
			fgets(line, sizeof line, stdin);
			sscanf(line, "%lf %d %d %d", &timestamp, &a[0], &a[1], &a[2]);
			v = a[axis];
			in[i] = (double)a[axis]/(1<<14);
			if (seg_start_timestamp==0) {
				seg_start_timestamp = timestamp;
			}	
		}

		if (feof(stdin)) {
			break;
		}


		fftw_execute(p);

		// Find magnitude and frequency of peak 
		double oi,oj,mag;
		double max_mag = 0;
		int max_mag_index = 0;
		double frequency;

		// Highest frequency of interest
		double max_frequency = 1.0; 

		for (i = 2; i < N/2; i++) {
			frequency = (i*SPS)/N; 
			if (frequency > max_frequency) {
				break;
			}
			oi = out[i][0];
			oj = out[i][1];
			mag = sqrt(oi*oi+oj*oj)/(double)N;
			if (mag > max_mag) {
				max_mag = mag;
				max_mag_index = i;
			}
		}
        	fprintf (stdout, "%f %f %f\n", 
			seg_start_timestamp,
			((double)(max_mag_index*SPS)/N), 
			max_mag);

	}

	fftw_destroy_plan(p);
	fftw_free(out);
}
