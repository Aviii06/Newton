# Newton
A Physics engine with built in renderer implemented in openGL.
<img width="621" alt="Screenshot 2022-04-12 at 2 24 22 AM" src="https://user-images.githubusercontent.com/45993519/162830991-825b9486-5ea7-4c79-89a3-66ff444d1f28.png">
<img width="1031" alt="image" src="https://user-images.githubusercontent.com/45993519/191841279-a73a3ee9-94bb-4d39-bf76-8676b5948d13.png">


# Executable

First install [CMake](https://cmake.org/install/) and [Ninja](https://ninja-build.org/). For installation in MacOS run 
```brew install cmake ninja```

Now run 

```
git clone git@github.com:Aviii06/Newton.git
cd newton
git submodule update --init --recursive
mkdir build && cd build
cmake .. -G Ninja
ninja -j8
src/newton
```

# Debugging
After building an executable press `F5`. Or go to `Run` -> `Start Debugging`
