#include "unity.h"

void setUp(void) {
    // Set up code here
}

void tearDown(void) {
    // Clean up code here
}

void test_example(void) {
    // Example test case
    TEST_ASSERT_EQUAL(1, 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    return UNITY_END();
}
