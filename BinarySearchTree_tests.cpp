#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

// ========================================
// BASIC OPERATIONS TESTS
// ========================================

TEST(test_empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0u);
    ASSERT_EQUAL(tree.height(), 0u);
}

TEST(test_single_element) {
    BinarySearchTree<int> tree;
    tree.insert(5);

    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1u);
    ASSERT_EQUAL(tree.height(), 1u);
}

TEST(test_size_multiple_elements) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    ASSERT_EQUAL(tree.size(), 5u);
}

TEST(test_height_balanced) {
    BinarySearchTree<int> tree;
    tree.insert(5);    // Height 1
    tree.insert(3);    // Height 2
    tree.insert(7);    // Height 2
    tree.insert(1);    // Height 3
    tree.insert(9);    // Height 3

    ASSERT_EQUAL(tree.height(), 3u);
}

TEST(test_height_degenerate) {
    BinarySearchTree<int> tree;
    tree.insert(1);    // Height 1
    tree.insert(2);    // Height 2
    tree.insert(3);    // Height 3
    tree.insert(4);    // Height 4

    ASSERT_EQUAL(tree.height(), 4u);
}

// ========================================
// INSERT AND FIND TESTS
// ========================================

TEST(test_insert_and_find_single) {
    BinarySearchTree<int> tree;
    tree.insert(5);

    auto it = tree.find(5);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 5);
}

TEST(test_find_nonexistent) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    auto it = tree.find(10);
    ASSERT_TRUE(it == tree.end());
}

TEST(test_insert_multiple_and_find) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    ASSERT_TRUE(tree.find(10) != tree.end());
    ASSERT_TRUE(tree.find(5) != tree.end());
    ASSERT_TRUE(tree.find(15) != tree.end());
    ASSERT_TRUE(tree.find(3) != tree.end());
    ASSERT_TRUE(tree.find(7) != tree.end());
    ASSERT_TRUE(tree.find(12) != tree.end());
    ASSERT_TRUE(tree.find(20) != tree.end());
    ASSERT_TRUE(tree.find(100) == tree.end());
}

TEST(test_insert_maintains_structure) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);

    // Tree should look like:
    //       5
    //      / \
    //     3   7
    //    / \ / \
    //   1  4 6  9

    ASSERT_TRUE(tree.check_sorting_invariant());
}

// ========================================
// MIN AND MAX TESTS
// ========================================

TEST(test_min_element_single) {
    BinarySearchTree<int> tree;
    tree.insert(5);

    auto it = tree.min_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 5);
}

TEST(test_max_element_single) {
    BinarySearchTree<int> tree;
    tree.insert(5);

    auto it = tree.max_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 5);
}

TEST(test_min_element_multiple) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    auto it = tree.min_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 3);
}

TEST(test_max_element_multiple) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);

    auto it = tree.max_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 20);
}

TEST(test_min_max_empty_tree) {
    BinarySearchTree<int> tree;

    auto min_it = tree.min_element();
    auto max_it = tree.max_element();

    ASSERT_TRUE(min_it == tree.end());
    ASSERT_TRUE(max_it == tree.end());
}

// ========================================
// MIN_GREATER_THAN TESTS
// ========================================

TEST(test_min_greater_than_exists) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    auto it = tree.min_greater_than(5);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 7);
}

TEST(test_min_greater_than_not_in_tree) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(9);

    auto it = tree.min_greater_than(6);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 7);
}

TEST(test_min_greater_than_no_successor) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    auto it = tree.min_greater_than(10);
    ASSERT_TRUE(it == tree.end());
}

TEST(test_min_greater_than_max_element) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(9);

    auto it = tree.min_greater_than(9);
    ASSERT_TRUE(it == tree.end());
}

TEST(test_min_greater_than_smallest) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);

    auto it = tree.min_greater_than(1);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 3);
}

// ========================================
// ITERATOR TESTS
// ========================================

TEST(test_iterator_empty_tree) {
    BinarySearchTree<int> tree;

    auto it = tree.begin();
    ASSERT_TRUE(it == tree.end());
}

TEST(test_iterator_single_element) {
    BinarySearchTree<int> tree;
    tree.insert(5);

    auto it = tree.begin();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 5);

    ++it;
    ASSERT_TRUE(it == tree.end());
}

TEST(test_iterator_in_order) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    std::vector<int> elements;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        elements.push_back(*it);
    }

    ASSERT_EQUAL(elements.size(), 5u);
    ASSERT_EQUAL(elements[0], 1);
    ASSERT_EQUAL(elements[1], 3);
    ASSERT_EQUAL(elements[2], 5);
    ASSERT_EQUAL(elements[3], 7);
    ASSERT_EQUAL(elements[4], 9);
}

