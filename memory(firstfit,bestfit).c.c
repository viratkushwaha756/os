#include <stdio.h>
#define MAX 100

int blocks[MAX], processes[MAX], nBlocks, nProcesses, lastAllocIndex = 0;

void firstFit() {
    int allocation[nProcesses];
    for (int i = 0; i < nProcesses; i++) allocation[i] = -1;

    for (int i = 0; i < nProcesses; i++) {
        for (int j = 0; j < nBlocks; j++) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                blocks[j] -= processes[i];
                break;
            }
        }  
    }

    printf("\nFirst Fit Allocation:\n");
    printf("Process_No\tProcess Size\t Block Allocated\n");
    for (int i = 0; i < nProcesses; i++) {
        printf("%d\t\t\t\t%d\t\t\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit() {
    int allocation[nProcesses];
    for (int i = 0; i < nProcesses; i++) allocation[i] = -1;

    for (int i = 0; i < nProcesses; i++) {
        int best = -1;
        for (int j = 0; j < nBlocks; j++) {
            if (blocks[j] >= processes[i]) {
                if (best == -1 || blocks[j] < blocks[best]) {
                    best = j;
                }
            }
        }

        if (best != -1) {
            allocation[i] = best;
            blocks[best] -= processes[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    printf("Process No\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < nProcesses; i++) {
        printf("%d\t\t\t\t%d\t\t\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit() {
    int allocation[nProcesses];
    for (int i = 0; i < nProcesses; i++) allocation[i] = -1;

    for (int i = 0; i < nProcesses; i++) {
        int worst = -1;
        for (int j = 0; j < nBlocks; j++) {
            if (blocks[j] >= processes[i]) {
                if (worst == -1 || blocks[j] > blocks[worst]) {
                    worst = j;
                }
            }
        }
        if (worst != -1) {
            allocation[i] = worst;
            blocks[worst] -= processes[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    printf("Process No\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < nProcesses; i++) {
        printf("%d\t\t\t\t%d\t\t\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}


void nextFit() {
    int allocation[nProcesses];
    for (int i = 0; i < nProcesses; i++) allocation[i] = -1;

    for (int i = 0; i < nProcesses; i++) {
        int j = lastAllocIndex, count = 0;
        while (count < nBlocks) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                blocks[j] -= processes[i];
                lastAllocIndex = j;
                break;
            }
            j = (j + 1) % nBlocks;
            count++;
        }
    }

    printf("\nNext Fit Allocation:\n");
    printf("Process No\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < nProcesses; i++) {
        printf("%d\t\t\t\t%d\t\t\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void resetBlocks(int original[]) {
    for (int i = 0; i < nBlocks; i++)
        blocks[i] = original[i];
}

int main() {
    int choice, original[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &nBlocks);
    printf("Enter sizes of memory blocks: ");
    for (int i = 0; i < nBlocks; i++) {
        scanf("%d", &blocks[i]);
        original[i] = blocks[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &nProcesses);
    printf("Enter sizes of processes: ");
    for (int i = 0; i < nProcesses; i++) {
        scanf("%d", &processes[i]);
    }

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Next Fit\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            firstFit();
            break;
        case 2:
            bestFit();
            break;
        case 3:
            worstFit();
            break;
        case 4:
            nextFit();
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }

    return 0;
}
