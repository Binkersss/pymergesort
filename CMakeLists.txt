cmake_minimum_required(VERSION 3.4)
project(mergesort)

# Add pybind11 directly as a subdirectory
add_subdirectory(extern/pybind11)

pybind11_add_module(mergesort src/mergesort.cpp)