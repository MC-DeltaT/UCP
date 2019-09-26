#ifndef LINKED_LIST_H
#define LINKED_LIST_H


typedef struct LinkedListNode {
    struct LinkedListNode* prev;
    struct LinkedListNode* next;
    void* data;
} LinkedListNode;


typedef struct {
    LinkedListNode* head;
    LinkedListNode* tail;
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
