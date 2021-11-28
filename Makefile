CXX = g++
CFLAGS = -Wall -Ofast -march=native
LDFLAGS = -lcnpy -lz -L /usr/local/lib

SRC = src/main.cpp
 
OUTPUT = build/main

default: 
	@echo "\nCompiling...\n"
	@make all 
	@echo "\nRunning...\n"
	@(LD_LIBRARY_PATH=/usr/local/lib && cd build/ && exec ./main)
 
all: 
	@$(CXX) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUTPUT)
 
.PHONY: clean
 
clean: 
	@echo "\nCleaning...\n"
	@rm -rf $(OUTPUT) build/*
