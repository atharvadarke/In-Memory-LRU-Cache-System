/**
 * @file main.cpp
 * @brief Demonstration driver for the LRU Cache.
 *
 * Runs the exact example from the requirements, then follows up with a
 * more comprehensive walkthrough to exercise all public API endpoints.
 *
 * Compile (g++):
 *   g++ -std=c++17 -Wall -Wextra -o lru_cache \
 *       src/main.cpp src/LRUCache.cpp src/DoublyLinkedList.cpp
 *
 * Run:
 *   ./lru_cache        (Linux / macOS)
 *   lru_cache.exe      (Windows)
 */

#include <iostream>
#include "LRUCache.h"

// Handy helpers ─────────────────────────────────────────────────────────── //

static void section(const std::string& title) {
    std::cout << "\n\n╔══════════════════════════════════════════╗\n";
    std::cout << "║  " << title;
    // pad to fixed width
    int pad = 40 - static_cast<int>(title.size());
    for (int i = 0; i < pad; ++i) std::cout << ' ';
    std::cout << "║\n";
    std::cout << "╚══════════════════════════════════════════╝\n";
}

static void step(const std::string& op) {
    std::cout << "\n>>> " << op << "\n";
}

// ─────────────────────────────────────────────────────────────────────────  //
//  Demo 1 – Required example from the specification                          //
// ─────────────────────────────────────────────────────────────────────────  //
void demo_required() {
    section("DEMO 1 – Required Specification Example");
    std::cout << "  Cache capacity: 3\n";

    LRUCache cache(3);

    step("put(1, 10)");
    cache.put(1, 10);

    step("put(2, 20)");
    cache.put(2, 20);

    step("put(3, 30)");
    cache.put(3, 30);

    step("get(1) → should return 10");
    int val = cache.get(1);
    std::cout << "  Result: " << val << "\n";

    step("put(4, 40)  [capacity full → evict LRU which is key=2]");
    cache.put(4, 40);

    step("printCache()");
    cache.printCache();

    std::cout << "\n  LRU item: "; cache.printLRU();
    std::cout << "  MRU item: "; cache.printMRU();

    cache.printStats();
}

// ─────────────────────────────────────────────────────────────────────────  //
//  Demo 2 – Hit / Miss / Eviction walkthrough                                //
// ─────────────────────────────────────────────────────────────────────────  //
void demo_hits_misses() {
    section("DEMO 2 – Hit / Miss / Eviction Walkthrough");
    std::cout << "  Cache capacity: 3\n";

    LRUCache cache(3);

    step("put(10, 100) | put(20, 200) | put(30, 300)");
    cache.put(10, 100);
    cache.put(20, 200);
    cache.put(30, 300);
    cache.printCache();

    step("get(10)  → HIT (also promotes key=10 to MRU)");
    std::cout << "  Result: " << cache.get(10) << "\n";
    cache.printCache();

    step("get(99)  → MISS (key does not exist)");
    std::cout << "  Result: " << cache.get(99) << "\n";

    step("put(40, 400)  → cache full; LRU (key=20) evicted");
    cache.put(40, 400);
    cache.printCache();

    step("get(20)  → MISS (was evicted)");
    std::cout << "  Result: " << cache.get(20) << "\n";

    step("put(10, 999)  → update existing key=10, promote to MRU");
    cache.put(10, 999);
    cache.printCache();

    cache.printStats();
}

// ─────────────────────────────────────────────────────────────────────────  //
//  Demo 3 – Edge cases                                                        //
// ─────────────────────────────────────────────────────────────────────────  //
void demo_edge_cases() {
    section("DEMO 3 – Edge Cases");

    // Cache of capacity 1
    std::cout << "\n  [A] Capacity-1 cache\n";
    LRUCache tiny(1);
    tiny.put(1, 111);
    std::cout << "  get(1)=" << tiny.get(1) << "  (expected 111)\n";
    tiny.put(2, 222);   // evicts key=1
    std::cout << "  get(1)=" << tiny.get(1) << "  (expected -1, evicted)\n";
    std::cout << "  get(2)=" << tiny.get(2) << "  (expected 222)\n";
    tiny.printCache();

    // Repeated put of the same key
    std::cout << "\n  [B] Repeated update of the same key\n";
    LRUCache c(3);
    c.put(5, 50);
    c.put(5, 55);
    c.put(5, 500);
    std::cout << "  get(5)=" << c.get(5) << "  (expected 500)\n";
    c.printCache();

    // get on empty cache
    std::cout << "\n  [C] get() on empty cache\n";
    LRUCache empty(2);
    std::cout << "  get(1)=" << empty.get(1) << "  (expected -1)\n";
}

// ─────────────────────────────────────────────────────────────────────────  //
//  main                                                                       //
// ─────────────────────────────────────────────────────────────────────────  //
int main() {
    std::cout << "==============================================\n";
    std::cout << "   High-Performance In-Memory LRU Cache Demo  \n";
    std::cout << "==============================================\n";

    demo_required();
    demo_hits_misses();
    demo_edge_cases();

    std::cout << "\n\n[All demos completed successfully]\n";
    return 0;
}
