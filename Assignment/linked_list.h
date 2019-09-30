#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>


/* Node for LinkedList, below.
   Instances of this shouldn't have to be created outside this module. */
typedef struct LinkedListNode
{
    struct LinkedListNode* prev;        /* Previous node in the list. */
    struct LinkedListNode* next;        /* Next node in the list. */
    void* data;                         /* Arbitrary data stored in node. */
} LinkedListNode;


/* Generic linked list.
   Use createLinkedList() to create an empty linked list.
   To "free" the linked list, just remove all the nodes using removeFirst(),
   removeLast(), or removeAll(). */
typedef struct
{
    LinkedListNode* head;       /* First node in the list. */
    LinkedListNode* tail;       /* Last node in the list. */
    size_t size;                /* Number of nodes in the list. */
} LinkedList;


/* Creates an empty linked list. */
LinkedList createLinkedList(void);

/* Inserts a new node with the given data at the front of the linked list. */
void insertFirst(LinkedList* list, void* data);

/* Inserts a new node with the given data at the back of the linked list. */
void insertLast(LinkedList* list, void* data);

/* Removes the first node, if there is one.
 * If the removal occurs, returns the removed node's data, otherwise returns
 * NULL. */
void* removeFirst(LinkedList* list);

/* Removes the last node, if there is one.
 * If the removal occurs, returns the removed node's data, otherwise returns
 * NULL. */
void* removeLast(LinkedList* list);

/* Removes all nodes and frees their data. */
void removeAll(LinkedList* list);

/* Invokes the callback on the data of each element, traversed from the front
 * of the list to the back. */
void iterateForward(LinkedList* list, void (*callback)(void*, void*),
    void* callbackData);

/* Invokes the callback on the data of each element, traversed from the back
 * of the list to the front. */
void iterateReverse(LinkedList* list, void (*callback)(void*, void*),
    void* callbackData);


#endif
