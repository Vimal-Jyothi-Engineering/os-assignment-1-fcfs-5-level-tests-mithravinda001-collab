#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int pid[100], at[100], bt[100];
    int wt[100], tat[100];

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
    }

    // Sort by arrival time (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                int tmp;
                tmp = at[j];  at[j] = at[j+1];  at[j+1] = tmp;
                tmp = bt[j];  bt[j] = bt[j+1];  bt[j+1] = tmp;
                tmp = pid[j]; pid[j] = pid[j+1]; pid[j+1] = tmp;
            }
        }
    }

    // Compute waiting time and turnaround time
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < at[i]) {
            currentTime = at[i];
        }
        wt[i] = currentTime - at[i];
        tat[i] = wt[i] + bt[i];
        currentTime += bt[i];
    }

    // Compute averages
    double avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT  += wt[i];
        avgTAT += tat[i];
    }
    avgWT  /= n;
    avgTAT /= n;

    // Print all on one line (exact format required)
    printf("Waiting Time:");
    for (int i = 0; i < n; i++) printf(" P%d %d", pid[i], wt[i]);
    printf(" Turnaround Time:");
    for (int i = 0; i < n; i++) printf(" P%d %d", pid[i], tat[i]);
    printf(" Average Waiting Time: %.2f Average Turnaround Time: %.2f\n", avgWT, avgTAT);

    return 0;
}
