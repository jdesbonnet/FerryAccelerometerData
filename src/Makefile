CC=gcc
DEPS=-lm -lfftw3
SOURCES=frequency_analysis.c
EXECUTABLE=frequency_analysis

all: frequency_analysis frequency_analysis2 waterfall_plot

frequency_analysis: frequency_analysis.c
	$(CC) -o frequency_analysis frequency_analysis.c $(DEPS)

frequency_analysis2: frequency_analysis2.c
	$(CC) -o frequency_analysis2 frequency_analysis2.c $(DEPS)

waterfall_plot: waterfall_plot.c
	$(CC) -o waterfall_plot waterfall_plot.c $(DEPS)

#$(EXECUTABLE): $(SOURCES) $(DEPS)
#	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ $(EXECUTABLE)
