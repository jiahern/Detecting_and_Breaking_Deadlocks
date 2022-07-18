#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "problems.h"
#include "utils.h"
#include "struc.h"

int main(int argc, char *argv[])
{
    // Identify which Task and proceed read file
    bool triggerTask2 = NOT_TASK2;
    char *fileName = NULL;
    fileName = getFileName(argc, argv, fileName, &triggerTask2);

    int fileLinesAmount = 0;
    content_t *fileContents = scanFileContent(fileName, &fileLinesAmount);

    // create empty graph
    graph_t *graph = createEmptyGraph();

    // TASK 1
    readFileIntoNode(fileContents, fileLinesAmount, graph);

    printf("Processes %d\nFiles %d\n", graph->amountProcesses, graph->amountFiles);
    // END TASK 1

    // TASK 2 - 5
    int amountProcesses = graph->amountProcesses;
    int len = 0;
    unsigned int deadlockList[amountProcesses];

    // Detect if there is deadlock
    if (detectDeadlock(graph, deadlockList, &len))
    {
        printf("Deadlock detected\n");

        printf("Terminate");
        for (int i = 0; i < len; i++)
        {
            printf(" %u", deadlockList[i]);
        }

        printf("\n");
    }

    else
    {
        // When it is Task2
        if (isTask2(triggerTask2))
        {
            printf("Execution time %d\n", getExecutionTime(fileContents, fileLinesAmount));
        }
        else
        // When it is not Task2
        {
            printf("No deadlocks\n");
        }
    }
    return 0;
}
