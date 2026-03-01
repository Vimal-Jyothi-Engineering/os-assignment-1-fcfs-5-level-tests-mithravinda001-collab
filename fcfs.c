#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int pid[100], at[100], bt[100];
    int wt[100], tat[100];

    for (int i = 0; i < n; i++) {
        char pname[20];
        scanf("%s %d %d", pname, &at[i], &bt[i]);
        pid[i] = atoi(pname + 1);
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

    // Proper FCFS
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (cur < at[i]) cur = at[i];
        wt[i] = cur - at[i];
        tat[i] = wt[i] + bt[i];
        cur += bt[i];
    }

    double avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) { avgWT += wt[i]; avgTAT += tat[i]; }
    avgWT /= n;
    avgTAT /= n;

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) printf("P%d %d\n", pid[i], wt[i]);
    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) printf("P%d %d\n", pid[i], tat[i]);
    printf("Average Waiting Time: %.2f\n", avgWT);
    printf("Average Turnaround Time: %.2f\n", avgTAT);

    return 0;
}
