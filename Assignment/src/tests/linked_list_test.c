/* Unit tests for the linked list module. */

#include "linked_list_test.h"

#include "common.h"
#include "../main/linked_list.h"

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


/* Tests EMPTY_LINKED_LIST. */
static void emptyLinkedListTest(void)
{
    LinkedList list = EMPTY_LINKED_LIST;
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.size == 0);
}


/* Tests listInsertFirst(). */
static void listInsertFirstTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        listInsertFirst(&list, testData(i));
        assert(list.head != NULL);
        assert(list.tail != NULL);
        assert(list.size == i + 1ul);
        assert(list.tail->next == NULL);
        assert(list.head->prev == NULL);
        assertHasData(i, list.head);
    }

    listFreeAndRemoveAll(&list);
}


/* Tests listInsertLast(). */
static void listInsertLastTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        listInsertLast(&list, testData(i));
        assert(list.head != NULL);
        assert(list.tail != NULL);
        assert(list.size == i + 1ul);
        assert(list.head->prev == NULL);
        assert(list.tail->next == NULL);
        assertHasData(i, list.tail);
    }

    listFreeAndRemoveAll(&list);
}


/* Tests listRemoveFirst(). */
static void listRemoveFirstTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();
    void* data;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        listInsertLast(&list, testData(i));
    }

    for (i = 0; i < TEST_SIZE; ++i)
    {
        data = listRemoveFirst(&list);
        assert(list.size == TEST_SIZE - 1ul - i);
        assertData(i, data);
        free(data);
    }

    assert(list.head == NULL);
    assert(list.tail == NULL);
}


/* Tests listRemoveLast(). */
static void listRemoveLastTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();
    void* data;

    for (i = 0; i < TEST_SIZE; ++i)
    {
        listInsertFirst(&list, testData(i));
    }

    for (i = 0; i < TEST_SIZE; ++i)
    {
        data = listRemoveLast(&list);
        assert(list.size == TEST_SIZE - 1ul - i);
        assertData(i, data);
        free(data);
    }

    assert(list.head == NULL);
    assert(list.tail == NULL);
}


/* Tests listRemoveAll(). */
static void listRemoveAllTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();
    unsigned long* data = (unsigned long*)malloc(
                            TEST_SIZE * sizeof(unsigned long));

    for (i = 0; i < TEST_SIZE; ++i)
    {
        listInsertFirst(&list, data + i);
    }

    listRemoveAll(&list);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.size == 0);

    free(data);
    data = NULL;
}


/* Tests listFreeAndRemoveAll(). */
static void listFreeAndRemoveAllTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        listInsertFirst(&list, testData(i));
    }

    listFreeAndRemoveAll(&list);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.size == 0);
}


/* Helper for listIterateForwardTest(), used by listIterateForward() to visit
   nodes. */
static void iterateForwardCallback(void** data, void* expected)
{
    assertData(VTOUL(expected), *data);
    ++VTOUL(expected);
}


/* Tests listIterateForward(). */
static void listIterateForwardTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        listInsertLast(&list, testData(i));
    }

    i = 0;
    listIterateForward(&list, iterateForwardCallback, &i);

    listFreeAndRemoveAll(&list);
}


/* Helper for listIterateReverseTest(), used by listIterateReverse() to visit
   nodes. */
static void iterateReverseCallback(void** data, void* expected)
{
    assertData(VTOUL(expected), *data);
    ++VTOUL(expected);
}


/* Tests listIterateReverse(). */
static void listIterateReverseTest(void)
{
    unsigned long i = 0;
    LinkedList list = createLinkedList();

    for (i = 0; i < TEST_SIZE; ++i)
    {
        listInsertFirst(&list, testData(i));
    }

    i = 0;
    listIterateReverse(&list, iterateReverseCallback, &i);

    listFreeAndRemoveAll(&list);
}



/* PUBLIC INTERFACE */


void linkedListTest(void)
{
    moduleTestHeader("linked list");

    runUnitTest("createLinkedList()", createLinkedListTest);
    runUnitTest("EMPTY_LINKED_LIST", emptyLinkedListTest);
    runUnitTest("listInsertFirst()", listInsertFirstTest);
    runUnitTest("listInsertLast()", listInsertLastTest);
    runUnitTest("listRemoveFirst()", listRemoveFirstTest);
    runUnitTest("listRemoveLast()", listRemoveLastTest);
    runUnitTest("listRemoveAll()", listRemoveAllTest);
    runUnitTest("listFreeAndRemoveAll()", listFreeAndRemoveAllTest);
    runUnitTest("listIterateForward()", listIterateForwardTest);
    runUnitTest("listIterateReverse()", listIterateReverseTest);
}
