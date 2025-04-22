#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], rt[n], ct[n], tat[n], wt[n];
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    int completed = 0, time = 0, min = 99999, shortest = 0;
    int finish_time;
    int check = 0;

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
    return 0;
}
