#include "unity.h"

void test_dummy(void) {
  // test stuff
  TEST_ASSERT_EQUAL(1, 1);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_dummy);
  return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
 * For native dev-platform or for some embedded frameworks
 */
int main(void) { return runUnityTests(); }
