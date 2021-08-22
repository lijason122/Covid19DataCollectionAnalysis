cmake_minimum_required(VERSION 3.19)
project(Covid19DataCollectionAnalysis C)

set(CMAKE_C_STANDARD 99)

add_executable(Covid19DataCollectionAnalysis covid19InfoLL.c household.c household.h)