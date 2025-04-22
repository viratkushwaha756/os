#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], pr[n], done[n];
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority : ");
        scanf("%d", &pr[i]);
        done[i] = 0;
    }

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, highest = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && pr[i] < highest) {
                highest = pr[i];
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
        } else time++;
    }

    int total_wt = 0, total_tat = 0;
    printf("\nPriority Scheduling (Non-Preemptive):\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
    return 0;
}
