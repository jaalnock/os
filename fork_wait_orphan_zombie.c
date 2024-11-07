#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 20

// Bubble Sort function
void bubble_sort(int arr[MAX], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        // Swap arr[j] and arr[j + 1]
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

// Selection Sort function
void selection_sort(int arr[MAX], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    int min_idx = i;
    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[min_idx])
      {
        min_idx = j;
      }
    }
    // Swap the found minimum element with the first element
    int temp = arr[min_idx];
    arr[min_idx] = arr[i];
    arr[i] = temp;
  }
}

int main()
{
  pid_t pid;
  int i, num, num2;

  // Ask the user to input the number of elements for both arrays
  printf("Enter the number of elements for Bubble Sort array: ");
  scanf("%d", &num2);
  int arr2[MAX]; // Array for Bubble Sort
  printf("Enter the elements for Bubble Sort array: ");
  for (i = 0; i < num2; i++)
  {
    scanf("%d", &arr2[i]);
  }

  printf("Enter the number of elements for Selection Sort array: ");
  scanf("%d", &num);
  int arr[MAX]; // Array for Selection Sort
  printf("Enter the elements for Selection Sort array: ");
  for (i = 0; i < num; i++)
  {
    scanf("%d", &arr[i]);
  }

  pid = fork();

  if (pid == 0)
  {
    // Child process: Bubble sort
    // sleep(10)    // handle this sleep for zombie or orphan state
    printf("\nI am in child... %d", getpid());
    printf("\nMy parent's Id is... %d", getppid());

    bubble_sort(arr2, num2); // Perform Bubble Sort
    printf("\nAFTER PERFORMING THE BUBBLE SORT:\n");
    for (int i = 0; i < num2; i++)
    {
      printf("%d\t", arr2[i]);
    }
    printf("\n");
    printf("\nI (CHILD) COMPLETED MY EXECUTION.\n");
  }
  else
  {
    // Parent process: Selection sort
    // sleep(10)    // handle this sleep for zombie or orphan state
    wait(NULL); // Wait for child process to finish
    // int wstatus, w1;
    // w1 = wait(&wstatus);
    // printf("PID of child : ", w1);
    // printf("State : ", WIFEXITED(wstatus));

    printf("\nI am in parent... %d", getpid());
    printf("\nI am performing Selection Sort on the array.\n");

    selection_sort(arr, num); // Perform Selection Sort
    printf("\nAFTER PERFORMING THE SELECTION SORT:\n");
    for (int i = 0; i < num; i++)
    {
      printf("%d\t", arr[i]);
    }
    printf("\n");

    printf("\nI (PARENT) AM FREE TO EXIT.\n");
    exit(0);
  }

  return 0;
}
