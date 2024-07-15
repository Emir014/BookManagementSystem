cmake_minimum_required(VERSION 3.23)
project(Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Lib)

add_executable(Project
        Lib/json.hpp
        book.h
        library.cpp
        library.h
        user.h)
