cmake_minimum_required(VERSION 3.14)

project(TimeConvert LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ask for all warnings and strict compliance with the standard
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic")

add_library(TimeConvert STATIC
  src/timeconvert.h
  src/time_base.cpp
  src/time_base.h
  src/time_cuc.cpp
  src/time_cuc.h
  src/time_gregorian.cpp
  src/time_gregorian.h
  src/time_unix_timestamp.cpp
  src/time_unix_timestamp.h
)

target_compile_definitions(TimeConvert PRIVATE TIMECONVERT_LIBRARY)
target_include_directories(TimeConvert PUBLIC src)
