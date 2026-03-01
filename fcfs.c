#include <stdio.h>
#include <stdlib.h>

// Structure to hold process information
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

// Function to sort processes by arrival time (and by PID if arrival times are equal)
void sort_by_arrival_time(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Sort by arrival time, if equal, sort by PID
            if (p[j].arrival_time > p[j + 1].arrival_time || 
                (p[j].arrival_time == p[j + 1].arrival_time && p[j].pid > p[j + 1].pid)) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    
    // Read number of processes
    scanf("%d", &n);
    
    Process *p = (Process *)malloc(n * sizeof(Process));
    
    // Read PID, arrival time, and burst time for each process
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i].pid, &p[i].arrival_time, &p[i].burst_time);
    }
    
    // Sort processes by arrival time
    sort_by_arrival_time(p, n);
    
    // Calculate completion time, turnaround time, and waiting time
    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++) {
        // If current time is less than arrival time, CPU is idle
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }
        
        // Completion time
        p[i].completion_time = current_time + p[i].burst_time;
        
        // Turnaround time = Completion time - Arrival time
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        
        // Waiting time = Turnaround time - Burst time
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        
        // Update current time and totals
        current_time = p[i].completion_time;
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }
    
    // Calculate averages
    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    
    // Print output in EXACT format required
    printf("Waiting Time: ");
    for (int i = 0; i < n; i++) {
        printf("P%d %d ", p[i].pid, p[i].waiting_time);
    }
    
    printf("Turnaround Time: ");
    for (int i = 0; i < n; i++) {
        printf("P%d %d ", p[i].pid, p[i].turnaround_time);
    }
    
    printf("Average Waiting Time: %.2f Average Turnaround Time: %.2f\n", avg_wt, avg_tat);
    
    free(p);
    return 0;
}