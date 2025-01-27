/**
 * FILE : ex2.c
 * WRITER : Amit Halbreich , amithalbreich , 208917393
 * EXERCISE : Programming Workshop in C & C++ ex2 fall semester 2021
 * DESCRIPTION: This project is about dealing with doubly-linked-lists
 * and nodes that contains int numbers as data.
 * First I read the given file in the correct format using strtok function. Select where
 * to add the node - head/tail of the linked list according to "s" or "e"
 * char in the start of the line.
 * I parse the char numbers to ints and insert data to the node one by one.
 * The process repeats until all nodes are added to the list.
 * Free linked list function is using remove node function to remove all
 * nodes one by one.
 * get_averages function calculates the average of ints data for each node
 * in the linked list and returns an array of doubles (average) with all the grade
 * averages.
 */

#include "ex2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/**
 * Sum function for double values.
 * Help function for get_averages function.
 *
 * @param array[] array of doubles to sum on.
 * @param size size of array members.
 *
 * @return Sum of all doubles in the array.
 */
double sum_int(const double array[], int size)
{
    double total = 0;

    for ( int i = 0; i < size; i++ )
    {
        total += array[i];
    }
    return total;
}

/**
 * Searches if node exists on a given linked list.
 *
 * @param list pointer to list to search a node in.
 * @param node pointer to the node to search in the list.
 *
 * @return true - if node was found in linked list, false - otherwise.
 */
