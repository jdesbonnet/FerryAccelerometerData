#!/bin/bash
DATA_FILE=../data/boat_accl-20160512-lapalma.dat.gz
gunzip -c ${DATA_FILE} | ../src/frequency_analysis 18 0 > fft_x.dat
gunzip -c ${DATA_FILE} | ../src/frequency_analysis 18 1 > fft_y.dat
gunzip -c ${DATA_FILE} | ../src/frequency_analysis 18 2 > fft_z.dat

 
gnuplot <<- EOF
  set terminal pngcairo size 1280,720 background rgb 'black'
  set output "fft.png"

  set border lc rgb 'white'
  set key tc rgb 'white'
  set grid lc rgb 'white'
  set style line 1 linecolor rgb "green"
  set style line 2 linecolor rgb "blue"

  set title "Frequency analysis of accelerometer sensor on ferry (z-axis)\n(LIS3DSH, 100sps, +/- 2g FSD, 200Hz anti-alias filter)" textcolor rgb 'white'
  set xlabel "Frequency (Hz)" textcolor rgb 'white'
  set ylabel "Amplitude" textcolor rgb 'white'

  set xrange [.05:1]
  #set yrange [0:1e3]

  plot 'fft_z.dat' using 2:3 with impulses title 'Normalized FFT magnitude Z-axis' ,\
  'fft_x.dat' using 2:3 with impulses title 'Normalized FFT magnitude X-axis' ,\
  'fft_y.dat' using 2:3 with impulses title 'Normalized FFT magnitude Y-axis'


EOF
