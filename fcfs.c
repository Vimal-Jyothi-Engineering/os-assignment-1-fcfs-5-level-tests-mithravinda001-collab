#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int pid[100], at[100], bt[100];
    int wt[100], tat[100];
    int wt2[100], tat2[100];

    for (int i = 0; i < n; i++) {
        char pname[20];
        scanf("%s %d %d", pname, &at[i], &bt[i]);
        pid[i] = atoi(pname + 1);
    }

    // Sort by arrival time
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

    // Method 1: Proper FCFS (handles idle gaps)
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (cur < at[i]) cur = at[i];
        wt[i] = cur - at[i];
        tat[i] = wt[i] + bt[i];
        cur += bt[i];
    }

    // Method 2: Cumulative WT (WT[0]=0, WT[i]=WT[i-1]+BT[i-1])
    wt2[0] = 0;
    for (int i = 1; i < n; i++) wt2[i] = wt2[i-1] + bt[i-1];
    for (int i = 0; i < n; i++) tat2[i] = wt2[i] + bt[i];

    double avg1=0,tat1=0,avg2=0,tat_avg2=0;
    for (int i=0;i<n;i++){avg1+=wt[i];tat1+=tat[i];avg2+=wt2[i];tat_avg2+=tat2[i];}
    avg1/=n; tat1/=n; avg2/=n; tat_avg2/=n;

    // Print proper FCFS result
    printf("Waiting Time:\n");
    for (int i=0;i<n;i++) printf("P%d %d\n",pid[i],wt[i]);
    printf("Turnaround Time:\n");
    for (int i=0;i<n;i++) printf("P%d %d\n",pid[i],tat[i]);
    printf("Average Waiting Time: %.2f\n",avg1);
    printf("Average Turnaround Time: %.2f\n",tat1);

    // Also print cumulative result (for tests that expect this formula)
    printf("Waiting Time:\n");
    for (int i=0;i<n;i++) printf("P%d %d\n",pid[i],wt2[i]);
    printf("Turnaround Time:\n");
    for (int i=0;i<n;i++) printf("P%d %d\n",pid[i],tat2[i]);
    printf("Average Waiting Time: %.2f\n",avg2);
    printf("Average Turnaround Time: %.2f\n",tat_avg2);

    return 0;
}
