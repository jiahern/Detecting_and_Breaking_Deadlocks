#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "utils.h"

// Trigger boolean for Task2
bool isTask2(bool trigger)
{
    if (trigger == TRUE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Get the file name based on the user input condition
char *getFileName(int argc, char *argv[], char *fileName, bool *trigger)
{
    for (int i = 0; i < argc; i++)
    {
        // Condition to trigger is Task 2
        if (!strcmp(argv[i], "-e"))
        {
            for (int j = 0; j < argc; j++)
            {
                if (!strcmp(argv[j], "-f"))
                {
                    *trigger = IS_TASK2;
                    fileName = argv[j + 1];

                    return fileName;
                }
            }
        }

        // Condition to trigger not Task 2
        else if (!strcmp(argv[i], "-f"))
        {

            *trigger = NOT_TASK2;
            fileName = argv[i + 1];
            return fileName;
        };
    }
    return 0;
}

// Reference from COMP30023 Ass1 Help - File Reading (Linux & C)
// Scan the file contents
content_t *scanFileContent(char *fileName, int *countLines)
{
    int maxLines = FILE_MAX_LINES;

    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    content_t *fileContents = malloc(sizeof(content_t) * maxLines);
    if (fileContents == NULL)
    {
        fprintf(stderr, "Malloc failure\n");
        exit(EXIT_FAILURE);
    }

    unsigned int col1, col2, col3;

    while (fscanf(fp, "%u %u %u", &col1, &col2, &col3) == FILE_ELEMENT)
    {
        if (*countLines == maxLines)
        {
            maxLines *= 2;

            fileContents = realloc(fileContents, sizeof(content_t) * maxLines);

            if (fileContents == NULL)
            {
                fprintf(stderr, "Realloc failure\n");
                exit(EXIT_FAILURE);
            }
        }

        fileContents[*countLines].processID = col1;
        fileContents[*countLines].lockedID = col2;
        fileContents[*countLines].waitingID = col3;

        *countLines += 1;
    }

    return fileContents;
}

// Take the file contents parse into the node
void readFileIntoNode(content_t *fileContents, int amountProcesses, graph_t *graph)
{

    node_t *processNode, *lockedNode, *waitNode;
    unsigned int processID, lockedID, waitID;
    int i;

    // Assign each corresponding value into the array
    for (i = 0; i < amountProcesses; i++)
    {
        processID = fileContents[i].processID;
        lockedID = fileContents[i].lockedID;
        waitID = fileContents[i].waitingID;

        // Creating Node for each ID
        processNode = createNewNode(graph, processID, PROCESS_TYPE);
        lockedNode = createNewNode(graph, lockedID, FILE_LOCKED_TYPE);
        waitNode = createNewNode(graph, waitID, FILE_WAIT_TYPE);

        // Implement Relationship of the Node
        processNode->next = waitNode;
        lockedNode->next = processNode;
    }
}

// Create new node and allocate them to the appropriate type
node_t *createNewNode(graph_t *graph, unsigned int id, int type)
{
    node_t *newNode;
    if ((newNode = isInExistingGraph(id, type, graph)) != NULL)
    {
        return newNode;
    }
    newNode = malloc(sizeof(node_t));
    assert(newNode);

    // Initial all the given data
    newNode->id = id;
    newNode->type = type;
    newNode->next = NULL;
    newNode->visited = NOT_VISITED;

    insertIntoList(graph, newNode);

    if (newNode->type == PROCESS_TYPE)
    {
        graph->amountProcesses++;
    }
    else if (newNode->type == FILE_LOCKED_TYPE || newNode->type == FILE_WAIT_TYPE)
    {
        graph->amountFiles++;
    }

    return newNode;
}

// Add the specific node into the list
void insertIntoList(graph_t *graph, node_t *newNode)
{
    // realloc the dynamic memory if it exceeded
    if (graph->amountNodes >= graph->maxAmountNodes)
    {
        graph->maxAmountNodes *= 2;
        graph->arrayOfList = realloc(graph->arrayOfList, sizeof(node_t *) * graph->maxAmountNodes);
    }
    graph->arrayOfList[graph->amountNodes] = newNode;
    graph->amountNodes++;
}
