CC=gcc
DEPS=-lm -lfftw3
SOURCES=frequency_analysis.c
EXECUTABLE=frequency_analysis

$(EXECUTABLE): $(SOURCES) $(DEPS)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ $(EXECUTABLE)
