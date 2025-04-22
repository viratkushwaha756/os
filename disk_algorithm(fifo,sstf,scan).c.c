#include <stdio.h> 
#include <stdlib.h> 
 
int compare(const void* a, const void* b) { 
    return (*(int*)a - *(int*)b); 
} 
 
void fifo(int requests[], int n, int head) { 
    int total = 0; 
    for (int i = 0; i < n; i++) { 
        total += abs(requests[i] - head); 
        head = requests[i]; 
    } 
    printf("\nFIFO Total Head Movement: %d\n", total); 
} 
 
void sstf(int requests[], int n, int head) { 
    int done[n], total = 0; 
    for (int i = 0; i < n; i++) done[i] = 0; 
 
    for (int i = 0; i < n; i++) { 
        int min = 1e9, pos = -1; 
        for (int j = 0; j < n; j++) { 
            if (!done[j]) { 
                int diff = abs(requests[j] - head); 
                if (diff < min) { 
                    min = diff; 
                    pos = j; 
                } 
            } 
        } 
        total += abs(requests[pos] - head); 
        head = requests[pos]; 
        done[pos] = 1; 
    } 
    printf("\nSSTF Total Head Movement: %d\n", total); 
} 
 
void scan(int requests[], int n, int head, int disk_size) { 
    int total = 0; 
    requests[n] = head; 
    n++; 
    qsort(requests, n, sizeof(int), compare); 
 
    int pos; 
    for (int i = 0; i < n; i++) { 
        if (requests[i] == head) { 
            pos = i; 
            break; 
        } 
    } 
 
    for (int i = pos; i < n - 1; i++) { 
        total += abs(requests[i + 1] - requests[i]); 
    } 
    total += abs(disk_size - 1 - requests[n - 1]); 
 
    for (int i = pos - 1; i >= 0; i--) { 
        total += abs(requests[i + 1] - requests[i]); 
    } 
 
    printf("\nSCAN Total Head Movement: %d\n", total); 
} 
 
void cscan(int requests[], int n, int head, int disk_size) { 
    int total = 0; 
    requests[n] = head; 
    n++; 
    qsort(requests, n, sizeof(int), compare); 
 
    int pos; 
    for (int i = 0; i < n; i++) { 
        if (requests[i] == head) { 
            pos = i; 
            break; 
        } 
    } 
 
    for (int i = pos; i < n - 1; i++) { 
        total += abs(requests[i + 1] - requests[i]); 
    } 
 
    total += abs((disk_size - 1) - requests[n - 1]); 
    total += abs((disk_size - 1) - 0); 
 
    for (int i = 0; i < pos; i++) { 
        total += abs(requests[i + 1] - requests[i]); 
    } 
 
    printf("\nC-SCAN Total Head Movement: %d\n", total); 
} 
 
int main() { 
    int n, head, disk_size, choice; 
    int requests[100]; 
 
    printf("Enter number of track requests: "); 
    scanf("%d", &n); 
 
    printf("Enter track requests: "); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &requests[i]); 
    } 
 
    printf("Enter initial head position: "); 
    scanf("%d", &head); 
 
    printf("Enter disk size : "); 
    scanf("%d", &disk_size); 
 
    printf("\n1. FIFO\n2. SSTF\n3. SCAN\n4. C-SCAN\nEnter your choice: "); 
    scanf("%d", &choice); 
 
    switch (choice) { 
        case 1: 
            fifo(requests, n, head); 
            break; 
        case 2: 
            sstf(requests, n, head); 
            break; 
        case 3: 
            scan(requests, n, head, disk_size); 
            break; 
        case 4: 
            cscan(requests, n, head, disk_size); 
            break; 
        default: 
            printf("Invalid choice.\n"); 
    } 
 
    return 0; 
} 