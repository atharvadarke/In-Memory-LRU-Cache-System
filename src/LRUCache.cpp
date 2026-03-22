/**
 * @file LRUCache.cpp
 * @brief Implements the LRUCache class.
 *
 * Core Idea
 * ---------
 * Combining an unordered_map (O(1) lookup) with a custom doubly linked list
 * (O(1) insert/remove from arbitrary position via pointer) gives us O(1)
 * amortised time for both get() and put().
 *
 * List layout:  head(dummy) <-> [LRU] <-> ... <-> [MRU] <-> tail(dummy)
 *
 * Every time a key is accessed or inserted, its node is "moved to front"
 * (i.e., placed just before the dummy tail – the MRU position).
 * When eviction is needed, the node just after the dummy head (LRU) is removed.
 */

#include "LRUCache.h"
#include <iostream>
#include <iomanip>

// -------------------------------------------------------------------------- //
//  Constructor                                                                //
// -------------------------------------------------------------------------- //

LRUCache::LRUCache(int capacity)
    : capacity(capacity), cacheHits(0), cacheMisses(0) {}

// -------------------------------------------------------------------------- //
//  Core API                                                                   //
// -------------------------------------------------------------------------- //

/**
 * get(key)
 * --------
 * 1. Look up key in the hash map.
 * 2. If not found -> cache miss, return -1.
 * 3. If found    -> cache hit:
 *      a. Remove the node from its current position in the list.
 *      b. Re-insert it at MRU (just before tail).
 *      c. Return node->value.
 *
 * Time Complexity: O(1)  (unordered_map lookup + constant DLL ops)
 */
int LRUCache::get(int key) {
    auto it = map.find(key);
    if (it == map.end()) {
        ++cacheMisses;
        return -1;
    }

    ++cacheHits;
    Node* node = it->second;

    // Promote node to MRU position
    list.removeNode(node);
    list.addToFront(node);

    return node->value;
}

/**
 * put(key, value)
 * ---------------
 * Case A – key already exists:
 *   Update value and promote node to MRU.
 *
 * Case B – key is new:
 *   If at capacity, evict the LRU node (remove from list AND from map).
 *   Create a new node, add to MRU position, and insert into map.
 *
 * Time Complexity: O(1)
 */
void LRUCache::put(int key, int value) {
    auto it = map.find(key);

    if (it != map.end()) {
        // ---- Case A: update existing key ----
        Node* node = it->second;
        node->value = value;

        list.removeNode(node);
        list.addToFront(node);
    } else {
        // ---- Case B: new key ----
        if (list.getSize() == capacity) {
            // Evict LRU: remove from list and erase from hash map
            Node* lru = list.removeLRU();
            map.erase(lru->key);
            delete lru; // free heap memory
        }

        // Insert new node at MRU position
        Node* newNode = new Node(key, value);
        list.addToFront(newNode);
        map[key] = newNode;
    }
}

// -------------------------------------------------------------------------- //
//  Display / Diagnostics                                                      //
// -------------------------------------------------------------------------- //

void LRUCache::printCache() const {
    std::cout << "\n========================================\n";
    std::cout << "  Cache State  (size=" << list.getSize()
              << " / capacity=" << capacity << ")\n";
    std::cout << "========================================\n";

    if (list.getSize() == 0) {
        std::cout << "  (cache is empty)\n";
    } else {
        std::cout << "  Order: ";
        list.printList();
    }
    std::cout << "========================================\n";
}

void LRUCache::printLRU() const {
    Node* lru = list.getLRUNode();
    if (lru == nullptr) {
        std::cout << "  [LRU] Cache is empty.\n";
    } else {
        std::cout << "  [LRU] key=" << lru->key
                  << "  value=" << lru->value << "\n";
    }
}

void LRUCache::printMRU() const {
    Node* mru = list.getMRUNode();
    if (mru == nullptr) {
        std::cout << "  [MRU] Cache is empty.\n";
    } else {
        std::cout << "  [MRU] key=" << mru->key
                  << "  value=" << mru->value << "\n";
    }
}

void LRUCache::printStats() const {
    int total = cacheHits + cacheMisses;
    double hitRate = (total > 0) ? (100.0 * cacheHits / total) : 0.0;

    std::cout << "\n--- Cache Statistics ---\n";
    std::cout << std::left
              << std::setw(16) << "  Cache Hits:"   << cacheHits   << "\n"
              << std::setw(16) << "  Cache Misses:" << cacheMisses << "\n"
              << std::setw(16) << "  Total Gets:"   << total       << "\n"
              << std::fixed << std::setprecision(1)
              << std::setw(16) << "  Hit Rate:"     << hitRate << "%\n";
    std::cout << "------------------------\n";
}

// -------------------------------------------------------------------------- //
//  Accessors                                                                  //
// -------------------------------------------------------------------------- //

int LRUCache::getCacheHits()   const { return cacheHits;       }
int LRUCache::getCacheMisses() const { return cacheMisses;     }
int LRUCache::getSize()        const { return list.getSize();  }
int LRUCache::getCapacity()    const { return capacity;        }
