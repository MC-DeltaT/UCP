#include "linked_list.h"

#include <assert.h>
#include <stdlib.h>


/* Frees a linked list node and sets it to NULL.
 * Returns the node's data (i.e does NOT free the data). */
void* freeNode(LinkedListNode** node)
{
    void* data = (*node)->data;

    (*node)->prev = NULL;
    (*node)->next = NULL;
    (*node)->data = NULL;
    free(*node);
    *node = NULL;

    return data;
}



LinkedList createLinkedList(void)
{
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}


void insertFirst(LinkedList* list, void* data)
{
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->prev = NULL;

    if (list->head)
    {
        assert(list->tail);
        newNode->next = list->head;
        list->head->prev = newNode;
    }
    else
    {
        assert(!list->tail);
        newNode->next = NULL;
        list->tail = newNode;
    }
    list->head = newNode;
}


void insertLast(LinkedList* list, void* data)
{
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->next = NULL;

    if (list->tail)
    {
        assert(list->head);
        newNode->prev = list->tail;
        list->tail->next = newNode;
    }
    else
    {
        assert(!list->head);
        newNode->prev = NULL;
        list->head = newNode;
    }
    list->tail = newNode;
}


void* removeFirst(LinkedList* list)
{
    void* data = NULL;
    LinkedListNode* oldHead = list->head;
    LinkedListNode* newHead = NULL;

    if (oldHead)
    {
        assert(list->tail);
        newHead = oldHead->next;
        if (newHead)
        {
            newHead->prev = NULL;
        }
        else
        {
            list->tail = NULL;
        }
        list->head = newHead;
        data = freeNode(&oldHead);
    }

    return data;
}


void* removeLast(LinkedList* list)
{
    void* data = NULL;
    LinkedListNode* oldTail = list->tail;
    LinkedListNode* newTail = NULL;

    if (oldTail)
    {
        assert(list->head);
        newTail = oldTail->prev;
        if (newTail)
        {
            newTail->next = NULL;
        }
        else
        {
            list->head = NULL;
        }
        list->tail = newTail;
        data = freeNode(&oldTail);
    }

    return data;
}


void removeAll(LinkedList* list)
{
    LinkedListNode* node = list->head;
    LinkedListNode* next;

    while (node)
    {
        next = node->next;
        free(freeNode(&node));
        node = next;
    }

    list->head = NULL;
    list->tail = NULL;
}


void iterateForward(LinkedList* list, void (*callback)(void*, void*),
                    void* callbackData)
{
    LinkedListNode* node = list->head;

    while (node)
    {
        callback(node->data, callbackData);
        node = node->next;
    }
}


void iterateReverse(LinkedList* list, void (*callback)(void*, void*),
                    void* callbackData)
{
    LinkedListNode* node = list->tail;

    while (node)
    {
        callback(node->data, callbackData);
        node = node->prev;
    }
    
}
