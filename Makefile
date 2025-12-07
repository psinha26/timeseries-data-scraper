# Makefile for BinarySearchTree and Map tests

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

# Targets
all: BinarySearchTree_tests Map_tests

BinarySearchTree_tests: BinarySearchTree_tests.cpp BinarySearchTree.hpp unit_test_framework.hpp TreePrint.hpp
	$(CXX) $(CXXFLAGS) BinarySearchTree_tests.cpp -o BinarySearchTree_tests

Map_tests: Map_tests.cpp Map.hpp BinarySearchTree.hpp unit_test_framework.hpp TreePrint.hpp
	$(CXX) $(CXXFLAGS) Map_tests.cpp -o Map_tests

# Run tests
test: BinarySearchTree_tests Map_tests
	./BinarySearchTree_tests
	@echo ""
	@echo "================================"
	@echo "Running Map Tests"
	@echo "================================"
	./Map_tests

# Run only BST tests
test-bst: BinarySearchTree_tests
	./BinarySearchTree_tests

# Run only Map tests
test-map: Map_tests
	./Map_tests

# Clean up
clean:
	rm -f BinarySearchTree_tests Map_tests *.o

.PHONY: all test test-bst test-map clean