bool search_node(LinkedList *const list, Node *const node) {
    Node *cur = list->head;
    if (node == NULL) {
        fprintf(stderr, INVALID_NODE_ERROR);
        return EXIT_FAILURE;
    }
    while (cur != NULL) {
        if (node == cur) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

/**
 * Creates a new node empty of any data that doesn't points to any
 * other node and has no length.
 *
 * @return A new node empty of any data that doesn't points to other nodes.
 */
Node *create_empty_node() {
    Node *node = calloc(1, sizeof(Node));
    if (node != NULL) {
        node->next = NULL;
        node->prev = NULL;
        node->data = NULL;
        node->len = 0;
    }
    return node;
}

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
void add_to_start_linked_list(LinkedList *const list, Node *const node) {
    if (list == NULL) {
        fprintf(stderr, ADD_START_LL_ERR);
        return;
    }
    if (node == NULL) {
        fprintf(stderr, ADD_START_NODE_ERR);
        return;
    }
    if (list->head == NULL) {
        list->head = list->tail = node;
        return;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

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
void add_to_end_linked_list(LinkedList *const list, Node *const node) {
    if (list == NULL) {
        fprintf(stderr, ADD_START_LL_ERR);
        return;
    }
    if (node == NULL) {
        fprintf(stderr, ADD_START_NODE_ERR);
        return;
    }
    if (list->tail == NULL) {
        list->head = list->tail = node;
        return;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}


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
void remove_node(LinkedList *const list, Node *const node) {
    if (list == NULL) {
        fprintf(stderr, REM_NODE_LL_ERR);
        return;
    }
    if (node == NULL) {
        fprintf(stderr, REM_NODE_ERROR);
        return;
    }
    Node *cur = list->head;
    Node *tmp = cur;
    bool is_found = search_node(list, node);
    if (is_found) {
        // e.g This is the first node in the list.
        if (node == list->head) {
            if (list->head == list->tail) {
                list->head = list->tail = NULL;
                free(tmp->data);
                tmp->data = NULL;
                free(node);
                tmp = NULL;
                return;
            }
            list->head = list->head->next;
            list->head->prev = NULL;
            free(tmp->data);
            tmp->data = NULL;
            free(node);
            tmp = NULL;
            return;
        }
        // e.g This is the last node in the list.
        if (node->next == NULL) {
            if (list->head == list->tail) {
                list->head = list->tail = NULL;
                free(tmp->data);
                tmp->data = NULL;
                free(node);
                tmp = NULL;
                return;
            }
            tmp = list->tail;
            list->tail = list->tail->prev;
            list->tail->next = NULL;
            free(tmp->data);
            tmp->data = NULL;
            free(node);
            tmp = NULL;
            return;
        }
        //All other case when the node is not the last/first Node.
        tmp = cur->next;
        cur->next = cur->next->next;
        cur->next->prev = cur;
        free(tmp->data);
        tmp->data = NULL;
        free(tmp);
        tmp = NULL;
        return;
    }
}

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
void free_linked_list(LinkedList *list) {
    if (list == NULL) {
        fprintf(stderr, "%s", LIST_PTR_ERR);
        return;
    }
    Node *cur = list->head;
    while (cur != NULL) {
        Node * holder = cur;
        cur = cur->next;
        remove_node(list,holder);
    }
    list->head = list->tail = NULL;
    free(list);
}


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
double *get_averages(LinkedList *const list, size_t *const num_elements_in_returned_array) {
    if (list == NULL) {
        fprintf(stderr, "%s", LIST_PTR_ERR);
        return NULL;
    }
    if (num_elements_in_returned_array == NULL) {
        fprintf(stderr, "%s", NUM_ELEM_ERR);
        return NULL;
    }
    Node * current = list->head;
    Node * cur = list->head;
    int node_counter = 0;
    int node_count = 0;
    while (cur != NULL) {
        if (cur->data){
            node_counter++;
        }
        cur = cur->next;
    }
    *num_elements_in_returned_array = 0;
    double *avg_array = calloc(node_counter,sizeof (double));
    if (avg_array == NULL){
        fprintf(stderr, "%s", AVG_ALLOC_ERROR);
        return NULL;
    }
    while (current != NULL){
        if (current->data != NULL){
            *num_elements_in_returned_array+=1;
            double * node_data = malloc(current->len * sizeof (double));
            double * tmp_node_data = node_data;
            if (tmp_node_data == NULL){
                fprintf(stderr, "%s", NODE_ALLOC_ERROR);
                free(node_data);
                return NULL;
            }
            for (int i = 0; i < (int)current->len; i++) {
                node_data[i] = (double)current->data[i];
            }
            double grade_avg = (sum_int(node_data, (int)current->len)) / (int)current->len;
            avg_array[node_count] = grade_avg;
            node_count++;
            free(node_data);
        }
        current = current->next;
    }
    return avg_array;
}

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
LinkedList *parse_linked_list(const char *const filename) {
    LinkedList *my_list = malloc(sizeof(LinkedList));
    if (my_list == NULL){
        printf("%s", ALLOC_LIST_ERR);
        return NULL;
    }
    my_list->head = NULL;
    my_list->tail = NULL;
    char * end_ptr;
    FILE *open_file = fopen(filename, "r"); // open the given file in read mode
    if (open_file == NULL) { // check the file opened correctly
        fprintf(stderr, "ERROR: Invalid file! Failed to open file properly :(\n");
        free(my_list);
        return NULL;
    }
    char buffer[BUFFER_SIZE] = {0}, *token = NULL;
    while (fgets(buffer, BUFFER_SIZE, open_file) != NULL) {
        Node *node = create_empty_node();
        token = strtok(buffer, DELIMITERS); // set the string to parse, read first token
        while (token != NULL) {
            if (strcmp(token, START_CHAR) == 0) {
                add_to_start_linked_list(my_list, node);
            } else if (strcmp(token, END_CHAR) == 0) {
                add_to_end_linked_list(my_list, node);
            } else {
                long tmp_content = strtol(token, &end_ptr, DECIMAL);
                int int_content = (int) tmp_content;
                if (node->data == NULL) {
                    node->data = calloc(1, sizeof(int));
                } else {
                    int * tmp_node_data = realloc(node->data, (node->len + 1) * sizeof(int));
                    if (tmp_node_data == NULL){
                        free(node->data);
                        return NULL;
                    }
                    node->data = tmp_node_data;
                }
                node->data[node->len] = int_content;
                node->len++;
            }
            token = strtok(NULL, DELIMITERS);
        }
    }
    fclose(open_file);
    return (my_list);
    }
