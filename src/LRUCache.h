/**
 * @file LRUCache.h
 * @brief Declares the LRUCache class.
 *
 * The cache combines:
 *   - An unordered_map<int, Node*> for O(1) key lookup
 *   - A DoublyLinkedList for O(1) LRU ordering
 *
 * Together they give O(1) amortised time for both get() and put().
 *
 * Statistics tracked:
 *   - cacheHits   : number of successful get() calls
 *   - cacheMisses : number of get() calls that returned -1
 */

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <unordered_map>
#include <string>
#include "DoublyLinkedList.h"

class LRUCache {
private:
    int capacity;                          ///< Maximum number of entries
    int cacheHits;                         ///< Total successful lookups
    int cacheMisses;                       ///< Total missed lookups
    DoublyLinkedList list;                 ///< MRU-ordered list of nodes
    std::unordered_map<int, Node*> map;    ///< key -> Node* lookup table

public:
    /**
     * @brief Constructs an LRU Cache with a fixed capacity.
     * @param capacity Maximum number of key-value pairs. Must be >= 1.
     */
    explicit LRUCache(int capacity);

    // ------------------------------------------------------------------ //
    //  Core API                                                            //
    // ------------------------------------------------------------------ //

    /**
     * @brief Retrieve the value for `key`.
     *
     * If the key is found, the node is promoted to MRU position and the
     * value is returned. Otherwise returns -1.
     *
     * Time Complexity: O(1)
     *
     * @param key  The key to look up.
     * @return     Value associated with `key`, or -1 if not present.
     */
    int get(int key);

    /**
     * @brief Insert or update the key-value pair.
     *
     * If `key` already exists, its value is updated and the node is
     * promoted to MRU.  If the cache is at capacity, the LRU entry is
     * evicted before insertion.
     *
     * Time Complexity: O(1)
     *
     * @param key   The key to insert or update.
     * @param value The value to associate with `key`.
     */
    void put(int key, int value);

    // ------------------------------------------------------------------ //
    //  Display / Diagnostics                                               //
    // ------------------------------------------------------------------ //

    /** @brief Print the full cache state (MRU → LRU). */
    void printCache() const;

    /** @brief Print key/value of the least-recently-used item. */
    void printLRU() const;

    /** @brief Print key/value of the most-recently-used item. */
    void printMRU() const;

    /** @brief Print cumulative hit/miss statistics. */
    void printStats() const;

    // ------------------------------------------------------------------ //
    //  Accessors                                                           //
    // ------------------------------------------------------------------ //

    int getCacheHits()   const;
    int getCacheMisses() const;
    int getSize()        const;
    int getCapacity()    const;
};

#endif // LRUCACHE_H
