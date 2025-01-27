//
// Created by Varda on 26/10/2020.
//

#ifndef EX2_WINTER2021_EX2_H
#define EX2_WINTER2021_EX2_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/**
 * General Assumptions:
 *    1. You may assume that the linked list does not contain cycles.
 *    2. You may assume that all nodes and their data arrays are allocated dynamically.
 *    3. You may assume that there are no two nodes that their data fields point to the
 *       same array.
 */


#define FAILURE 0
#define DECIMAL 10
#define MAX_CHARS 1000000
#define BUFFER_SIZE 1024
#define BUFFER_SIZE 1024
#define START_CHAR "s"
#define END_CHAR "e"
#define DELIMITERS ",\r\n"
#define NODE_ALLOC_ERROR "ERROR: Failed to allocate memory to node data.\n"
#define INVALID_NODE_ERROR "ERROR: Invalid node. This node doesn't exist\n"
#define ADD_START_LL_ERR "ERROR: Failed to add Node to start - Pointer provided for Linked List is NULL.\n"
#define ADD_START_NODE_ERR "ERROR: Failed to add Node to start - Pointer provided for Node is NULL.\n"
#define AVG_ALLOC_ERROR "ERROR: Failed to allocate memory to average array.\n"
#define REM_NODE_LL_ERR "ERROR: Failed to remove Node - Pointer provided for Linked List is NULL.\n"
#define REM_NODE_ERROR "ERROR: Failed to remove Node - Pointer provided for Node is NULL.\n"
#define LIST_PTR_ERR "ERROR: Pointer provided for Linked List is NULL.\n"
#define NUM_ELEM_ERR "ERROR: Provided num_elements_in_returned_array pointer is NULL.\n"
#define ALLOC_LIST_ERR "ERROR: Failed to allocate memory to linked list.\n"
/*
 * Do not add or remove any field of the struct and do not change their names!!!
 */

typedef struct Node {
    /** ??? **/ struct Node *next; // this member should allow access to next node in the list. (think - pointer or instance?)
    /** ??? **/ struct Node *prev; // this member should allow access to next node in the list. (think - pointer or instance?)
    /** ??? **/ int *data; // this member should be an array of ints. (think - signed or unsigned?)
    /** ??? **/ size_t len; // this member should be the number of elements in the data array. (think - signed or unsigned?)
} Node;

typedef struct LinkedList {
    /** ??? **/ Node *head; // this member should allow access to the first node in the linked list. (think - pointer or instance?)
    /** ??? **/ Node *tail; // this member should allow access to the node at the end of the linked list. (think - pointer or instance?)
    size_t size_ll;
} LinkedList;

/**
 * This struct holds the root node of the BST
 */
typedef struct int_list_head {
    struct Node *list_root;
} int_list_head;


/**
 * Adds a node as the head of the list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_start_linked_list(LinkedList *list, Node *node);


/**
 * Adds a node as the tail of the list.
 *
 * Assumptions:
 *   You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_end_linked_list(LinkedList *list, Node *node);


/**
 * removes a node from the list and frees it's resources.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You cannot assume the node is in the list. In this case don't free its resources.
 *    To be sure - you are supposed to compare the given node to the nodes in the list using == operator.
 *
 * In case of errors:
 *    Invalid pointer - print informative error message to stderr and return from function.
 *
 * @param list pointer to list to remove a node from.
 * @param node pointer to the node to remove from the list.
 */
void remove_node(LinkedList *list, Node *node);


/**
 * Frees the resources (all dynamic allocations) of the given list.
 *
 * Assumptions:
 *    You cannot assume the pointer is valid.
 *
 * In case of errors:
 *    Invalid pointer - This means there is nothing to free, just return from function.
 *
 * @param list the list to free.
 */
void free_linked_list(LinkedList *list);


/**
 * calculates the grade average of every node in the linked list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You don't know the number of nodes in the linkedlist in advance.
 *    You can assume that there is at least one node with data != NULL (i.e. len > 0).
 *    You can assume that for each node 'len' is indeed the length of 'data'
 *     (in particular len=0 <=> data=NULL).
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Node with NULL data - don't count the node in the calculation.
 *
 * @param list: LinkedList pointer to linked list from whom to calculate grade averages.
 * @param num_elements_in_returned_array: pointer to unsigned long, that should contain the number of nodes in the list
 * (for nodes with data != NULL) when the function finishes execution. To be clear - at the start of the function,
 * (*num_elements_in_returned_array) is a garbage value, and this function should set its value.
 *    @Note: Nodes with NULL data should not be count in the calculation.
 *    Therefore *num_elements_in_returned_array <= numOfNodes.
 * @return array of grade averages per node. To be clear - this means you should
 * calculate the grade average of every node and save it into an array, which you will return from the function.
 */
double *get_averages(LinkedList *list, size_t *num_elements_in_returned_array);


/**
 * opens a file from a given filename and parses it's contents into a LinkedList.
 *
 * Assumptions:
 *    You cannot assume the filename is OK (meaning - you cannot assume it is a valid path to a file).
 *    You cannot assume anything on the number of ints in a row of the file, just that it is >= 1.
 *    You can assume that if the file opened, then it is exactly in the format specified in the exercise PDF.
 *    You can assume max line length of 1024.
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    File open fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *
 * Think - in what mode should we open this file? (read? write? append?)
 *
 * @param file filename of input file that needs to be parsed.
 * @return pointer to LinkedList instance, whose nodes and data arrays were parsed from the given file.
 */
LinkedList *parse_linked_list(const char * filename);

#endif //EX2_WINTER2021_EX2_H
