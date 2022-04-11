# Newton
A Physics engine with built in renderer implemented in openGL.
<img width="621" alt="Screenshot 2022-04-12 at 2 24 22 AM" src="https://user-images.githubusercontent.com/45993519/162830991-825b9486-5ea7-4c79-89a3-66ff444d1f28.png">
<img width="602" alt="Screenshot 2022-04-12 at 2 49 56 AM" src="https://user-images.githubusercontent.com/45993519/162835380-86360722-e2fe-4d60-b885-ce26d3f3ce2d.png">


# Executable

First install [CMake](https://cmake.org/install/) and [Ninja](https://ninja-build.org/). For installation in MacOS run 
```brew install cmake ninja```

Now run 

```
git clone git@github.com:Aviii06/Newton.git
cd newton
mkdir build && cd build
cmake .. -G Ninja
ninja
./newton
```

# Debugging
After building an executable press `F5`. Or go to `Run` -> `Start Debugging`
