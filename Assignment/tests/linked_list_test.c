/* Unit tests for the linked list module. */

#include "linked_list_test.h"

#include "../linked_list.h"
#include "common.h"

#include <assert.h>
#include <stdlib.h>


/* Controls the maximum size of the linked list during testing. */
#define TEST_SIZE 100000ul

/* Dereferences a void* into an unsigned long.
 * Only because I'm too lazy to type it out each time. */
#define VTOUL(p) (*(unsigned long*)p)


/* PRIVATE INTERFACE */


/* Creates one piece of test data, an unsigned long, and sets its value to x. */
static void* testData(unsigned long x)
{
    void* p = malloc(sizeof(unsigned long));
    VTOUL(p) = x;
    return p;
}


/* Asserts that the given test data has value x. */
static void assertData(unsigned long x, void const* data)
{
    assert(data != NULL);
    assert(VTOUL(data) == x);
}


/* Asserts that the given list node has data equal to x. */
static void assertHasData(unsigned long x, LinkedListNode const* node)
{
    assert(node != NULL);
    assertData(x, node->data);
}


/* Tests createLinkedList(). */
static void createLinkedListTest(void)
{
    LinkedList list = createLinkedList();
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.size == 0);
}


/* Tests insertFirst(). */
static void insertFirstTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertFirst(&list, testData(i));
        assert(list.head != NULL);
        assert(list.tail != NULL);
        assert(list.size == i + 1ul);
        assert(list.tail->next == NULL);
        assert(list.head->prev == NULL);
        assertHasData(i, list.head);
    }

    removeAll(&list);
}


/* Tests insertLast(). */
static void insertLastTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        insertLast(&list, testData(i));
        assert(list.head != NULL);
        assert(list.tail != NULL);
        assert(list.size == i + 1ul);
        assert(list.head->prev == NULL);
        assert(list.tail->next == NULL);
        assertHasData(i, list.tail);
    }

    removeAll(&list);
}


/* Tests removeFirst(). */
static void removeFirstTest(void)
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
        assert(list.size == TEST_SIZE - 1ul - i);
        assertData(i, data);
        free(data);
    }

    assert(list.head == NULL);
    assert(list.tail == NULL);
}


/* Tests removeLast(). */
static void removeLastTest(void)
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
        assert(list.size == TEST_SIZE - 1ul - i);
        assertData(i, data);
        free(data);
    }

    assert(list.head == NULL);
    assert(list.tail == NULL);
}


/* Tests removeAll(). */
static void removeAllTest(void)
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
    assert(list.size == 0);
}


/* Helper for iterateForwardTest(), used by iterateForward() to visit nodes. */
static void iterateForwardCallback(void* data, void* expected)
{
    assertData(VTOUL(expected), data);
    ++VTOUL(expected);
}


/* Tests iterateForward(). */
static void iterateForwardTest(void)
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


/* Helper for iterateReverseTest(), used by iterateReverse() to visit nodes. */
static void iterateReverseCallback(void* data, void* expected)
{
    assertData(VTOUL(expected), data);
    ++VTOUL(expected);
}


/* Tests iterateReverse(). */
static void iterateReverseTest(void)
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



/* PUBLIC INTERFACE */


void linkedListTest(void)
{
    moduleTestHeader("linked list");

    runUnitTest("createLinkedList()", createLinkedListTest);
    runUnitTest("insertFirst()", insertFirstTest);
    runUnitTest("insertLast()", insertLastTest);
    runUnitTest("removeFirst()", removeFirstTest);
    runUnitTest("removeLast()", removeLastTest);
    runUnitTest("removeAll()", removeAllTest);
    runUnitTest("iterateForward()", iterateForwardTest);
    runUnitTest("iterateReverse()", iterateReverseTest);
}
