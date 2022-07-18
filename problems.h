#ifndef PROBLEMS
#define PROBLEMS

#include <stdbool.h>
#include "struc.h"
#include "utils.h"

// Check the specific node whether in the existing graph andd return the node.
node_t *isInExistingGraph(unsigned int id, int type, graph_t *graph);

// Detect the deadlock and put the filtered process ID into the deadlock list.
int detectDeadlock(graph_t *graph, unsigned int *deadlockList, int *len);

// Detect whether it is a cycle graph
int detectCycle(node_t *node);

// Determine the chosen node is in the node or not
bool traversedNode(node_t *node, graph_t *graph);

// Calculate the Execution time of Task 2
unsigned int getExecutionTime(content_t *array, int n);

// Sort out the smallest element
int getSmallestElement(node_t *element);

// Filter out duplicate value
bool filterDistinctValue(unsigned int *deadlockList, unsigned int processID, int len);

#endif
