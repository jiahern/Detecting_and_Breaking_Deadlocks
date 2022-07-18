#ifndef UTILS
#define UTILS

#include "struc.h"
#include "problems.h"

#define FILE_ELEMENT 3
#define PROCESS_TYPE 4
#define FILE_LOCKED_TYPE 5
#define FILE_WAIT_TYPE 6
#define TRUE 1
#define FALSE 0
#define VISITED 1
#define NOT_VISITED 0
#define IS_TASK2 1
#define NOT_TASK2 0
#define MAX_NODES 40
#define FILE_MAX_LINES 4

// Prototype

// Trigger boolean for Task2
bool isTask2(bool trigger);

// Get the filename from user input argument and consider the -e -f situation
char *getFileName(int argc, char *argv[], char *fileName, bool *trigger);

// Scan the file contents line by line
content_t *scanFileContent(char *file_name, int *count_lines);

// Take the file contents parse into the node
void readFileIntoNode(content_t *fileContents, int amountProcesses, graph_t *graph);

// Create new node and allocate them to the appropriate type
node_t *createNewNode(graph_t *graph, unsigned int id, int type);

// Add the specific node into the list
void insertIntoList(graph_t *graph, node_t *newNode);

// End of Prototype

#endif
