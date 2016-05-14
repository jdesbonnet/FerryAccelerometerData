#!/bin/bash
ACCL_DATA_FILE=../data/boat_accl-20160512-lapalma.dat.gz
GNSS_TRACK_FILE=../data/boat_gnss_track.csv.gz
gunzip -c ${ACCL_DATA_FILE} | ../src/frequency_analysis2 12 2 > accl_segments.dat
gunzip -c ${GNSS_TRACK_FILE} | java -cp ../src ReadMyTracksCSV  > track.dat
java -cp ../src JoinAcclToTrack track.dat accl_segments.dat > stitched.dat
 
gnuplot <<- EOF
  #set terminal pngcairo size 1280,720 background rgb 'black'
  set terminal pngcairo size 1024,600 background rgb 'black'

  set output "map.png"

  set border lc rgb 'white'
  set key tc rgb 'white'
  set grid lc rgb 'white'
  set style line 1 linecolor rgb "green"
  set style line 2 linecolor rgb "blue"

  #set title "Frequency analysis of accelerometer sensor on Fred Olsen ferry arriving LaPalma, 22:00 12 May 2016\nLIS3DSH, 100sps, ±2g FSD, 200Hz anti-alias filter. 131072 data points covering approx 22 minutes." textcolor rgb 'white'
  set xlabel "Longitude degrees" textcolor rgb 'white'
  set ylabel "Latitude degrees" textcolor rgb 'white'

  set label "Joe Desbonnet, 13 May 2016" at graph -0.11,-0.1 font ",8" tc rgb "white"

  plot \
'stitched.dat' using 5:4:((\$3)*0.1) with circles title 'Magnitude of peak frequency'


EOF
