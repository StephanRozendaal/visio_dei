# Dit is het begin van de Cmake buildfiles voor het minor computer vision project
# Gemaakt met Cmake versie 2.8
cmake_minimum_required(VERSION 2.8)
#het project heet minor_computer_vision
project(minor_computer_vision)
#source files zitten in directory src/
include_directories("include")
add_subdirectory(src)
