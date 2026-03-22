/**
 * @file DoublyLinkedList.h
 * @brief Declares the DoublyLinkedList class used as the ordered access structure
 *        inside the LRU Cache.
 *
 * Layout convention:
 *   head (dummy) <-> [LRU node] <-> ... <-> [MRU node] <-> tail (dummy)
 *
 * The most-recently-used item is always just before the dummy tail.
 * The least-recently-used item is always just after the dummy head.
 */

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Node.h"

class DoublyLinkedList {
private:
    Node* head; ///< Dummy head sentinel – its ->next is the LRU node
    Node* tail; ///< Dummy tail sentinel – its ->prev is the MRU node
    int   size; ///< Current number of real (non-sentinel) nodes

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    // ------------------------------------------------------------------ //
    //  Modifiers                                                           //
    // ------------------------------------------------------------------ //

    /** @brief Insert node right before the dummy tail (MRU position). */
    void addToFront(Node* node);

    /** @brief Detach a node from its current position (does NOT delete it). */
    void removeNode(Node* node);

    /** @brief Remove and return the node right after the dummy head (LRU). */
    Node* removeLRU();

    // ------------------------------------------------------------------ //
    //  Accessors                                                           //
    // ------------------------------------------------------------------ //

    /** @brief Return the LRU node without removing it (nullptr if empty). */
    Node* getLRUNode() const;

    /** @brief Return the MRU node without removing it (nullptr if empty). */
    Node* getMRUNode() const;

    /** @brief Return the current number of real nodes. */
    int getSize() const;

    /** @brief Print the cache contents from MRU → LRU. */
    void printList() const;
};

#endif // DOUBLYLINKEDLIST_H
