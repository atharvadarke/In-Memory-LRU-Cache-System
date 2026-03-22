/**
 * @file DoublyLinkedList.cpp
 * @brief Implements the DoublyLinkedList class for the LRU Cache.
 *
 * Sentinel nodes (head & tail) simplify all insert/remove operations by
 * eliminating edge-case nullptr checks.
 */

#include "DoublyLinkedList.h"
#include <iostream>

// -------------------------------------------------------------------------- //
//  Constructor / Destructor                                                    //
// -------------------------------------------------------------------------- //

DoublyLinkedList::DoublyLinkedList() : size(0) {
    // Create dummy sentinel nodes
    head = new Node(0, 0);
    tail = new Node(0, 0);

    // Wire them together: head <-> tail
    head->next = tail;
    tail->prev = head;
}

DoublyLinkedList::~DoublyLinkedList() {
    // Walk from head, deleting every node including sentinels
    Node* curr = head;
    while (curr != nullptr) {
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
}

// -------------------------------------------------------------------------- //
//  Modifiers                                                                  //
// -------------------------------------------------------------------------- //

/**
 * Inserts `node` immediately before the dummy tail, making it the MRU node.
 *
 *  Before: ... <-> prev <-> tail
 *  After : ... <-> prev <-> node <-> tail
 */
void DoublyLinkedList::addToFront(Node* node) {
    Node* prev = tail->prev;

    prev->next  = node;
    node->prev  = prev;
    node->next  = tail;
    tail->prev  = node;

    ++size;
}

/**
 * Detaches `node` from the list without deleting it.
 *
 *  Before: ... <-> prevNode <-> node <-> nextNode <-> ...
 *  After : ... <-> prevNode <-> nextNode <-> ...
 */
void DoublyLinkedList::removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = nullptr;
    node->next = nullptr;

    --size;
}

/**
 * Removes and returns the LRU node (the real node just after the dummy head).
 * Returns nullptr if the list is empty.
 */
Node* DoublyLinkedList::removeLRU() {
    if (size == 0) return nullptr;

    Node* lru = head->next; // first real node
    removeNode(lru);
    return lru;
}

// -------------------------------------------------------------------------- //
//  Accessors                                                                  //
// -------------------------------------------------------------------------- //

Node* DoublyLinkedList::getLRUNode() const {
    if (size == 0) return nullptr;
    return head->next;
}

Node* DoublyLinkedList::getMRUNode() const {
    if (size == 0) return nullptr;
    return tail->prev;
}

int DoublyLinkedList::getSize() const {
    return size;
}

/**
 * Prints the cache from MRU (most-recent) → LRU (least-recent).
 * Format: [MRU] key:value -> key:value -> ... -> [LRU]
 */
void DoublyLinkedList::printList() const {
    std::cout << "[MRU] ";
    Node* curr = tail->prev; // start at MRU
    while (curr != head) {
        std::cout << curr->key << ":" << curr->value;
        if (curr->prev != head) std::cout << " -> ";
        curr = curr->prev;
    }
    std::cout << " [LRU]" << std::endl;
}
