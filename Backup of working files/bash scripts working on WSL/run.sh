#!/bin/bash
echo -e "enter filename: "
read infile

echo -e "Plasma lifetime (ns): "
read plasma
echo -e "Frequency (GHz): "
read frequency
echo -e "TX power (W): "
read power
cd /home/rj/RadioScatter/example
./$infile $plasma $frequency $power
#$infile $plasma $frequency $power
