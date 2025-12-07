#ifndef UNIT_TEST_FRAMEWORK_HPP
#define UNIT_TEST_FRAMEWORK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>

// Simple unit testing framework
class TestCase {
public:
    std::string name;
    void (*test_func)();

    TestCase(const std::string &name_, void (*test_func_)())
        : name(name_), test_func(test_func_) {}
};

class TestRegistry {
public:
    static TestRegistry& get_instance() {
        static TestRegistry instance;
        return instance;
    }

    void add_test(const std::string &name, void (*test_func)()) {
        tests.push_back(TestCase(name, test_func));
    }

    int run_tests() {
        int failed = 0;
        std::cout << "Running " << tests.size() << " test(s)" << std::endl;

        for (size_t i = 0; i < tests.size(); ++i) {
            std::cout << "Running test: " << tests[i].name << std::endl;
            try {
                tests[i].test_func();
                std::cout << "PASS" << std::endl;
            } catch (const std::exception &e) {
                std::cout << "FAIL: " << e.what() << std::endl;
                ++failed;
            } catch (...) {
                std::cout << "FAIL: Unknown exception" << std::endl;
                ++failed;
            }
        }

        std::cout << "\n";
        if (failed == 0) {
            std::cout << "ALL TESTS PASSED!" << std::endl;
        } else {
            std::cout << failed << " test(s) FAILED" << std::endl;
        }

        return failed;
    }

private:
    std::vector<TestCase> tests;
    TestRegistry() {}
};

class TestRegistrar {
public:
    TestRegistrar(const std::string &name, void (*test_func)()) {
        TestRegistry::get_instance().add_test(name, test_func);
    }
};

class TestFailure : public std::exception {
public:
    TestFailure(const std::string &msg, const std::string &file, int line)
        : message(msg), filename(file), line_number(line) {
        std::ostringstream oss;
        oss << filename << ":" << line_number << ": " << message;
        full_message = oss.str();
    }

    const char* what() const noexcept override {
        return full_message.c_str();
    }

private:
    std::string message;
    std::string filename;
    int line_number;
    std::string full_message;
};

#define TEST(test_name) \
    static void test_name(); \
    static TestRegistrar test_name##_registrar(#test_name, test_name); \
    static void test_name()

#define TEST_MAIN() \
    int main() { \
        return TestRegistry::get_instance().run_tests(); \
    }

#define ASSERT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            throw TestFailure("Expected true but was false: " #expr, __FILE__, __LINE__); \
        } \
    } while(0)

#define ASSERT_FALSE(expr) \
    do { \
        if (expr) { \
            throw TestFailure("Expected false but was true: " #expr, __FILE__, __LINE__); \
        } \
    } while(0)

#define ASSERT_EQUAL(expected, actual) \
    do { \
        if (!((expected) == (actual))) { \
            std::ostringstream oss; \
            oss << "Expected " #actual " to be " << (expected) \
                << " but was " << (actual); \
            throw TestFailure(oss.str(), __FILE__, __LINE__); \
        } \
    } while(0)

#define ASSERT_NOT_EQUAL(expected, actual) \
    do { \
        if ((expected) == (actual)) { \
            std::ostringstream oss; \
            oss << "Expected " #actual " to NOT be " << (expected); \
            throw TestFailure(oss.str(), __FILE__, __LINE__); \
        } \
    } while(0)

#define ASSERT_ALMOST_EQUAL(expected, actual, epsilon) \
    do { \
        if (std::abs((expected) - (actual)) > (epsilon)) { \
            std::ostringstream oss; \
            oss << "Expected " #actual " to be within " << (epsilon) \
                << " of " << (expected) << " but was " << (actual); \
            throw TestFailure(oss.str(), __FILE__, __LINE__); \
        } \
    } while(0)

#endif // UNIT_TEST_FRAMEWORK_HPP
