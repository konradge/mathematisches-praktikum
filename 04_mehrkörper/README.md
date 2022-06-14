# Build and run the project with cmake

## Initialize build folder

    cmake -S . -B build

## Compile/Build

    cmake --build build

## Compile/Build for debugging

    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    make

## Run solution

    cd build/bin"
    ./loesung

## Run tests

    cd build/tests
    ./example_tests
