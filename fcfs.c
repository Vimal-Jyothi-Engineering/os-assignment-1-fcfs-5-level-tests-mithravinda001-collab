#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
} Process;

int main() {
    int n;
    scanf("%d", &n);
    
    Process p[1000];
    
    // Read input
    for(int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst);
    }
    
    // Sort by arrival time (bubble sort)
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].arrival > p[j+1].arrival) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    
    // Calculate times
    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    
    for(int i = 0; i < n; i++) {
        // Handle CPU idle time
        if(current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }
        
        int completion = current_time + p[i].burst;
        p[i].turnaround = completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        
        current_time = completion;
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }
    
    // Print EXACT format required
    printf("Waiting Time: ");
    for(int i = 0; i < n; i++) {
        printf("P%d %d ", p[i].pid, p[i].waiting);
    }
    
    printf("Turnaround Time: ");
    for(int i = 0; i < n; i++) {
        printf("P%d %d ", p[i].pid, p[i].turnaround);
    }
    
    printf("Average Waiting Time: %.2f Average Turnaround Time: %.2f\n", 
           total_wt / n, total_tat / n);
    
    return 0;
}
