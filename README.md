![til](/res/output.gif)

2D n-body simulatino made with OpenGL and C++

As of now only tested on Arch Linux, but should work on Windows 11.

Build Instructions Arch Linux
```
git clone git@github.com:RagnarokPDX/2DNBodySim.git
```
```
cd 2DNBodySim
```
```
cmake ..
```
```
make
```

Todo
- Implemt Barnes-Hut and Fast Multipole
- Refactor and Cleanup code
- Parallelize physics solving method
- Make build system multiplatform
- Put simulation setup into a config file or as command line arguments







