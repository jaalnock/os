#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

void sortArray(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}
int main()
{

  int arr[100];
  int n;
  printf("Enter the no. of elements in arr : ");
  scanf("%d", &n);

  printf("Enter the numbers : \n");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }

  pid_t q;
  printf("Before fork\n");
  q = fork();

  if (q < 0)
  {
    printf("Error Occured");
  }
  else if (q > 0)
  {

    sortArray(arr, n);

    for (int i = 0; i < n; i++)
    {
      printf("%d", arr[i]);
    }

    char *args[n + 2];
    args[0] = (char *)"./exec_child";
    for (int i = 0; i < n; i++)
    {
      args[i + 1] = (char *)malloc(12 * sizeof(char));
      sprintf(args[i + 1], "%d", arr[i]);
    }
    args[n + 1] = NULL;

    if (execve(args[0], args, NULL) == -1)
      printf("Error in execv");

    for (int i = 1; i <= n; i++)
    {
      free(args[i]);
    }

    wait(NULL);
  }
  else
  {
    exit(0);
  }

  return 0;
}