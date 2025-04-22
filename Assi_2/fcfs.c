#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], wt[n], tat[n], ct[n];
    printf("Enter Arrival and Burst Times:\n");

    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

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

    int total_wt = 0, total_tat = 0;
    printf("\nFCFS:\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average WT = %.2f\n", (float)total_wt / n);
    printf("Average TAT = %.2f\n", (float)total_tat / n);
    return 0;
}
