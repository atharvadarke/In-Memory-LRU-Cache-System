/**
 * @file Node.h
 * @brief Defines the Node class for the Doubly Linked List used in LRU Cache.
 *
 * Each node stores a key-value pair and pointers to its previous and next
 * neighbours in the list. The key is stored so that when a node is evicted
 * from the tail, we can remove its entry from the hash map in O(1).
 */

#ifndef NODE_H
#define NODE_H

class Node {
public:
    int key;    ///< Cache key (also used to erase from the hash map on eviction)
    int value;  ///< Cache value associated with the key
    Node* prev; ///< Pointer to the previous (less-recently-used) node
    Node* next; ///< Pointer to the next (more-recently-used) node

    /**
     * @brief Constructs a Node with given key and value.
     * @param k  The key to store.
     * @param v  The value to store.
     */
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

#endif // NODE_H
