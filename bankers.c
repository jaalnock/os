#include<stdio.h>
#include<stdlib.h>

int main() {
	int n, m;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("Enter the number of resources: ");
	scanf("%d", &m);
	
	int alloc[n][m], max[n][m], need[n][m];
	int available[m];

	printf("Enter the allocated resources for each process:\n");
	for(int i = 0; i < n; i++) {
		printf("Process %d allocation: ", i);
		for(int j = 0; j < m; j++) {
			scanf("%d", &alloc[i][j]);
		}
	}

	printf("Enter the maximum resources required for each process:\n");
	for(int i = 0; i < n; i++) {
		printf("Process %d max need: ", i);
		for(int j = 0; j < m; j++) {
			scanf("%d", &max[i][j]);
		}
	}

	printf("Enter the available resources: ");
	for(int i = 0; i < m; i++) {
		scanf("%d", &available[i]);
	}
	
	// Calculate the need matrix
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}
	
	int done[n], processSeq[n];
	for(int i = 0; i < n; i++) done[i] = 0;
	int count = 0;
	
	// Implement the safety algorithm
	while (count < n) {
		int found = 0;
		for (int i = 0; i < n; i++) {
			if (!done[i]) { // Check if process is not finished
				int flag = 1;
				for (int j = 0; j < m; j++) {
					if (need[i][j] > available[j]) {
						flag = 0; // Not enough resources for this process
						break;
					}
				}

				if (flag) { // If this process can be completed
					processSeq[count++] = i;
					for (int k = 0; k < m; k++) {
						available[k] += alloc[i][k];
					}
					done[i] = 1;
					found = 1;
				}
			}
		}

		if (!found) { // No process was able to execute in this loop
			printf("The system is not in a safe state.\n");
			return 0;
		}
	}

	// If all processes are done, we have a safe sequence
	printf("The system is in a safe state.\nSafe sequence: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", processSeq[i]);
	}
	printf("\n");

	return 0;
}

// Enter the number of processes: 3
// Enter the number of resources: 3
// Enter the allocated resources for each process:      
// Process 0 allocation: 2 1 3
// Process 1 allocation: 1 3 2
// Process 2 allocation: 4 0 1
// Enter the maximum resources required for each process:
// Process 0 max need: 6 4 5
// Process 1 max need: 3 3 2
// Process 2 max need: 4 2 4
// Enter the available resources: 3 2 1
// The system is in a safe state.
// Safe sequence: 1 2 0
