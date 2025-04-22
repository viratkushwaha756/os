#include <stdio.h>

void findAvgTime_FCFS(int bt[], int at[], int n) {
    int wt[n], tat[n], ct[n], total_wt = 0, total_tat = 0;

    wt[0] = 0;
    ct[0] = at[0] + bt[0];

    for (int i = 1; i < n; i++) {
        if (at[i] > ct[i - 1])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i - 1] + bt[i];

        wt[i] = ct[i] - at[i] - bt[i];
    }

    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    printf("\nFCFS Scheduling:\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
}

void findAvgTime_SJF(int bt[], int at[], int n) {
    int wt[n], tat[n], ct[n], done[n], total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
        done[i] = 0;

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if (idx != -1) {
            time += bt[idx];
            ct[idx] = time;
            wt[idx] = ct[idx] - at[idx] - bt[idx];
            tat[idx] = bt[idx] + wt[idx];
            done[idx] = 1;
            completed++;
        } else {
            time++;
        }
    }

    printf("\nSJF (Non-Preemptive) Scheduling:\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
}

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n];
    printf("Enter Arrival and Burst Times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF (Non-Preemptive)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            findAvgTime_FCFS(bt, at, n);
            break;
        case 2:
            findAvgTime_SJF(bt, at, n);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
