#ifndef STRUC
#define STRUC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node node_t;

struct node
{
    unsigned int id;
    int type;
    int visited;
    node_t *next;
};

typedef struct graph graph_t;

struct graph
{
    // array of node_t*
    node_t **arrayOfList;

    // array elements quantity
    int amountNodes;
    int amountProcesses;
    int amountFiles;
    int maxAmountNodes;
};

typedef struct
{
    unsigned int processID;
    unsigned int lockedID;
    unsigned int waitingID;
} content_t;

// Prototype
// Declare and create an empty graph
graph_t *createEmptyGraph();

// End of Prototype

#endif
