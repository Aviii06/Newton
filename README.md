# Newton
<img width="1080" alt="Screenshot 2023-02-03 at 4 12 49 PM" src="https://user-images.githubusercontent.com/45993519/218171952-624d8dda-5c49-4fe4-942f-301deaa502f4.png">

A Physics engine with built in renderer implemented in openGL. 

It uses [Vivid](https://github.com/Aviii06/Vivid) for its rendering backend.

# Devlopment

## Dependencies
[CMake](https://cmake.org/install/) and [Ninja](https://ninja-build.org/).

## Build 

```
git clone git@github.com:Aviii06/Newton.git
cd newton
git submodule update --init --recursive
mkdir build && cd build
cmake .. -G Ninja
ninja -j8
./marchingSquare
```
