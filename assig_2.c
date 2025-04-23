#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
struct Process { 
int pid; 
int arrival_time; 
int burst_time; 
int priority; 
int remaining_time; 
int completion_time; 
int turnaround_time; 
int waiting_time; 
int response_time; 
}; 
void fcfs(struct Process *processes, int n); 
void sjf_non_preemptive(struct Process *processes, int n); 
void priority_non_preemptive(struct Process *processes, int n); 
void priority_preemptive(struct Process *processes, int n); 
void round_robin(struct Process *processes, int n, int quantum); 
void display_results(struct Process *processes, int n, const char *algorithm); 
void get_processes(struct Process *processes, int *n, int include_priority); 
void reset_processes(struct Process *processes, int n); 
void fcfs(struct Process *processes, int n) { 
int current_time = 0; 
// Sort by arrival time 
for (int i = 0; i < n - 1; i++) { 
        for (int j = 0; j < n - i - 1; j++) { 
            if (processes[j].arrival_time > processes[j + 1].arrival_time) { 
                struct Process temp = processes[j]; 
                processes[j] = processes[j + 1]; 
                processes[j + 1] = temp; 
            } 
        } 
    } 
 
    for (int i = 0; i < n; i++) { 
        if (current_time < processes[i].arrival_time) 
            current_time = processes[i].arrival_time; 
        processes[i].response_time = current_time - processes[i].arrival_time; 
        current_time += processes[i].burst_time; 
        processes[i].completion_time = current_time; 
        processes[i].turnaround_time = current_time - processes[i].arrival_time; 
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time; 
    } 
    display_results(processes, n, "FCFS"); 
} 
 
void sjf_non_preemptive(struct Process *processes, int n) { 
    int current_time = 0, completed = 0; 
    int is_completed[100] = {0}; 
 
    while (completed != n) { 
        int shortest_job = -1; 
        int min_burst = INT_MAX; 
        for (int i = 0; i < n; i++) { 
            if (processes[i].arrival_time <= current_time && !is_completed[i]) { 
                if (processes[i].burst_time < min_burst || 
                    (processes[i].burst_time == min_burst && 
                     processes[i].arrival_time < processes[shortest_job].arrival_time)) { 
                    min_burst = processes[i].burst_time; 
                    shortest_job = i; 
                } 
            } 
        } 
 
        if (shortest_job == -1) { 
            current_time++; 
        } else { 
            processes[shortest_job].response_time = current_time - processes[shortest_job].arrival_time; 
            current_time += processes[shortest_job].burst_time; 
            processes[shortest_job].completion_time = current_time; 
            processes[shortest_job].turnaround_time = current_time - processes[shortest_job].arrival_time; 
            processes[shortest_job].waiting_time = processes[shortest_job].turnaround_time - 
processes[shortest_job].burst_time; 
            is_completed[shortest_job] = 1; 
            completed++; 
        } 
    } 
 
    display_results(processes, n, "SJF (Non-Preemptive)"); 
} 
 
void priority_non_preemptive(struct Process *processes, int n) { 
    int current_time = 0, completed = 0; 
    int is_completed[100] = {0}; 
 
    while (completed != n) { 
        int highest_priority = -1; 
        int max_priority = INT_MIN; 
        for (int i = 0; i < n; i++) { 
            if (processes[i].arrival_time <= current_time && !is_completed[i]) { 
                if (processes[i].priority > max_priority || 
                    (processes[i].priority == max_priority && 
                     processes[i].arrival_time < processes[highest_priority].arrival_time)) { 
                    max_priority = processes[i].priority; 
                    highest_priority = i; 
                } 
            } 
        } 
 
        if (highest_priority == -1) { 
            current_time++; 
        } else { 
            processes[highest_priority].response_time = current_time - 
processes[highest_priority].arrival_time; 
            current_time += processes[highest_priority].burst_time; 
            processes[highest_priority].completion_time = current_time; 
            processes[highest_priority].turnaround_time = current_time - 
processes[highest_priority].arrival_time; 
            processes[highest_priority].waiting_time = processes[highest_priority].turnaround_time - 
processes[highest_priority].burst_time; 
            is_completed[highest_priority] = 1; 
            completed++; 
        } 
    } 
 
    display_results(processes, n, "Priority Scheduling (Non-Preemptive)"); 
} 
 
