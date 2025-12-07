#include "Map.hpp"
#include "unit_test_framework.hpp"
#include <string>

// ========================================
// BASIC MAP OPERATIONS
// ========================================

TEST(test_map_empty_and_size) {
    Map<int, std::string> map;

    // Empty map
    ASSERT_TRUE(map.empty());
    ASSERT_EQUAL(map.size(), 0u);

    // Insert one element
    map.insert({1, "one"});
    ASSERT_FALSE(map.empty());
    ASSERT_EQUAL(map.size(), 1u);

    // Insert more elements
    map.insert({2, "two"});
    map.insert({3, "three"});
    ASSERT_EQUAL(map.size(), 3u);
}

// ========================================
// INSERT OPERATIONS
// ========================================

TEST(test_map_insert) {
    Map<int, std::string> map;

    // Insert new element
    auto result1 = map.insert({5, "five"});
    ASSERT_TRUE(result1.second);  // Should return true (inserted)
    ASSERT_EQUAL(result1.first->first, 5);
    ASSERT_EQUAL(result1.first->second, "five");

    // Insert duplicate key
    auto result2 = map.insert({5, "FIVE"});
    ASSERT_FALSE(result2.second);  // Should return false (not inserted)
    ASSERT_EQUAL(result2.first->first, 5);
    ASSERT_EQUAL(result2.first->second, "five");  // Original value unchanged

    // Insert more elements
    map.insert({3, "three"});
    map.insert({7, "seven"});
    map.insert({1, "one"});

    ASSERT_EQUAL(map.size(), 4u);
}

// ========================================
// FIND OPERATIONS
// ========================================

TEST(test_map_find) {
    Map<int, std::string> map;
    map.insert({10, "ten"});
    map.insert({5, "five"});
    map.insert({15, "fifteen"});

    // Find existing keys
    auto it1 = map.find(10);
    ASSERT_TRUE(it1 != map.end());
    ASSERT_EQUAL(it1->first, 10);
    ASSERT_EQUAL(it1->second, "ten");

    auto it2 = map.find(5);
    ASSERT_TRUE(it2 != map.end());
    ASSERT_EQUAL(it2->second, "five");

    // Find non-existent key
    auto it3 = map.find(100);
    ASSERT_TRUE(it3 == map.end());
}

// ========================================
// OPERATOR[] TESTS
// ========================================

TEST(test_map_bracket_operator) {
    Map<std::string, int> map;

    // Access non-existent key (should insert with default value)
    int &val1 = map["apple"];
    ASSERT_EQUAL(val1, 0);  // Default value for int is 0
    ASSERT_EQUAL(map.size(), 1u);

    // Modify value
    val1 = 5;
    ASSERT_EQUAL(map["apple"], 5);

    // Access existing key
    map["banana"] = 10;
    ASSERT_EQUAL(map["banana"], 10);
    ASSERT_EQUAL(map.size(), 2u);

    // Modify existing key
    map["banana"] = 20;
    ASSERT_EQUAL(map["banana"], 20);
    ASSERT_EQUAL(map.size(), 2u);  // Size unchanged
}

TEST(test_map_bracket_insert_and_modify) {
    Map<int, double> map;

    // Insert via []
    map[1] = 1.1;
    map[2] = 2.2;
    map[3] = 3.3;

    ASSERT_EQUAL(map.size(), 3u);
    ASSERT_EQUAL(map[1], 1.1);
    ASSERT_EQUAL(map[2], 2.2);
    ASSERT_EQUAL(map[3], 3.3);

    // Modify via []
    map[2] = 99.9;
    ASSERT_EQUAL(map[2], 99.9);
    ASSERT_EQUAL(map.size(), 3u);
}

// ========================================
// ITERATOR TESTS
// ========================================

TEST(test_map_iterator) {
    Map<int, std::string> map;

    // Empty map iteration
    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        ++count;
    }
    ASSERT_EQUAL(count, 0);

    // Insert elements
    map.insert({5, "five"});
    map.insert({3, "three"});
    map.insert({7, "seven"});
    map.insert({1, "one"});

    // Iterate and verify sorted order (by key)
    std::vector<int> keys;
    for (auto it = map.begin(); it != map.end(); ++it) {
        keys.push_back(it->first);
    }

    ASSERT_EQUAL(keys.size(), 4u);
    ASSERT_EQUAL(keys[0], 1);
    ASSERT_EQUAL(keys[1], 3);
    ASSERT_EQUAL(keys[2], 5);
    ASSERT_EQUAL(keys[3], 7);
}

TEST(test_map_range_based_loop) {
    Map<std::string, int> map;
    map.insert({"dog", 4});
    map.insert({"cat", 3});
    map.insert({"elephant", 8});
    map.insert({"ant", 3});

    // Range-based for loop
    std::vector<std::string> keys;
    for (const auto &pair : map) {
        keys.push_back(pair.first);
    }

    // Should be in alphabetical order
    ASSERT_EQUAL(keys.size(), 4u);
    ASSERT_EQUAL(keys[0], "ant");
    ASSERT_EQUAL(keys[1], "cat");
    ASSERT_EQUAL(keys[2], "dog");
    ASSERT_EQUAL(keys[3], "elephant");
}

