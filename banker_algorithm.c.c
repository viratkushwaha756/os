#include<stdio.h> 
int main() { 
    int p, c, i, j, count = 0, terminate = 0; 
    printf("Enter the number of processes and resources: "); 
    scanf("%d %d", &p, &c); 
 
    int allocation[p][c], max[p][c], need[p][c], available[c], done[p], safe[p]; 
 
    printf("Enter current allocation matrix (%d x %d):\n", p, c); 
    for (i = 0; i < p; i++) 
        for (j = 0; j < c; j++) scanf("%d", &allocation[i][j]); 
 
    printf("Enter max need matrix (%d x %d):\n", p, c); 
    for (i = 0; i < p; i++) 
        for (j = 0; j < c; j++) scanf("%d", &max[i][j]); 
 
    printf("Enter available resources: "); 
    for (i = 0; i < c; i++) scanf("%d", &available[i]); 
 
    for (i = 0; i < p; i++) 
        for (j = 0; j < c; j++) need[i][j] = max[i][j] - allocation[i][j]; 
 
    for (i = 0; i < p; i++) done[i] = 0; 
 
    printf("\nProcess|Max need(A,B,C)|current Alloc(A,B,C)|RN(A,B,C)\n"); 
    printf("--------------------------------------------------------------\n"); 
    for (i = 0; i < p; i++) { 
        printf("P%-2d    | ", i); 
        for (j = 0; j < c; j++) printf("%-4d", max[i][j]);  
        printf("    | "); 
        for (j = 0; j < c; j++) printf("%-4d", allocation[i][j]);  
        printf("    | "); 
        for (j = 0; j < c; j++) printf("%-4d", need[i][j]);  
        printf("\n"); 
    } 
 
    while (count < p) { 
        for (i = 0; i < p; i++) { 
            if (!done[i]) { 
                int can_execute = 1; 
                for (j = 0; j < c; j++) { 
                    if (need[i][j] > available[j]) { 
                        can_execute = 0; 
                        break; 
                    } 
                } 
                if (can_execute) { 
                    safe[count++] = i; 
                    done[i] = 1; 
                    for (j = 0; j < c; j++) available[j] += allocation[i][j]; 
                    break; 
                } 
            } 
        } 
        if (count == p) break; 
        if (terminate == p - 1) { 
            printf("Safe sequence does not exist.\n"); 
            return 0; 
        } 
    } 
 
    printf("\nSafe sequence: "); 
    for (i = 0; i < p; i++) printf("P%-2d", safe[i]); 
    printf("\nAvailable resources after completion: "); 
    for (i = 0; i < c; i++) printf("%-4d", available[i]); 
    printf("\n"); 
 
    return 0; 
} 