void priority_preemptive(struct Process *processes, int n) { 
    int current_time = 0, completed = 0; 
    int is_completed[100] = {0}; 
 
    while (completed != n) { 
        int highest_priority = -1; 
        int max_priority = INT_MIN; 
 
        for (int i = 0; i < n; i++) { 
            if (processes[i].arrival_time <= current_time && !is_completed[i] && processes[i].remaining_time 
> 0) { 
                if (processes[i].priority > max_priority) { 
                    max_priority = processes[i].priority; 
                    highest_priority = i; 
                } 
            } 
        } 
 
        if (highest_priority == -1) { 
            current_time++; 
        } else { 
            if (processes[highest_priority].response_time == -1) 
                processes[highest_priority].response_time = current_time - 
processes[highest_priority].arrival_time; 
 
            processes[highest_priority].remaining_time--; 
            current_time++; 
 
            if (processes[highest_priority].remaining_time == 0) { 
                processes[highest_priority].completion_time = current_time; 
                processes[highest_priority].turnaround_time = current_time - 
processes[highest_priority].arrival_time; 
                processes[highest_priority].waiting_time = processes[highest_priority].turnaround_time - 
processes[highest_priority].burst_time; 
                is_completed[highest_priority] = 1; 
                completed++; 
            } 
        } 
    } 
 
    display_results(processes, n, "Priority Scheduling (Preemptive)"); 
} 
 
void round_robin(struct Process *processes, int n, int quantum) { 
    int current_time = 0, completed = 0; 
    int is_completed[100] = {0}; 
    int all_done = 0; 
 
    while (!all_done) { 
        all_done = 1; 
        for (int i = 0; i < n; i++) { 
            if (!is_completed[i] && processes[i].arrival_time <= current_time) { 
                all_done = 0; 
 
                if (processes[i].response_time == -1) 
                    processes[i].response_time = current_time - processes[i].arrival_time; 
 
                int time_to_run = (processes[i].remaining_time > quantum) ? quantum : 
processes[i].remaining_time; 
                processes[i].remaining_time -= time_to_run; 
                current_time += time_to_run; 
 
                if (processes[i].remaining_time == 0) { 
                    processes[i].completion_time = current_time; 
                    processes[i].turnaround_time = current_time - processes[i].arrival_time; 
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time; 
                    is_completed[i] = 1; 
                    completed++; 
                } 
            } 
        } 
        if (all_done) break; 
        if (completed != n && all_done) current_time++; // prevent deadlock 
    } 
 
    display_results(processes, n, "Round Robin"); 
} 
 
void display_results(struct Process *processes, int n, const char *algorithm) { 
    float avg_waiting_time = 0, avg_turnaround_time = 0; 
    printf("\n%s Scheduling Results:\n", algorithm); 
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n"); 
    printf("------------------------------------------------\n"); 
    for (int i = 0; i < n; i++) { 
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].completion_time, 
               processes[i].turnaround_time, 
               processes[i].waiting_time, 
               processes[i].response_time); 
        avg_waiting_time += processes[i].waiting_time; 
        avg_turnaround_time += processes[i].turnaround_time; 
    } 
    avg_waiting_time /= n; 
    avg_turnaround_time /= n; 
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time); 
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time); 
} 
 
void get_processes(struct Process *processes, int *n, int include_priority) { 
    printf("\nEnter the number of processes: "); 
    scanf("%d", n); 
    for (int i = 0; i < *n; i++) { 
        printf("\nProcess %d:\n", i + 1); 
        processes[i].pid = i + 1; 
        printf("Enter arrival time: "); 
        scanf("%d", &processes[i].arrival_time); 
        printf("Enter burst time: "); 
        scanf("%d", &processes[i].burst_time); 
        if (include_priority) { 
            printf("Enter priority (higher number = higher priority): "); 
            scanf("%d", &processes[i].priority); 
        } else { 
            processes[i].priority = 0; 
        } 
        processes[i].remaining_time = processes[i].burst_time; 
        processes[i].response_time = -1; 
    } 
} 
 
void reset_processes(struct Process *processes, int n) { 
    for (int i = 0; i < n; i++) { 
        processes[i].remaining_time = processes[i].burst_time; 
        processes[i].response_time = -1; 
        processes[i].completion_time = 0; 
        processes[i].turnaround_time = 0; 
        processes[i].waiting_time = 0; 
    } 
} 
 
int main() { 
    int choice, n, quantum; 
    struct Process processes[100]; 
    while (1) { 
        printf("\nCPU Scheduling Algorithms\n"); 
        printf("1. First Come First Serve (FCFS)\n"); 
        printf("2. Shortest Job First (SJF) - Non Preemptive\n"); 
        printf("3. Priority Scheduling - Non Preemptive\n"); 
        printf("4. Priority Scheduling - Preemptive\n"); 
        printf("5. Round Robin\n"); 
        printf("6. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
        if (choice == 6) break; 
 
        if (choice >= 1 && choice <= 5) { 
            int include_priority = (choice == 3 || choice == 4); 
            get_processes(processes, &n, include_priority); 
            reset_processes(processes, n); // reset before each scheduling 
        } 
 
        switch (choice) { 
            case 1: fcfs(processes, n); break; 
            case 2: sjf_non_preemptive(processes, n); break; 
            case 3: priority_non_preemptive(processes, n); break; 
            case 4: priority_preemptive(processes, n); break; 
            case 5: 
                printf("Enter time quantum: "); 
                scanf("%d", &quantum); 
                round_robin(processes, n, quantum); 
                break; 
            default: 
                printf("Invalid choice!\n"); 
        } 
    } 
    return 0; 
} 
