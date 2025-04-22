#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int bt[n], at[n], rt[n], ct[n], wt[n], tat[n];
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    int time = 0, completed = 0;
    int queue[n], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        int i = queue[front++];
        if (rt[i] > 0) {
            if (rt[i] > tq) {
                time += tq;
                rt[i] -= tq;
            } else {
                time += rt[i];
                ct[i] = time;
                rt[i] = 0;
                completed++;
            }

            for (int j = 0; j < n; j++) {
                if (j != i && at[j] <= time && !visited[j] && rt[j] > 0) {
                    queue[rear++] = j;
                    visited[j] = 1;
                }
            }

            if (rt[i] > 0)
                queue[rear++] = i;
        }
    }

    int total_wt = 0, total_tat = 0;
    printf("\nRound Robin:\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
    return 0;
}
