# Newton
A Physics engine with built in renderer implemented in openGL.

The renderer creates a user frendly interface for rendering on OpenGL.
<img width="1512" alt="Screenshot 2023-01-14 at 9 29 19 PM" src="https://user-images.githubusercontent.com/45993519/212481445-95819cdf-72d6-4744-b5eb-12a8accfff09.png">

<img width="1031" alt="image" src="https://user-images.githubusercontent.com/45993519/191841279-a73a3ee9-94bb-4d39-bf76-8676b5948d13.png">


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
