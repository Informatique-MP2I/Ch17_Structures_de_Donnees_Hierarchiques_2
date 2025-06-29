# Binary Search Tree Project

This project implements binary search trees and their use in heap structures and priority queues in C.

## Project Structure

The project is organized into several directories:

- ``src/``: Contains all source files for the binary tree implementation.
- ``include/``: Contains all header files.
- ``build/``: Directory where object files and binaries are placed after compilation.
- ``bin/``: Contains the final executable files.

## Building the Project

To build the project, you will need gcc installed on your machine. From the root of the project directory, run:

```bash
make
```

This will compile the source files and place the resulting binaries in the `bin/` directory. The provided Makefile supports several targets:

- `all`: Builds all versions of the search binary tree program, including both production and test versions and also heap and priority queue programs.
- `clean`: Removes all generated files and directories.
- `docs`: Generates Doxygen documentation.

## Running the Programs

Three different versions of the binary search tree program are produced during the build process:

- `simple_bst`: Simple binary tree implementation.
- `avl_bst`: AVL (Adelson-Velsky and Landis) binary tree implementation.
- `rb_bst`: Red-Black binary tree implementation.

Additionally, for debugging purposes and enhanced memory management, each of these versions has a corresponding test version with memory sanitization options enabled. These test versions aid in identifying memory-related issues during development. They are named as follows:

- `test_simple_bst`: Test version of the simple binary tree program.
- `test_avl_bst`: Test version of the AVL binary tree program.
- `test_rb_bst`: Test version of the Red-Black binary tree program.

All versions, both production and test, follow the same principle of usage, allowing for consistency and ease of understanding when working with the binary tree implementations.

All these programs follow the same principle of usage. To execute any of them, use the following command format:

```bash
./bin/program_name [options] [commands]
```

Replace `program_name` with the desired binary tree program you want to execute (`simple_bst`, `avl_bst`, or `rb_bst`).

A heap program using arrays and a priority queue program using search binary trees are also produced during the build process :

- `heap`: Heap implementation.
- `priority_queue`: Priority queue implementation.

## Cleaning Up

To clean up the build and binary directories, run:

```bash
make clean
```
This will remove all compiled objects and binaries.