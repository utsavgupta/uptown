# Uptown

## Objective

To create a simple hash table storage system in C.

## Techniques Used

1. [Quadratic probing](https://en.wikipedia.org/wiki/Quadratic_probing)
2. [Linear probing](https://en.wikipedia.org/wiki/Linear_probing)

## Todo

1. Develop a module for handling encryption of data.
2. Implement a LRU cache.
3. Make the operations thread safe and implement a client-server model.
4. Create bindings for Python.

## Running the project

The project is still in its early stages. Only the basic I/O operations and
hash table handling functions have been implemented.

The project has been compiled and tested on Ubuntu using GNU C Compiler.

A driver program, `driver.c`, has been created for testing the functionality
of the project.

Execute the following commands commands at the command prompt to build and test
the project.

1. `$ mkdir lib`
2. `$ make driver.c`
3. `$ lib/install_db ./test.db 100`
4. `$ lib/uptown ./test.db`
