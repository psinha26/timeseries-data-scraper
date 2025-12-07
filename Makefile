# Makefile for BinarySearchTree tests

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

# Targets
all: BinarySearchTree_tests

BinarySearchTree_tests: BinarySearchTree_tests.cpp BinarySearchTree.hpp unit_test_framework.hpp TreePrint.hpp
	$(CXX) $(CXXFLAGS) BinarySearchTree_tests.cpp -o BinarySearchTree_tests

# Run tests
test: BinarySearchTree_tests
	./BinarySearchTree_tests

# Clean up
clean:
	rm -f BinarySearchTree_tests *.o

.PHONY: all test clean
