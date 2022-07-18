
#include "problems.h"

// Check the specific node whether in the existing graph andd return the node.
node_t *isInExistingGraph(unsigned int id, int type, graph_t *graph)
{
    int i;

    for (i = 0; i < graph->amountNodes; i++)
    {
        // if it is Processor type with same ID
        if (type == PROCESS_TYPE)
        {
            if ((id == (graph->arrayOfList[i]->id)) && type == (graph->arrayOfList[i]->type))
            {
                return graph->arrayOfList[i];
            }
        }
        else
        {
            // if it is FILE type with same ID
            if (id == (graph->arrayOfList[i]->id))
            {
                if ((graph->arrayOfList[i]->type) == FILE_LOCKED_TYPE || (graph->arrayOfList[i]->type) == FILE_WAIT_TYPE)
                {
                    return graph->arrayOfList[i];
                }
            }
        }
    }

    return NULL;
}

// Detect the deadlock and put the filtered process ID into the deadlock list.
int detectDeadlock(graph_t *graph, unsigned int *deadlockList, int *len)
{
    int i;
    bool isDeadlock = false;
    unsigned int smallest;
    for (i = 0; i < graph->amountNodes; i++)
    {
        // Get the Process type ID and filter it to put in the deadlock list.
        if (detectCycle(graph->arrayOfList[i]) == TRUE && (graph->arrayOfList[i]->type == PROCESS_TYPE))
        {
            isDeadlock = true;

            // get the smallest element within the deadlock cycle
            smallest = getSmallestElement(graph->arrayOfList[i]);
            if (filterDistinctValue(deadlockList, smallest, *len))
            {
                deadlockList[*len] = smallest;
                *len += 1;
            }
        }
    }
    if (isDeadlock == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Detect whether it is a cycle graph
int detectCycle(node_t *node)
{
    // create a graph to store the visited graph
    graph_t *visitedGraph = createEmptyGraph();

    // while loop to find out condition of the node
    node_t *start = node;
    while (node->next != NULL)
    {
        node = node->next;

        // if next node is NULL then the list has reached an end, so not cycle graph
        if (node == NULL)
        {
            return false;
        };

        // filter out those visited node
        if (traversedNode(node, visitedGraph))
        {
            break;
        }

        // The node is not visited so mark it as visited
        else
        {
            node->visited = VISITED;
            insertIntoList(visitedGraph, node);
        }

        // If the last node point to the start node, then means its a cycle, deadlock appeared
        if (node == start)
        {
            return true;
        }
    }

    return false;
}

// Determine the chosen node is in the node or not
bool traversedNode(node_t *node, graph_t *graph)
{
    int i = 0;
    for (i = 0; i < graph->amountNodes; i++)
    {
        // if it has same id and process type
        if (node->type == PROCESS_TYPE)
        {
            if ((node->id == (graph->arrayOfList[i]->id)) && node->type == (graph->arrayOfList[i]->type))
            {
                return true;
            }
        }
        else
        {
            // if it has same id and file type
            if (node->id == (graph->arrayOfList[i]->id))
            {
                if ((graph->arrayOfList[i]->type) == FILE_LOCKED_TYPE || (graph->arrayOfList[i]->type) == FILE_WAIT_TYPE)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Referenced from https://www.studytonight.com/c-programs/c-program-to-find-the-maximum-repeating-element-in-an-array
// Calculate the Execution time of Task 2 by getting the highest frequency of the waiting file section and added by 1.
unsigned int getExecutionTime(content_t *array, int n)
{

    int i, j, maxElement, count, result;
    int maxCount = 0;
    int highestFrequency = 0;
    // Get the element which has highest frequency.
    /* Frequency of each element is counted and checked.If it's greater than the utmost count element we found till now, then it is updated accordingly  */
    for (i = 0; i < n; i++) // For loop to hold each element
    {
        count = 1;
        for (j = i + 1; j < n; j++) // For loop to check for duplicate elements
        {
            if (array[j].waitingID == array[i].waitingID)
            {
                count++; // Increment  count
                /* If count of current element is more than
                maxCount, then update maxElement */
                if (count > maxCount)
                {
                    maxElement = array[j].waitingID;
                }
            }
        }
    }

    // Calculate the highest element frequency
    for (i = 0; i < n; i++)
    {
        if (array[i].waitingID == maxElement)
        {
            highestFrequency += 1;
        }
    }

    // Result of execution time is the highest frequency waiting type node's frequency, added by 1
    result = highestFrequency + 1;

    return result;
}

// Sort out the smallest element
int getSmallestElement(node_t *element)
{

    node_t *start = element;
    unsigned int smallest = start->id;

    while (element->next != start)
    {
        if (element->id < smallest)
        {
            smallest = element->id;
        }
        element = element->next;
    }
    return smallest;
}

// Filter out duplicate value
bool filterDistinctValue(unsigned int *deadlockList, unsigned int processID, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (processID == deadlockList[i])
        {
            return false;
        }
    }
    return true;
}
