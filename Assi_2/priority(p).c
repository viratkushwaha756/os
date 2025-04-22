#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], rt[n], ct[n], tat[n], wt[n], done[n];
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (lower = higher): ");
        scanf("%d", &pr[i]);
        rt[i] = bt[i];
        done[i] = 0;
    }

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, highest = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && pr[i] < highest && rt[i] > 0) {
                highest = pr[i];
                idx = i;
            }
        }

        if (idx != -1) {
            rt[idx]--;
            if (rt[idx] == 0) {
                ct[idx] = time + 1;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                done[idx] = 1;
                completed++;
            }
        }
        time++;
    }

    int total_wt = 0, total_tat = 0;
    printf("\nPriority Scheduling (Preemptive):\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
    return 0;
}
