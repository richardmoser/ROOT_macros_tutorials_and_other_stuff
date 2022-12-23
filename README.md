#  No Guarantees
This is a collection of macros and jupyter notebooks for ROOT. Many probably don't work without specific RadioScatter files/data, but they are preserved here in case of future need for the functions and code snippets.

# Known Issues/Common Errors
    - setRxSampleRate() values may lead to errors in code depending on binsize and sample rate of frequency data fom spec

    - adjusting TX frequency requires changing the scaling factor in the code for macros like sumpowfreq.C and scattersumpowfreq.C. Dummy check is to look at 
      where the data ends - i.e. where spec goes from blue to white. Any data on a plot derived from this that appears above that frequency means that you have 
      scaling issues. If data cuts off before this point, then you probably have scaling issues there as well. Theoretically, they should be the same.
        > because of the way binning works, the last data point will probably be just shy of the apparent cutoff point
        > this is because the last bin is centered on the last data point, so the last data point is actually the center of the last bin, which is just shy 
          of the cutoff point. Or something like that.
        > a few (but probably not all) places to change the scaling factor are:
            1. the loop above the loop calling power_generator() which sets the single event (non summed) plot
            2. the power_generator() function which sets the summed plots
            3. the max_generator() function which finds the maximum bin-points for the summed plots