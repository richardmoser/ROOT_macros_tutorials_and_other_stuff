"""
Author: Richard Moser
Date: 28Aug23
Description: This script plots the voltage vs time for CReSIS radar data from a .mat file.
"""

# Import libraries
import numpy as np
import matplotlib.pyplot as plt
import scipy.io as sio
import os
import sys
import pandas as pd

# Set the path to the data
data_path = '/home/rj/cresis_stuff/20180501_02'

# Set the path to the .mat file
mat_file = 'Data_20180501_02_001.mat'

# Set the path to the output .png file
png_file = 'Data_20180501_02_001.png'

# Load the .mat file
mat_contents = sio.loadmat(os.path.join(data_path, mat_file))

# show the contents of the .mat file
# print(mat_contents)

# the .mat file has the following contents:
#{'__header__': b'MATLAB 5.0 MAT-file, Platform: GLNXA64, Created on: Wed Dec  9 08:42:46 2020', '__version__': '1.0', '__globals__': [], 'GPS_time': array([[1.52519827e+09, 1.52519827e+09, 1.52519827e+09, ...,
#         1.52519831e+09, 1.52519831e+09, 1.52519831e+09]]), 'Latitude': array([[68.67363694, 68.67361187, 68.67357516, ..., 68.63077677,
#         68.63073864, 68.6307005 ]]), 'Longitude': array([[-50.42039117, -50.42042074, -50.42046401, ..., -50.45469133,
#         -50.45472378, -50.45475617]]), 'Elevation': array([[1169.27645642, 1169.13735045, 1168.93333956, ...,  967.41234923,
#          967.2318083 ,  967.05382853]]), 'layerData': array([[array([[(array([[array([[(array([[nan, nan, nan, ..., nan, nan, nan]]),)]],
#                               dtype=[('data', 'O')])                              ,
#                         array([[(array([[5.39287073e-06, 5.39287073e-06, 5.39236792e-06, ...,
#                                         4.27711781e-06, 4.27289300e-06, 4.27525587e-06]]),)  ]],
#                               dtype=[('data', 'O')])                                            ]],
#                       dtype=object), array([[1, 1, 1, ..., 1, 1, 1]], dtype=uint8))                ]],
#               dtype=[('value', 'O'), ('quality', 'O')])                                               ]],
#       dtype=object)}

# Extract the data from the .mat file and add it to a pandas dataframe
contents = mat_contents['layerData']
contents_cleaned = [contents[0][0][0][0][0][0][0], contents[0][0][0][0][0][0][1]]
print(contents_cleaned[0])
print(contents_cleaned[0][0])
print(contents_cleaned[0][0][0])
print(contents_cleaned[0][0][0][0])
print(contents_cleaned[0][0][0][0][0])
print(contents_cleaned[0][0][0][0][0][0])

# Extract the time data from the .mat file
time = mat_contents['GPS_time']
time_cleaned = time[0]

# plot the data
# plt.plot(time_cleaned, contents_cleaned[0])
