#include "linked_list.h"

#include <assert.h>
#include <stdlib.h>


#define TEST_SIZE 10000ul

/* Dereferences a void* into an unsigned long.
 * Only because I'm too lazy to type it out each time. */
#define VTOUL(p) (*(unsigned long*)p)


void* testData(unsigned long x)
{
    void* p = malloc(sizeof(unsigned long));
    VTOUL(p) = x;
    return p;
}


void assertData(unsigned long x, void const* data)
{
    assert(data);
    assert(VTOUL(data) == x);
}


void assertHasData(unsigned long x, LinkedListNode const* node)
{
    assert(node);
    assertData(x, node->data);
}


void testCreateLinkedList(void)
{
    LinkedList list = createLinkedList();
    assert(list.head == NULL);
    assert(list.tail == NULL);
}


void testInsertFirst(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertFirst(&list, testData(i));
        assert(list.head);
        assert(list.tail);
        assert(list.tail->next == NULL);
        assert(list.head->prev == NULL);
        assertHasData(i, list.head);
    }

    removeAll(&list);
}


void testInsertLast(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertLast(&list, testData(i));
        assert(list.head);
        assert(list.tail);
        assert(list.head->prev == NULL);
        assert(list.tail->next == NULL);
        assertHasData(i, list.tail);
    }

    removeAll(&list);
}


void testRemoveFirst(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();
    void* data;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertLast(&list, testData(i));
    }

    for (i = 0; i < TEST_SIZE; ++i)
    {
        data = removeFirst(&list);
        assertData(i, data);
        free(data);
    }
}


void testRemoveLast(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();
    void* data;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertFirst(&list, testData(i));
    }

    for (i = 0; i < TEST_SIZE; ++i)
    {
        data = removeLast(&list);
        assertData(i, data);
        free(data);
    }
}


void testRemoveAll(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertFirst(&list, testData(i));
    }

    removeAll(&list);
    assert(list.head == NULL);
    assert(list.tail == NULL);
}


void iterateForwardCallback(void* data, void* expected)
{
    assertData(VTOUL(expected), data);
    ++VTOUL(expected);
}


void testIterateForward(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertLast(&list, testData(i));
    }

    i = 0;
    iterateForward(&list, iterateForwardCallback, (void*)&i);

    removeAll(&list);
}


void iterateReverseCallback(void* data, void* expected)
{
    assertData(VTOUL(expected), data);
    ++VTOUL(expected);
}


void testIterateReverse(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertFirst(&list, testData(i));
    }

    i = 0;
    iterateReverse(&list, iterateReverseCallback, (void*)&i);

    removeAll(&list);
}


int main(void)
{
    testCreateLinkedList();
    testInsertFirst();
    testInsertLast();
    testRemoveFirst();
    testRemoveLast();
    testRemoveAll();
    testIterateForward();
    testIterateReverse();

    return 0;
}
