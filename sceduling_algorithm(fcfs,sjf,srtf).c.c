#include <stdio.h>
#include <limits.h>

void findWaitingTime(int bt[], int at[], int n, int wt[], int ct[]) {
    wt[0] = 0;
    ct[0] = at[0] + bt[0];
    for (int i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + bt[i];
        if (at[i] > ct[i - 1]) {
            ct[i] = at[i] + bt[i];
        }
        wt[i] = ct[i] - at[i] - bt[i];
    }
}

void findTurnAroundTime(int bt[], int wt[], int n, int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findAvgTime_FCFS(int bt[], int at[], int n) {
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0;
    findWaitingTime(bt, at, n, wt, ct);
    findTurnAroundTime(bt, wt, n, tat);

    printf("\nFCFS:\nP   AT   BT   CT   TAT  WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d    %d    %d    %d    %d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
}

void findWaitingTime_SJF(int bt[], int at[], int n, int wt[], int ct[]) {
    int remaining[n], completed = 0, t = 0;
    for (int i = 0; i < n; i++) remaining[i] = bt[i];

    while (completed < n) {
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= t && remaining[i] > 0 &&
                (min_index == -1 || remaining[i] < remaining[min_index])) {
                min_index = i;
            }
        }
        if (min_index != -1) {
            t += bt[min_index];
            ct[min_index] = t;
            wt[min_index] = ct[min_index] - at[min_index] - bt[min_index];
            remaining[min_index] = 0;
            completed++;
        } else {
            t++;
        }
    }
}

void findAvgTime_SJF(int bt[], int at[], int n) {
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime_SJF(bt, at, n, wt, ct);
    findTurnAroundTime(bt, wt, n, tat);

    printf("\nSJF:\nP   AT   BT   CT   TAT  WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d    %d    %d    %d    %d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
}

void findWaitingTime_SRTF(int bt[], int at[], int n, int wt[], int ct[]) {
    int remaining[n], completed = 0, t = 0;
    for (int i = 0; i < n; i++) remaining[i] = bt[i];

    while (completed < n) {
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= t && remaining[i] > 0 &&
                (min_index == -1 || remaining[i] < remaining[min_index])) {
                min_index = i;
            }
        }
        if (min_index != -1) {
            remaining[min_index]--;
            t++;
            if (remaining[min_index] == 0) {
                ct[min_index] = t;
                wt[min_index] = ct[min_index] - at[min_index] - bt[min_index];
                completed++;
            }
        } else {
            t++;
        }
    }
}

void findAvgTime_SRTF(int bt[], int at[], int n) {
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime_SRTF(bt, at, n, wt, ct);
    findTurnAroundTime(bt, wt, n, tat);

    printf("\nSRTF:\nP   AT   BT   CT   TAT  WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d    %d    %d    %d    %d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
}

void findWaitingTime_RR(int bt[], int at[], int n, int wt[], int ct[], int quantum) {
    int remaining[n], completed = 0, t = 0;
    for (int i = 0; i < n; i++) remaining[i] = bt[i];

    while (completed < n) {
        int idle = 1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= t && remaining[i] > 0) {
                idle = 0;
                if (remaining[i] > quantum) {
                    t += quantum;
                    remaining[i] -= quantum;
                } else {
                    t += remaining[i];
                    ct[i] = t;
                    wt[i] = ct[i] - at[i] - bt[i];
                    remaining[i] = 0;
                    completed++;
                }
            }
        }
        if (idle) t++;
    }
}

void findAvgTime_RR(int bt[], int at[], int n, int quantum) {
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime_RR(bt, at, n, wt, ct, quantum);
    findTurnAroundTime(bt, wt, n, tat);

    printf("\nRound Robin:\nP   AT   BT   CT   TAT  WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d    %d    %d    %d    %d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
}

void findWaitingTime_Priority_NonPreemptive(int bt[], int at[], int pr[], int n, int wt[], int ct[]) {
    int visited[n], completed = 0, t = 0;
    for (int i = 0; i < n; i++) visited[i] = 0;

    while (completed < n) {
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= t && !visited[i] &&
                (min_index == -1 || pr[i] < pr[min_index])) {
                min_index = i;
            }
        }

        if (min_index != -1) {
            t += bt[min_index];
            ct[min_index] = t;
            wt[min_index] = ct[min_index] - at[min_index] - bt[min_index];
            visited[min_index] = 1;
            completed++;
        } else {
            t++;
        }
    }
}

void findWaitingTime_Priority_Preemptive(int bt[], int at[], int pr[], int n, int wt[], int ct[]) {
    int remaining[n], completed = 0, t = 0, visited[n];
    for (int i = 0; i < n; i++) remaining[i] = bt[i], visited[i] = 0;

    while (completed < n) {
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= t && !visited[i] &&
                (min_index == -1 || pr[i] < pr[min_index])) {
                min_index = i;
            }
        }

        if (min_index != -1) {
            remaining[min_index]--;
            t++;
            if (remaining[min_index] == 0) {
                ct[min_index] = t;
                wt[min_index] = ct[min_index] - at[min_index] - bt[min_index];
                visited[min_index] = 1;
                completed++;
            }
        } else {
            t++;
        }
    }
}

void findAvgTime_Priority(int bt[], int at[], int pr[], int n, int preemptive) {
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0;

    if (preemptive)
        findWaitingTime_Priority_Preemptive(bt, at, pr, n, wt, ct);
    else
        findWaitingTime_Priority_NonPreemptive(bt, at, pr, n, wt, ct);

    findTurnAroundTime(bt, wt, n, tat);

    if (preemptive)
        printf("\nPriority Scheduling (Preemptive):\nP   AT   BT   CT   TAT  WT\n");
    else
        printf("\nPriority Scheduling (Non-Preemptive):\nP   AT   BT   CT   TAT  WT\n");

    for (int i = 0; i < n; i++) {
        printf("%d   %d    %d    %d    %d    %d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
}

int main() {
    int n, quantum, choice, preemptive;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst_time[n], arrival_time[n], priority[n];

    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        printf("Priority : ");
        scanf("%d", &priority[i]);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF(non preemptive)\n3. SRTF\n4. Round Robin\n5. Priority Scheduling\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            findAvgTime_FCFS(burst_time, arrival_time, n);
            break;
        case 2:
            findAvgTime_SJF(burst_time, arrival_time, n);
            break;
        case 3:
            findAvgTime_SRTF(burst_time, arrival_time, n);
            break;
        case 4:
            printf("Enter Quantum Time: ");
            scanf("%d", &quantum);
            findAvgTime_RR(burst_time, arrival_time, n, quantum);
            break;
        case 5:
            printf("Enter 0 for Non-Preemptive, 1 for Preemptive: ");
            scanf("%d", &preemptive);
            findAvgTime_Priority(burst_time, arrival_time, priority, n, preemptive);
            break;
        default:
            printf("Invalid Choice!\n");
    }

    return 0;
}
