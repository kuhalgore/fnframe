cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(fnframe)
add_executable(
	fnframe
	frame.h
	ztime.h
	link.cpp
	)
