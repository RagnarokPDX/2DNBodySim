![til](/res/output.gif)

2D n-body simulation made with OpenGL and C++

As of now only tested on Arch Linux, but should work on Windows 11.

## Build Instructions

This project uses CMake as a build system.

Build Instructions Arch Linux
```
git clone git@github.com:RagnarokPDX/2DNBodySim.git
```
```
cd 2DNBodySim/
```
```
mkdir build && cd build
```
```
cmake ..
```
```
make
```
To run, run the 2DNBodySim executable
```
./2DNBodySim
```

## Controls

MouseWheel - Zoom in and out 

W, A, S, D - Move Around

Esc - exit

## Todo

- Implemt Barnes-Hut and Fast Multipole
- Refactor and Cleanup code
- Parallelize physics solving method
- Make build system multiplatform
- Put simulation setup into a config file or as command line arguments













