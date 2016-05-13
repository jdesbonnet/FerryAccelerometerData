#!/bin/bash
DATA_FILE=../data/boat_accl-20160512-lapalma.dat.gz
gunzip -c ${DATA_FILE} | ../src/frequency_analysis 18 0 > fft_x.dat
gunzip -c ${DATA_FILE} | ../src/frequency_analysis 18 1 > fft_y.dat
gunzip -c ${DATA_FILE} | ../src/frequency_analysis 18 2 > fft_z.dat

 
gnuplot <<- EOF
  #set terminal pngcairo size 1280,720 background rgb 'black'
  set terminal pngcairo size 1024,600 background rgb 'black'

  set output "fft.png"

  set border lc rgb 'white'
  set key tc rgb 'white'
  set grid lc rgb 'white'
  set style line 1 linecolor rgb "green"
  set style line 2 linecolor rgb "blue"

  set title "Frequency analysis of accelerometer sensor on Fred Olsen ferry arriving LaPalma, 22:00 12 May 2016\nLIS3DSH, 100sps, ±2g FSD, 200Hz anti-alias filter. 131072 data points covering approx 22 minutes." textcolor rgb 'white'
  set xlabel "Frequency (Hz)" textcolor rgb 'white'
  set ylabel "DFT magnitude (g units)" textcolor rgb 'white'

  set label "Joe Desbonnet, 13 Feb 2016" at graph -0.11,-0.1 font ",8" tc rgb "white"

  set xrange [.05:1]
  #set yrange [0:1e3]

  plot \
  'fft_z.dat' using 2:3 with impulses title 'Z-axis (vertical)' ,\
  'fft_x.dat' using 2:3 with impulses title 'X-axis (left-right)' ,\
  'fft_y.dat' using 2:3 with impulses title 'Y-axis (bow-stern)'


EOF
