# ANTLR-Demo
Dummy programming language to test out ANTLR and its build system. 

## Usage
CMake 3.27+ is required.
```shell
git clone https://github.com/appleplectic/antlr-demo
cd antlr-demo
mkdir build
cd build
cmake ..
cmake --build .
```
Run the resulting `ANTLRDemoInterpreter` binary with a file as a command line argument.