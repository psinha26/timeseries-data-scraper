#ifndef TREE_PRINT_HPP
#define TREE_PRINT_HPP
/* TreePrint.hpp
 *
 * Print utilities for BinarySearchTree
 *
 * Simplified version for testing purposes
 */

#include <string>
#include <sstream>
#include <algorithm>

template <typename T, typename Compare>
class BinarySearchTree<T, Compare>::Tree_grid_square {
public:
    std::string text;
    Tree_grid_square() : text("") {}
    Tree_grid_square(const std::string &s) : text(s) {}
};

template <typename T, typename Compare>
class BinarySearchTree<T, Compare>::Tree_grid {
public:
    std::vector<std::vector<Tree_grid_square>> grid;
    Tree_grid() {}
};

template <typename T, typename Compare>
int BinarySearchTree<T, Compare>::get_max_elt_width() const {
    int max_width = 1;
    for (const T &elt : *this) {
        std::ostringstream oss;
        oss << elt;
        max_width = std::max(max_width, static_cast<int>(oss.str().length()));
    }
    return max_width;
}

template <typename T, typename Compare>
std::string BinarySearchTree<T, Compare>::to_string() const {
    if (empty()) {
        return "[ empty tree ]";
    }

    std::ostringstream oss;
    oss << "[ ";
    for (const T &elt : *this) {
        oss << elt << " ";
    }
    oss << "]";
    return oss.str();
}

#endif // TREE_PRINT_HPP