TEST(test_iterator_range_based_loop) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::vector<int> elements;
    for (int val : tree) {
        elements.push_back(val);
    }

    ASSERT_EQUAL(elements.size(), 5u);
    ASSERT_EQUAL(elements[0], 3);
    ASSERT_EQUAL(elements[1], 5);
    ASSERT_EQUAL(elements[2], 7);
    ASSERT_EQUAL(elements[3], 10);
    ASSERT_EQUAL(elements[4], 15);
}

TEST(test_iterator_postfix_increment) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    auto it = tree.begin();
    auto old_it = it++;

    ASSERT_EQUAL(*old_it, 3);
    ASSERT_EQUAL(*it, 5);
}

TEST(test_iterator_equality) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);

    auto it1 = tree.begin();
    auto it2 = tree.begin();

    ASSERT_TRUE(it1 == it2);
    ASSERT_FALSE(it1 != it2);

    ++it1;
    ASSERT_FALSE(it1 == it2);
    ASSERT_TRUE(it1 != it2);
}

// ========================================
// TRAVERSAL TESTS
// ========================================

TEST(test_traverse_inorder) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    std::ostringstream oss;
    tree.traverse_inorder(oss);

    ASSERT_EQUAL(oss.str(), "1 3 5 7 9 ");
}

TEST(test_traverse_inorder_empty) {
    BinarySearchTree<int> tree;

    std::ostringstream oss;
    tree.traverse_inorder(oss);

    ASSERT_EQUAL(oss.str(), "");
}

TEST(test_traverse_preorder) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    std::ostringstream oss;
    tree.traverse_preorder(oss);

    ASSERT_EQUAL(oss.str(), "5 3 1 7 9 ");
}

TEST(test_traverse_preorder_empty) {
    BinarySearchTree<int> tree;

    std::ostringstream oss;
    tree.traverse_preorder(oss);

    ASSERT_EQUAL(oss.str(), "");
}

TEST(test_traverse_preorder_degenerate) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);

    std::ostringstream oss;
    tree.traverse_preorder(oss);

    ASSERT_EQUAL(oss.str(), "1 2 3 4 ");
}

// ========================================
// SORTING INVARIANT TESTS
// ========================================

TEST(test_sorting_invariant_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_single) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_valid_tree) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_after_many_inserts) {
    BinarySearchTree<int> tree;
    for (int i = 0; i < 20; ++i) {
        tree.insert(i);
    }
    ASSERT_TRUE(tree.check_sorting_invariant());
}

// ========================================
// COPY CONSTRUCTOR TESTS
// ========================================

TEST(test_copy_constructor_empty) {
    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree2(tree1);

    ASSERT_TRUE(tree2.empty());
    ASSERT_EQUAL(tree2.size(), 0u);
}

TEST(test_copy_constructor_single) {
    BinarySearchTree<int> tree1;
    tree1.insert(5);

    BinarySearchTree<int> tree2(tree1);

    ASSERT_EQUAL(tree2.size(), 1u);
    ASSERT_TRUE(tree2.find(5) != tree2.end());
}

TEST(test_copy_constructor_multiple) {
    BinarySearchTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);
    tree1.insert(3);
    tree1.insert(7);

    BinarySearchTree<int> tree2(tree1);

    ASSERT_EQUAL(tree2.size(), tree1.size());
    ASSERT_EQUAL(tree2.height(), tree1.height());

    // Verify all elements are present
    ASSERT_TRUE(tree2.find(10) != tree2.end());
    ASSERT_TRUE(tree2.find(5) != tree2.end());
    ASSERT_TRUE(tree2.find(15) != tree2.end());
    ASSERT_TRUE(tree2.find(3) != tree2.end());
    ASSERT_TRUE(tree2.find(7) != tree2.end());
}

TEST(test_copy_constructor_independence) {
    BinarySearchTree<int> tree1;
    tree1.insert(5);
    tree1.insert(3);

    BinarySearchTree<int> tree2(tree1);

    // Modify tree1
    tree1.insert(7);

    // tree2 should be unchanged
    ASSERT_EQUAL(tree1.size(), 3u);
    ASSERT_EQUAL(tree2.size(), 2u);
    ASSERT_TRUE(tree1.find(7) != tree1.end());
    ASSERT_TRUE(tree2.find(7) == tree2.end());
}

// ========================================
// ASSIGNMENT OPERATOR TESTS
// ========================================

TEST(test_assignment_empty) {
    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree2;
    tree2.insert(10);

    tree2 = tree1;

    ASSERT_TRUE(tree2.empty());
    ASSERT_EQUAL(tree2.size(), 0u);
}

