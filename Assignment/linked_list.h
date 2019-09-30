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
   To "free" the linked list, just remove all the nodes using listRemoveFirst(),
   listRemoveLast(), or listRemoveAll(). */
typedef struct
{
    LinkedListNode* head;       /* First node in the list. */
    LinkedListNode* tail;       /* Last node in the list. */
    size_t size;                /* Number of nodes in the list. */
} LinkedList;


/* Same as the result of createLinkedList(), but can be used in constant
   initialisation.*/
#define EMPTY_LINKED_LIST {NULL, NULL, 0};


/* Creates an empty linked list. */
LinkedList createLinkedList(void);

/* Inserts a new node with the given data at the front of the linked list. */
void listInsertFirst(LinkedList* list, void* data);

/* Inserts a new node with the given data at the back of the linked list. */
void listInsertLast(LinkedList* list, void* data);

/* Removes the first node, if there is one.
 * If the removal occurs, returns the removed node's data, otherwise returns
 * NULL. */
void* listRemoveFirst(LinkedList* list);

/* Removes the last node, if there is one.
 * If the removal occurs, returns the removed node's data, otherwise returns
 * NULL. */
void* listRemoveLast(LinkedList* list);

/* Removes all nodes, but NOT does free their data. */
void listRemoveAll(LinkedList* list);

/* Removes all nodes and frees their data. */
void listFreeAndRemoveAll(LinkedList* list);

/* Invokes the callback on the data of each element, traversed from the front
 * of the list to the back. */
void listIterateForward(LinkedList const* list,
    void (*callback)(void** nodeData, void* callbackData), void* callbackData);

/* Invokes the callback on the data of each element, traversed from the back
 * of the list to the front. */
void listIterateReverse(LinkedList const* list,
    void (*callback)(void** nodeData, void* callbackData), void* callbackData);


#endif
