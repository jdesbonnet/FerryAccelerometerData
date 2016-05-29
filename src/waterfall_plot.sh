#!/bin/bash

#gunzip -c ../data/boat_accl-20160512-lapalma.dat.gz | ./waterfall_plot 8 2 > waterfall_plot.dat

gnuplot <<- EOF

  set terminal pngcairo size 1280,720 background rgb 'black'
  set output "waterfall_plot.png"

  set border lc rgb 'white'
  set key tc rgb 'white'
  set grid lc rgb 'white'
  set style line 1 linecolor rgb "green"
  set style line 2 linecolor rgb "blue"

  set title "Accelerometer frequency waterfall plot.\n" textcolor rgb "white"

  set label "Joe Desbonnet, 12 May 2016" at graph -0.04,-0.08 font "8" tc rgb "white"
  set label "Magnitude" at graph 1.03,1.05 font "8" tc rgb "white"

  set xlabel "Time" textcolor rgb "white"
  set ylabel "Frequency" textcolor rgb "white"
  #set y2label "test" textcolor rgb "white"

  set xrange [800:1000]
  #set yrange [0:90]
  set cbrange[0:0.02]

  #set xtics 45
  #set ytics 15

  set palette model RGB defined ( 0 'black', 10 'blue', 50 'red', 80 'yellow', 99 'green' )
  plot 'waterfall_plot.dat' using 1:2:3 with image

EOF