TEST(test_assignment_multiple) {
    BinarySearchTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);

    BinarySearchTree<int> tree2;
    tree2.insert(100);
    tree2.insert(200);

    tree2 = tree1;

    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_TRUE(tree2.find(10) != tree2.end());
    ASSERT_TRUE(tree2.find(5) != tree2.end());
    ASSERT_TRUE(tree2.find(15) != tree2.end());
    ASSERT_TRUE(tree2.find(100) == tree2.end());
    ASSERT_TRUE(tree2.find(200) == tree2.end());
}

TEST(test_assignment_self) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);

    tree = tree;  // Self-assignment

    ASSERT_EQUAL(tree.size(), 2u);
    ASSERT_TRUE(tree.find(10) != tree.end());
    ASSERT_TRUE(tree.find(5) != tree.end());
}

TEST(test_assignment_independence) {
    BinarySearchTree<int> tree1;
    tree1.insert(5);
    tree1.insert(3);

    BinarySearchTree<int> tree2;
    tree2 = tree1;

    // Modify tree1
    tree1.insert(7);

    // tree2 should be unchanged
    ASSERT_EQUAL(tree1.size(), 3u);
    ASSERT_EQUAL(tree2.size(), 2u);
    ASSERT_TRUE(tree1.find(7) != tree1.end());
    ASSERT_TRUE(tree2.find(7) == tree2.end());
}

// ========================================
// EDGE CASE TESTS
// ========================================

TEST(test_large_tree) {
    BinarySearchTree<int> tree;

    // Insert 100 elements
    for (int i = 0; i < 100; ++i) {
        tree.insert(i);
    }

    ASSERT_EQUAL(tree.size(), 100u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    // Verify all elements
    for (int i = 0; i < 100; ++i) {
        ASSERT_TRUE(tree.find(i) != tree.end());
    }
}

TEST(test_left_degenerate_tree) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    // Should be a chain going left
    ASSERT_EQUAL(tree.size(), 5u);
    ASSERT_EQUAL(tree.height(), 5u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    auto min_it = tree.min_element();
    ASSERT_EQUAL(*min_it, 1);

    auto max_it = tree.max_element();
    ASSERT_EQUAL(*max_it, 5);
}

TEST(test_right_degenerate_tree) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    // Should be a chain going right
    ASSERT_EQUAL(tree.size(), 5u);
    ASSERT_EQUAL(tree.height(), 5u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    auto min_it = tree.min_element();
    ASSERT_EQUAL(*min_it, 1);

    auto max_it = tree.max_element();
    ASSERT_EQUAL(*max_it, 5);
}

TEST(test_string_tree) {
    BinarySearchTree<std::string> tree;

    tree.insert("dog");
    tree.insert("cat");
    tree.insert("elephant");
    tree.insert("ant");
    tree.insert("zebra");

    ASSERT_EQUAL(tree.size(), 5u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    std::vector<std::string> elements;
    for (const std::string &s : tree) {
        elements.push_back(s);
    }

    // Should be sorted alphabetically
    ASSERT_EQUAL(elements[0], "ant");
    ASSERT_EQUAL(elements[1], "cat");
    ASSERT_EQUAL(elements[2], "dog");
    ASSERT_EQUAL(elements[3], "elephant");
    ASSERT_EQUAL(elements[4], "zebra");
}

TEST(test_double_tree) {
    BinarySearchTree<double> tree;

    tree.insert(3.14);
    tree.insert(2.71);
    tree.insert(1.41);
    tree.insert(4.20);

    ASSERT_EQUAL(tree.size(), 4u);

    auto min_it = tree.min_element();
    ASSERT_EQUAL(*min_it, 1.41);

    auto max_it = tree.max_element();
    ASSERT_EQUAL(*max_it, 4.20);
}

TEST(test_custom_comparator) {
    // Tree with greater<int> comparator (reverse order)
    BinarySearchTree<int, std::greater<int>> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    // Min with greater comparator should return the largest value
    auto min_it = tree.min_element();
    ASSERT_EQUAL(*min_it, 9);

    // Max with greater comparator should return the smallest value
    auto max_it = tree.max_element();
    ASSERT_EQUAL(*max_it, 1);

    // In-order traversal should be in descending order
    std::ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "9 7 5 3 1 ");
}

TEST(test_perfect_tree) {
    BinarySearchTree<int> tree;

    // Create a perfect binary tree
    //       4
    //      / \
    //     2   6
    //    / \ / \
    //   1  3 5  7

    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    ASSERT_EQUAL(tree.size(), 7u);
    ASSERT_EQUAL(tree.height(), 3u);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_begin_points_to_minimum) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(20);

    auto begin_it = tree.begin();
    auto min_it = tree.min_element();

    ASSERT_TRUE(begin_it == min_it);
    ASSERT_EQUAL(*begin_it, 3);
}

TEST_MAIN()
