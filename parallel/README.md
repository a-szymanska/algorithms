# Codes for GPU parallelization
This folder contains functions and CUDA kernels for parallel algorithms, most of which get as arguments the data already on the GPU.
The codes are compiled with the ```nvcc``` compiler with flags ```-std=c++11 -arch sm_61 -O3 --expt-extended-lambda```. They have been tested on a GTX 1060 card.

## Requirements
Some of the codes require the latest version of thrust and moderngpu libraries.