# Newton
This is trying to be a physics engine.

# Debugging

## Vscode
To debug it in VS Code press `cmd`+`shift`+`b`.

and now run `./newton`

## CMake
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

