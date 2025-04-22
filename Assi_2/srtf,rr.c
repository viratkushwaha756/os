#include <stdio.h>

void findAvgTime_SRTF(int bt[], int at[], int n) {
    int rt[n], ct[n], tat[n], wt[n];
    for (int i = 0; i < n; i++) rt[i] = bt[i];

    int completed = 0, time = 0, min = 99999, shortest = 0, finish_time, check = 0;

    while (completed != n) {
        min = 99999;
        check = 0;
        for (int i = 0; i < n; i++) {
            if ((at[i] <= time) && (rt[i] < min) && rt[i] > 0) {
                min = rt[i];
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            time++;
            continue;
        }

        rt[shortest]--;
        if (rt[shortest] == 0) {
            completed++;
            finish_time = time + 1;
            ct[shortest] = finish_time;
            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
            tat[shortest] = bt[shortest] + wt[shortest];
        }
        time++;
    }

    int total_wt = 0, total_tat = 0;
    printf("\nSRTF:\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
}

void findAvgTime_RR(int bt[], int at[], int n, int tq) {
    int rt[n], ct[n], tat[n], wt[n], visited[n], queue[n];
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
        visited[i] = 0;
    }

    int time = 0, completed = 0, front = 0, rear = 0;
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
}

int main() {
    int n, choice, tq;
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
    printf("1. SRTF\n");
    printf("2. Round Robin\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            findAvgTime_SRTF(bt, at, n);
            break;
        case 2:
            printf("Enter Time Quantum: ");
            scanf("%d", &tq);
            findAvgTime_RR(bt, at, n, tq);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
