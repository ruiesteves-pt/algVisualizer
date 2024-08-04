# C++ Sorting Algorithm Visualizer
This program is intended to provide a visualization of the most import sorting algorithms during their process. It displays the array in bar or heap format while also displaying it in traditional format below the graphical one.


It serves as a pratice tool to revisit fundamental concepts in the C++ language: its data structures and algorithms. It also helps to pratice our array manipulation and function handling - although the provided functions are not completely memory and efficiency optimized, they aim at dealing with data in a C++ safe way: attempting at dealing with references and pointers in a safe way and using dynamically alocated memory as much as possible.

Additionally, the program uses a CMake built system. Althought it is definitely an overkill for a project of this complexity, it also serves as a pratice exercise on how to correctly setup a CMake build system and file.

The graphical side is programmed using the SFML library: https://www.sfml-dev.org/, which also proves itself valuable for a pratice exercise in GUI C++ development.

## Algorithms
Five sorting algorithms are available: bubble sort, heap sort, quick sort, merge sort, and selection sort.

## Installation
Clone or download this repo, move to the directory.

This program was built in a Linux environment (using WSL in a Windows 11 machine). However, if you prefer to run it in Windows outside of WSL, just install SFML from their website instead of using the command below.
```
sudo apt-get install libsfml-dev
```
Make sure you have CMake installed. After this, if you are using VS Code simply access your search bar and search CMake : Build, run that command. If you prefer to do it by terminal, run the following:
```
<YOUR_CMAKE_DIR> --build <PROJECT_DIR/build> --config Debug --target all
```
Your project is now built and your executable is ready.

## Running
There is a shell script present in the repo main folder called run.sh. Simply run this command and the program will start.
```
./run.sh
```

You can control it with your number keys 1 2 3 4 5 to select an algorithm and by pressing Enter you will start the sorting process. Enjoy!

![image](https://github.com/user-attachments/assets/15555820-0c31-401f-861b-0d99f00819ff)
