/**
 * @file test_cases.cpp
 * @brief Unit-style tests for the LRU Cache.
 *
 * Each test function prints PASS or FAIL.
 * Compile (from project root):
 *
 *   g++ -std=c++17 -Wall -Wextra -o run_tests \
 *       tests/test_cases.cpp src/LRUCache.cpp src/DoublyLinkedList.cpp \
 *       -I src
 *
 * Run:
 *   ./run_tests        (Linux / macOS)
 *   run_tests.exe      (Windows)
 */

#include <iostream>
#include <string>
#include "../src/LRUCache.h"

// -------------------------------------------------------------------------- //
//  Minimal test framework                                                     //
// -------------------------------------------------------------------------- //

static int passed = 0;
static int failed = 0;

static void check(const std::string& name, bool condition) {
    if (condition) {
        std::cout << "  [PASS] " << name << "\n";
        ++passed;
    } else {
        std::cout << "  [FAIL] " << name << "  <-- *** FAILED ***\n";
        ++failed;
    }
}

// -------------------------------------------------------------------------- //
//  Test suites                                                                //
// -------------------------------------------------------------------------- //

void test_basic_put_get() {
    std::cout << "\n--- test_basic_put_get ---\n";
    LRUCache c(3);
    c.put(1, 10);
    c.put(2, 20);
    c.put(3, 30);

    check("get(1) == 10", c.get(1) == 10);
    check("get(2) == 20", c.get(2) == 20);
    check("get(3) == 30", c.get(3) == 30);
}

void test_get_missing_key() {
    std::cout << "\n--- test_get_missing_key ---\n";
    LRUCache c(2);
    c.put(5, 50);

    check("get(99) == -1  (not found)",       c.get(99) == -1);
    check("get(0)  == -1  (never inserted)",  c.get(0)  == -1);
}

void test_eviction_order() {
    std::cout << "\n--- test_eviction_order ---\n";
    // capacity 3: put 1,2,3 → get(1) promotes 1 → put 4 evicts 2
    LRUCache c(3);
    c.put(1, 10);
    c.put(2, 20);
    c.put(3, 30);

    c.get(1);          // promote 1 to MRU; order: 2 (LRU) -> 3 -> 1 (MRU)
    c.put(4, 40);      // evict LRU=2

    check("key=4  present after insert",  c.get(4) == 40);
    check("key=1  still present (was MRU)", c.get(1) == 10);
    check("key=3  still present",         c.get(3) == 30);
    check("key=2  evicted",               c.get(2) == -1);
}

void test_update_existing_key() {
    std::cout << "\n--- test_update_existing_key ---\n";
    LRUCache c(3);
    c.put(1, 100);
    c.put(1, 200);   // update
    c.put(1, 300);   // update again

    check("updated value == 300", c.get(1) == 300);
    check("size still == 1",      c.getSize() == 1);
}

void test_capacity_one() {
    std::cout << "\n--- test_capacity_one ---\n";
    LRUCache c(1);
    c.put(1, 111);
    check("get(1) == 111", c.get(1) == 111);

    c.put(2, 222);   // evicts key=1
    check("get(1) == -1 (evicted)", c.get(1) == -1);
    check("get(2) == 222",          c.get(2) == 222);
}

void test_lru_promoted_on_get() {
    std::cout << "\n--- test_lru_promoted_on_get ---\n";
    // Fill capacity-2 cache with keys 1, 2.
    // get(1) promotes 1 → put(3) evicts 2 (not 1).
    LRUCache c(2);
    c.put(1, 10);
    c.put(2, 20);
    c.get(1);       // promote 1 to MRU
    c.put(3, 30);   // evicts LRU=2

    check("key=1 still present", c.get(1) == 10);
    check("key=2 evicted",       c.get(2) == -1);
    check("key=3 present",       c.get(3) == 30);
}

void test_hit_miss_counters() {
    std::cout << "\n--- test_hit_miss_counters ---\n";
    LRUCache c(2);
    c.put(1, 10);
    c.put(2, 20);

    c.get(1);   // hit
    c.get(1);   // hit
    c.get(9);   // miss
    c.get(8);   // miss
    c.get(7);   // miss

    check("cacheHits   == 2", c.getCacheHits()   == 2);
    check("cacheMisses == 3", c.getCacheMisses() == 3);
}

void test_large_sequence() {
    std::cout << "\n--- test_large_sequence (1000 keys, capacity 100) ---\n";
    LRUCache c(100);

    // Insert keys 0..499
    for (int i = 0; i < 500; ++i) c.put(i, i * 2);

    // Only the last 100 keys (400..499) should survive
    bool evicted_ok  = true;
    bool survived_ok = true;

    for (int i = 0; i < 400; ++i)
        if (c.get(i) != -1) { evicted_ok = false; break; }

    for (int i = 400; i < 500; ++i)
        if (c.get(i) != i * 2) { survived_ok = false; break; }

    check("Keys 0..399 all evicted",       evicted_ok);
    check("Keys 400..499 all survived",    survived_ok);
    check("cache size == 100",             c.getSize() == 100);
}

// -------------------------------------------------------------------------- //
//  main                                                                       //
// -------------------------------------------------------------------------- //

int main() {
    std::cout << "==========================================\n";
    std::cout << "   LRU Cache - Test Suite\n";
    std::cout << "==========================================\n";

    test_basic_put_get();
    test_get_missing_key();
    test_eviction_order();
    test_update_existing_key();
    test_capacity_one();
    test_lru_promoted_on_get();
    test_hit_miss_counters();
    test_large_sequence();

    std::cout << "\n==========================================\n";
    std::cout << "  Results: " << passed << " passed, "
                               << failed << " failed\n";
    std::cout << "==========================================\n";

    return (failed == 0) ? 0 : 1;
}
