![til](/res/output.gif)

2D n-body simulatino made with OpenGL and C++

As of now only tested on Arch Linux

Build Instructions
```
sudo pacman -S glm glfw
mkdir build
cd build
cmake ..
make
./2dNBodySim
```
Todo
- Implemt Barnes-Hut and Fast Multipole
- Refactor and Cleanup code
- Parallelize physics solving method
- Make build system multiplatform