// ========================================
// MIXED OPERATIONS
// ========================================

TEST(test_map_mixed_operations) {
    Map<int, std::string> map;

    // Use [] to insert
    map[10] = "ten";
    map[5] = "five";

    // Use insert to add more
    map.insert({15, "fifteen"});
    map.insert({3, "three"});

    ASSERT_EQUAL(map.size(), 4u);

    // Find existing
    auto it = map.find(5);
    ASSERT_TRUE(it != map.end());
    ASSERT_EQUAL(it->second, "five");

    // Modify via []
    map[5] = "FIVE";
    ASSERT_EQUAL(map[5], "FIVE");

    // Try to insert duplicate
    auto result = map.insert({5, "five again"});
    ASSERT_FALSE(result.second);
    ASSERT_EQUAL(map[5], "FIVE");  // Value unchanged
}

// ========================================
// COPY AND ASSIGNMENT
// ========================================

TEST(test_map_copy_constructor) {
    Map<int, std::string> map1;
    map1[1] = "one";
    map1[2] = "two";
    map1[3] = "three";

    // Copy constructor
    Map<int, std::string> map2(map1);

    ASSERT_EQUAL(map2.size(), 3u);
    ASSERT_EQUAL(map2[1], "one");
    ASSERT_EQUAL(map2[2], "two");
    ASSERT_EQUAL(map2[3], "three");

    // Modify map1
    map1[1] = "ONE";

    // map2 should be unchanged
    ASSERT_EQUAL(map2[1], "one");
}

TEST(test_map_assignment_operator) {
    Map<int, std::string> map1;
    map1[10] = "ten";
    map1[20] = "twenty";

    Map<int, std::string> map2;
    map2[100] = "hundred";

    // Assignment
    map2 = map1;

    ASSERT_EQUAL(map2.size(), 2u);
    ASSERT_EQUAL(map2[10], "ten");
    ASSERT_EQUAL(map2[20], "twenty");
    ASSERT_TRUE(map2.find(100) == map2.end());

    // Modify map1
    map1[10] = "TEN";

    // map2 should be unchanged
    ASSERT_EQUAL(map2[10], "ten");
}

// ========================================
// EDGE CASES
// ========================================

TEST(test_map_single_element) {
    Map<int, int> map;
    map[42] = 100;

    ASSERT_EQUAL(map.size(), 1u);
    ASSERT_EQUAL(map[42], 100);
    ASSERT_TRUE(map.find(42) != map.end());
    ASSERT_TRUE(map.find(99) == map.end());
}

TEST(test_map_default_values) {
    Map<std::string, int> int_map;
    Map<std::string, double> double_map;
    Map<std::string, std::string> string_map;

    // Accessing non-existent keys should create default values
    ASSERT_EQUAL(int_map["key"], 0);
    ASSERT_EQUAL(double_map["key"], 0.0);
    ASSERT_EQUAL(string_map["key"], "");
}

TEST(test_map_large) {
    Map<int, int> map;

    // Insert many elements
    for (int i = 0; i < 100; ++i) {
        map[i] = i * 10;
    }

    ASSERT_EQUAL(map.size(), 100u);

    // Verify all elements
    for (int i = 0; i < 100; ++i) {
        ASSERT_EQUAL(map[i], i * 10);
    }

    // Iterate in order
    int expected = 0;
    for (const auto &pair : map) {
        ASSERT_EQUAL(pair.first, expected);
        ASSERT_EQUAL(pair.second, expected * 10);
        ++expected;
    }
}

TEST(test_map_string_keys_and_values) {
    Map<std::string, std::string> map;

    map["name"] = "Alice";
    map["city"] = "New York";
    map["country"] = "USA";

    ASSERT_EQUAL(map.size(), 3u);
    ASSERT_EQUAL(map["name"], "Alice");
    ASSERT_EQUAL(map["city"], "New York");
    ASSERT_EQUAL(map["country"], "USA");

    // Modify
    map["city"] = "Boston";
    ASSERT_EQUAL(map["city"], "Boston");
}

TEST(test_map_custom_comparator) {
    // Map with reverse order comparator
    Map<int, std::string, std::greater<int>> map;

    map[5] = "five";
    map[3] = "three";
    map[7] = "seven";
    map[1] = "one";

    // Iterate (should be in descending order)
    std::vector<int> keys;
    for (const auto &pair : map) {
        keys.push_back(pair.first);
    }

    ASSERT_EQUAL(keys.size(), 4u);
    ASSERT_EQUAL(keys[0], 7);
    ASSERT_EQUAL(keys[1], 5);
    ASSERT_EQUAL(keys[2], 3);
    ASSERT_EQUAL(keys[3], 1);
}

TEST(test_map_word_count) {
    // Practical example: word counting
    Map<std::string, int> word_count;

    std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};

    for (const auto &word : words) {
        word_count[word]++;
    }

    ASSERT_EQUAL(word_count["apple"], 3);
    ASSERT_EQUAL(word_count["banana"], 2);
    ASSERT_EQUAL(word_count["cherry"], 1);
}

TEST_MAIN()
