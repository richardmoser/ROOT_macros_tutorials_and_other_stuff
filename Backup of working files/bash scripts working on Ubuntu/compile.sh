#!/bin/bash
echo -e "Drag file to terminal: "
read tempinfile
#echo "Temp infile: " $tempinfile
eval infile=$tempinfile
#echo "Cleaned infile: " $infile

echo -e "Enter output filename: "
read outfile
cd /home/rj/RadioScatter/example
g++ -std=c++0x $infile -o $outfile `root-config --cflags --glibs --libs` -lRadioScatter 
#g++ -std=c++0x scatterFromCascade.cc -o scatterFromCascade `root-config --cflags --glibs --libs` -lRadioScatter 
