#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int n;
  cout << "Enter the number of requests : ";
  cin >> n;

  cout << "Enter the requests : ";
  vector<int> req(n);
  for (int i = 0; i < n; i++)
  {
    cin >> req[i];
  }

  vector<bool> vis(n, false);

  int initialHead;
  cout << "Initial head position : ";
  cin >> initialHead;

  int totalHeadMov = 0;

  cout << "Seek Sequence : " << initialHead;
  int currHead = initialHead;

  int count = 1;

  while (count < n)
  {
    int minDist = 1e9;
    int minIdx = -1;
    for (int j = 0; j < n; j++)
    {
      if (!vis[j] && abs(req[currHead] - req[j]) < minDist)
      {
        minDist = abs(req[currHead] - req[j]);
        minIdx = j;
      }
    }

    vis[minIdx] = true;
    totalHeadMov += (abs(req[currHead] - req[minIdx]));
    currHead = minIdx;
    cout << " -> " << req[minIdx];
    count++;
  }

  cout << "Total Head Movement : " << totalHeadMov;
  cout << endl;
  return 0;
}