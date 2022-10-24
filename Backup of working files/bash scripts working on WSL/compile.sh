#!/bin/bash
echo -e "enter filename: "
read infile

echo -e "Enter output filename: "
read outfile

cd /home/rj/RadioScatter/example
g++ -std=c++0x $infile -o $outfile `root-config --cflags --glibs --libs` -lRadioScatter
#g++ -std=c++0x $infile -o $outfile `root-config --cflags --glibs --libs` -lRadioScatter 
#g++ -std=c++0x scatterFromCascade.cc -o scatterFromCascade `root-config --cflags --glibs --libs` -lRadioScatter