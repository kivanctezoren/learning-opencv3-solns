# OpenCV Exercises

This repository contains my solutions to the exercises provided in the book Learning OpenCV 3 (1st ed).

The solutions are presented in both OpenCV 3 and OpenCV 4. (Though, the differences are often small if there are any.)
Each program has its own CMake directives, and they are compiled independently.

## Requirements

* **CMake (>= 3.0)**

* **OpenCV 3** and/or **OpenCV 4**
(The programs are tested using OpenCV versions `3.2.0` and `4.5.1`.)

## Compiling the Programs


1. `cd` into the desired solution's `build` directory:

```
$ cd ocvX/chX/chXexX/build/
```

2. Run `cmake`:

```
$ cmake ../src/
```

You need to specify your OpenCV (version 3 or 4 depending on the program) installation path if it cannot be found using your `PATH` environment variable (see: [CMake find_package documentation](https://cmake.org/cmake/help/v3.0/command/find_package.html?highlight=find_package) for package searching behavior).

```
$ cmake -DOCV_PATH=/path/to/ocv/installation/ ../src/
```

3. Compile the program:

```
$ make
```
