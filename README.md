# Uptown

## Objective

To create a simple key value storage system in C.

## Techniques Used

1. [Hashing](https://en.wikipedia.org/wiki/Hash_table)
2. [Quadratic probing](https://en.wikipedia.org/wiki/Quadratic_probing)
3. [Linear probing](https://en.wikipedia.org/wiki/Linear_probing)
4. [LRU Cache](https://en.wikipedia.org/wiki/Cache_algorithms)

## Todo

1. Data encryption.
2. Implement a server.
3. Create bindings for Python.

## Running the project

The project has been tested on Ubuntu Trusty Tahr (and Fedora 22) using GNU C Compiler.

A driver program, `driver.c`, has been included for testing the functionality
of the application.

Execute the following commands commands in a shell to build and test the project.

1. `$ mkdir lib`
2. `$ make driver.c`
3. `$ lib/install_db ./test.db 100`
4. `$ lib/uptown ./test.db`
