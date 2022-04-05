# Mathematisches Praktikum

## Compile and run
To compile, open a shell and type:
```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic a.cpp ... z.cpp -o out
```
where `a.cpp`, ..., `z.cpp` are the cpp-files, that should be compiled (Or object-files, that should be linked). Now run the programm with the following command:
```sh
./out
```

## Debugging with Visual Studio Code in WSL
First start WSL, cd into the root-folder of the project (named `mathematisches-praktikum`) and type 
```sh
code .
```
### Build
The build task, that is configured in the .vscode-Folder will build all .cpp-Files in the folder, it has been started in
1. If there isn't any folder named `out` in the root of the project, create it
2. Press CTRL+SHIFT+B inside one file in the folder you want to build all .cpp-Files
3. In the out-folder, that was created in step 1., there is the compiled binary-file

### Build and debug
In the file containing the main-function, press `F5`. The debugger will then start automatically.