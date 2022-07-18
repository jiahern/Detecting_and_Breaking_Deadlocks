#include "struc.h"
#include "utils.h"

// Declare and create an empty graph
graph_t *createEmptyGraph()
{

    graph_t *graph = malloc(sizeof(graph_t));
    graph->amountProcesses = 0;
    graph->amountFiles = 0;
    graph->amountNodes = 0;
    graph->maxAmountNodes = MAX_NODES;

    graph->arrayOfList = malloc(sizeof(node_t *) * graph->maxAmountNodes);
    assert(graph->arrayOfList);
    return graph;
}