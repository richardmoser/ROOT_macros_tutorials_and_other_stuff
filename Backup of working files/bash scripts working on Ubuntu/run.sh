#!/bin/bash
echo -e "Drag file to terminal: "
read tempinfile
#echo "Temp infile: " $tempinfile
eval infile=$tempinfile
#echo "Cleaned infile: " $infile

echo -e "Plasma lifetime (ns): "
read plasma
echo -e "Frequency (GHz): "
read frequency
echo -e "TX power (W): "
read power
cd /home/rj/RadioScatter/example
#./$infile $plasma $frequency $power
$infile $plasma $frequency $power
