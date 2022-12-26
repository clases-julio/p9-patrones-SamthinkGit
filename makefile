# ------------------------------------ #
#             JVH SYSTEMS
#               makefile
#
# Author: Sebastian Mayorquin
# Date: 04/12/2022
#
# Use the command <<make>> for executing
# the makefile. Will automatically detect
# if using Windows or Linux a.
#
# All files will be built in the directory
# ./obj, constants modifiabless.
#
# Note: It is recommended to use any of the
# prebuilt GCC toolchains for windows in order
# to avoid errors. Find some options in:
# https://www.mingw-w64.org/downloads/
#
# More information about the systems in
# our Github:
# https://github.com/clases-julio/p6-setstl-usuarios-SamthinkGit
#
# ------------------------------------ #

SRC_DIR := ./src
LINUX_DIR := ./ext
OBJ_DIR := ./obj
DATA_DIR := ./data
OUTPUT_DIR := ./build

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS += -std=c++0x -Wl,--no-as-needed 
CC = g++

# MAIN COMPILER
$(OUTPUT_DIR)/main.exe: $(OBJ_FILES)
	g++ -g $(LDFLAGS) -o $@ $^ 

# SRC COMPILER
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -g $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

ifeq ($(OS), Windows_NT)

else
$(OBJ_DIR)/%.o: $(LINUX_DIR)/%.cpp
	g++ -g $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

endif

clean:
	rm -rf ./obj/*.o
