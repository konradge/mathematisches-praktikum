# Build and run the project with cmake

## Initialize build folder

    cmake -S . -B build

## Compile/Build

    cmake --build build

## Compile/Build for debugging

    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    make

## Compile/Build without debugging (with delete beforehand)

    cd ..
    rm -rf build
    mkdir build
    cd build
    cmake .. 
    make

## Run solution

    cd build/bin"
    ./loesung

## Run tests

    cd build/tests
    ./example_tests
