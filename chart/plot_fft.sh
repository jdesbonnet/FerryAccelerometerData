#!/bin/bash
DATA_FILE=../data/boat_accl-20160512-lapalma.dat.gz
gunzip -c ${DATA_FILE} | ../src/frequency_analysis 18 > fft.dat
 
gnuplot <<- EOF
  set terminal pngcairo size 1280,720 background rgb 'black'
  set output "fft.png"

  set border lc rgb 'white'
  set key tc rgb 'white'
  set grid lc rgb 'white'
  set style line 1 linecolor rgb "green"
  set style line 2 linecolor rgb "blue"

  set title "Accelerometer on ferry"
  set xlabel "Frequency (Hz)"
  set ylabel "Amplitude"

  set xrange [.05:1]
  #set yrange [0:1e3]

  plot 'fft.dat' using 2:3 with impulses

