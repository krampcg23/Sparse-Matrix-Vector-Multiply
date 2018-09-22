# CSCI 580 High Performance Computing, HW 1
## Author: Clayton Kramp
## List of all file
### main.cpp
Contains the main SPMV multiply method.
### BoostAndImp.cpp
Contains the boost SPMV and my implementation of SPMV.  Boost works for small values, so make sure input is small enough
### script.cpp
Contains a quick script to make an array with random numbers.  Sparse, so make sure N < elements.
### graphs.m
Matlab file that I used to generate graphs

## Compilation / Execution
Type `make` to compile all the executables.  Also just type `make main_exe` for just main.

To execute, type `make run` to traverse through the 3 inputs we use.  The files are not included in here though, as they are large files.  If you generate one with script, then simply type `./main_exe matrix.txt`
